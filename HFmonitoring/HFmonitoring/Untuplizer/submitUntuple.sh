#!/bin/bash
# script to submit condor jobs for the Untuple step

# TODO: works for all root files under an era
# TODO: figure out procedure for if jobs fail?

RCOMP="`root-config --cflags --glibs`"
macro=xAna_data.C
bin=xanadata

# Parse arguments
iflag=false; oflag=false; eflag=false; uflag=false; nflag=false; dflag=false
while getopts ":i:o:e:u:n:d" opt; do
    case ${opt} in
	i) iflag=true; indir=$OPTARG;;
	o) oflag=true; copydir=$OPTARG;;
	e) eflag=true; era=$OPTARG;;
	u) uflag=true; site=$OPTARG;;
	n) nflag=true; nfilesInChunk=$OPTARG;;
	d) dflag=true;;
	?) echo "Usage: ./submitUntuple.sh [-i InputDirectory] [-o OutputDirectory] [-e era (EGamma0_Run2023B_0000)] [-u site (T3_US_WISCONSIN)] [-n nperchunk] [-d]"
	    echo "Exiting..."; exit 1;;
	:) echo "ERROR: Option $OPTARG requires an argument... exiting"; exit 1;;
    esac
done

# Check required args
if ! ${iflag} || ! ${oflag} || ! ${eflag}; then
    echo "Error: One or more arguments missing, exiting..."
    exit 1
fi

# Clean url
if $uflag; then
    if [[ $site == "T3_US_WISCONSIN" ]]; then
	url=davs://cmsxrootd.hep.wisc.edu:1094/
    else
	echo "Error: Unknown site \"$site\", exiting..."; exit 1
	# url=cms-xrd-global.cern.ch
    fi
    # Check VOMS (TODO: set it up)
    if [ -z $X509_USER_PROXY ]; then
	echo "Error: VOMS proxy not set but needed by ${url}... exiting"; exit 1
    fi
fi

# Clean nperchunk
if $nflag; then
    re_NumCheck='^[0-9]+$'
    if ! [[ $nperchunk =~ $re_NumCheck ]] ; then
	echo "Error: Integer number of files per chunk required, exiting..."; exit 1
    fi
fi

# Make these vars available to the condor submission script
export era
export copydir=${url}${copydir}/${era}
indir=${url}${indir}

# Check if environment is clean
if [ ! -z ${CMSSW_BASE} ]; then
  echo -e "\tError: This script must be run in a clean environment. You already have a CMSSW environment set up for ${CMSSW_VERSION}."
  echo -e "\tPlease try again from a clean shell."
  exit 1
fi


# Compile the code
echo ">>> Compiling macro: ${macro}" 
if ! $(g++ $RCOMP $macro -o $bin); then
    echo -e "\tCouldn't compile ${macro}... exiting"
    exit 1
fi


chunk=0
counter=1
chunkdir=${era}/infiles
[ $nfilesInChunk ] || nfilesInChunk=100

echo ">>> Era:    ${era}"
echo ">>> Indir:  ${indir}"
echo -e ">>> Outdir: ${copydir}\n"

# Create directories as necessary
echo ">>> Checking directories: ${era}" 
if [ ! -d ${era} ]; then
    echo -e "\tcreating directory ${era}..."
    mkdir ${era}
fi

if [ ! -d ${chunkdir} ]; then
    echo -e "\tcreating directory ${chunkdir}..."
    mkdir ${chunkdir}
fi

if [ ! -d ${era}/jobs ]; then
    echo -e "\tcreating jobs directories..."
    mkdir ${era}/jobs
fi

if [ ! -d ${era}/jobs/err ]; then
    echo -e "\tcreating err directories..."
    mkdir ${era}/jobs/err
fi

if [ ! -d ${era}/jobs/out ]; then
    echo -e "\tcreating out directories..."
    mkdir ${era}/jobs/out
fi

if [ ! -d ${era}/jobs/log ]; then
    echo -e "\tcreating log directories..."
    mkdir ${era}/jobs/log
fi

# Check for existing chunks
echo ">>> Checking for chunks:  ${chunkdir}" 
# NB: &> redirects stderr and stdout, > just stdout
if ls ${chunkdir}/*.txt &> /dev/null; then
    echo -e "\tOld chunks exist... deleting"
    rm ${chunkdir}/*.txt
fi

# Look for the files
echo ">>> Looking for files:    ${indir}" 
if ! env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir} > /dev/null; then
    echo -e "\tUnable to access files: ${indir}"
    echo -e "\tExiting..."
    exit 1
else
    totalFiles=$(env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir} | wc -l)
fi

# Make the chunks
echo ">>> Will create chunks of ${nfilesInChunk} from ${totalFiles} files"
echo ">>> Creating chunk: ${chunk}"
for file in $( env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir}); do
    if [[ $file == *.root ]]; then # only match root files
	echo ${indir}/${file} >> ${chunkdir}/chunk_${chunk}.txt
	if [ $((${counter} % ${nfilesInChunk})) -eq 0 ]; then
	    chunk=$((${chunk} + 1))
	    echo ">>> Creating chunk: ${chunk}"
	fi
	counter=$((${counter} + 1))
    else
	echo -e "\tfile: ${file} is not a ROOT file"
    fi
done

# Submit jobs!
if $dflag; then 
    echo ">>> This was a dry run... skipping submission"
else
    echo ">>> Submitting jobs: condor_submit era=${era} condor_submit.sub"
    condor_submit era=${era} condor_submit.sub
fi
