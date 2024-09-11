# HF Z-->ee Radiation Damage Calibrations
Framework to study the radiation damage of the Hadron Forward (HF) Calorimeter using Z-->ee events. There are 3 steps required to make plots, which utilize both CRAB and HTCondor batch submission systems

Usefull Links:
- <a href="https://cds.cern.ch/record/2691403/files/Sirunyan_2020_J._Inst._15_P05002.pdf" target="_blank">HCAL Calibration Paper</a>
- <a href="https://twiki.cern.ch/twiki/bin/view/CMS/PdmVRun3Analysis" target="_blank">PdmV Run 3 Analysis Recipes</a>
- <a href="https://twiki.cern.ch/twiki/bin/view/CMS/PdmVRun2LegacyAnalysis" target="_blank">PdmV Run 2 UL Analysis Recipes</a>
- <a href="https://cms-service-dqmdc.web.cern.ch/CAF/certification/" target="_blank">Golden JSONs</a>

# Analysis Recipes
Analyzing different eras of data requires a few different parameters. The following table summarizes those for the studies that have been completed. The `CMSSW` versions do not need to be exact, but must be **newer** than listed (x is any number)

| Year | Eras | Data | MC | CMSSW | Golden JSON |
| -----| :--: | ---- | -- | ----- | ----------- |
| 2018         | A, B, C, D | |
| 2022preEE    | C, D       | /EGamma/Run2022\*22Sep2023\*/MINIAOD | /DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM | `CMSSW_12_3_x` | Collisions22/Cert_Collisions2022_355100_362760_Golden.json |
| 2022postEE   | E*, F, G   | /EGamma/Run2022\*22Sep2023\*/MINIAOD | DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v5-v2/MINIAODSIM | `CMSSW_12_3_x` | Collisions22/Cert_Collisions2022_355100_362760_Golden.json |
| 2023preBPix  | C          | /EGamma*/Run2023C-22Sep2023*/MINIAOD | /DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v1/MINIAODSIM | `CMSSW_13_0_6` | Collisions23/Cert_Collisions2023_366442_370790_Golden.json |
| 2023postBPix | D          | /EGamma*/Run2023D-22Sep2023*/MINIAOD | /DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer23BPixMiniAODv4-130X_mcRun3_2023_realistic_postBPix_v2-v3/MINIAODSIM | `CMSSW_13_0_10` | Collisions23/Cert_Collisions2023_366442_370790_Golden.json |
| 2024         | C, D, E, F | /EGamma*/Run2024*/MINIAOD            | /DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Winter24MiniAOD-133X_mcRun3_2024_realistic_v10-v3/MINIAODSIM | `CMSSW_14_0_11` | Collisions24/Cert_Collisions2024_378981_383743_Golden.json |

# Table of Contents
0. [Setup](#step-0-setup)
1. [nTuplizer](#step-1-ntuplizer)
2. [Untuplizer](#step-2-untuplizer)
	1. [Running Interactively](#running-interactively)
 	2. [Using Condor Jobs](#using-condor-jobs)
		1. [Useful Condor Links](#useful-condor-links)
4. [Analysis & Plotting](#step-3-analysis--plotting)
	1. [Analysis](#analysis)
	2. [Plotting](#plotting)
	3. [Deriving Corrections](#deriving-corrections)
		1. [Radiation Damage](#radiation-damage)
		2. [Pileup](#pileup)
	4. [Typical Workflow](#typical-workflow)


# Step 0: Setup
Checkout an appropriate CMSSW version. Below is an example for 2022:
```
cmsrel CMSSW_12_4_11_patch3
cd CMSSW_12_4_11_patch3/src
git clone https://github.com/jamesnatoli/RadDam.git
cmsenv
```

# Step 1: nTuplizer
The first step in the workflow is to process MINIAOD samples. HF sits outside of the tracker acceptance, so we need to build electron candidates ourselves from Particle Flow (PF) jets. This involves adding a module `ggNtuplizer` to CMSSW such that it can be used to process samples. To compile this module, execute the following steps, beginning from the `CMSSW_X_X_X/src` directory

```
cp -r RadDam/HFmonitoring/nTuplizer/ggAnalysis .
scram b clean
scram b -j10
```
If you make a change to the `ggNtuplizer` module, you must copy if again to `CMSSW_X_X_X/src` and recompile. The compile command can only access modules that are in `/src/`. The `scram b -j10` command must be run from `CMSSW_X_X_X/src` and should print out something similar to the following, if our additional modules were properly compiled

```
Entering library rule at src/ggAnalysis/ggNtuplizer/plugins
>> Compiling edm plugin /afs/cern.ch/work/j/jnatoli/private/HCAL/HFCalib/CMSSW_12_4_11_patch3/src/ggAnalysis/ggNtuplizer/plugins/ggNtuplizer.cc
>> Compiling edm plugin /afs/cern.ch/work/j/jnatoli/private/HCAL/HFCalib/CMSSW_12_4_11_patch3/src/ggAnalysis/ggNtuplizer/plugins/ggNtuplizer_globalEvent.cc
>> Compiling edm plugin /afs/cern.ch/work/j/jnatoli/private/HCAL/HFCalib/CMSSW_12_4_11_patch3/src/ggAnalysis/ggNtuplizer/plugins/ggNtuplizer_hfelectrons.cc
>> Compiling edm plugin /afs/cern.ch/work/j/jnatoli/private/HCAL/HFCalib/CMSSW_12_4_11_patch3/src/ggAnalysis/ggNtuplizer/plugins/ggNtuplizer_electrons.cc
>> Leaving Package RadDam/HFmonitoring
>> Leaving Package RadDam/oldHFmonitoring
>> Leaving Package oldRaddam/HFmonitoring
>> Package RadDam/HFmonitoring built
>> Package RadDam/oldHFmonitoring built
>> Package oldRaddam/HFmonitoring built
>> Subsystem RadDam built
>> Subsystem oldRaddam built
>> Building  edm plugin tmp/slc7_amd64_gcc10/src/ggAnalysis/ggNtuplizer/plugins/ggAnalysisggNtuplizerAuto/libggAnalysisggNtuplizerAuto.so
Leaving library rule at src/ggAnalysis/ggNtuplizer/plugins
```

**NB:** at the moment, CRAB does **NOT** work with the new `el9` architecture. This means that it must be used with a `sl7` CMSSW release

The code is now ready to use, and can be executed with the macros in the `RadDam/HFmonitoring/nTuplizer/ggAnalysis/ggNtuplizer/test` directory. Global Tag (GT) information can be found at the [PdmVRun3Analysis](https://twiki.cern.ch/twiki/bin/view/CMS/PdmVRun3Analysis) site. If there is no GT available on this website yet, the GT used to process the file can also be found directly on DAS by making a query with `condig dataset=/DATA/SET/`. To process a single file, add the path to the file from DAS in the line
```
process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('/store/data/path/to/file.root'))
```
and then use `cmsRun` to run the appropriate python script. If you are processing a file that is not stored locally, be sure to set your VOMS proxy.
```
cmsRun run_data.py
```

This will create a new root file in the directory called `ggTree.root`, which can be inspected. It is a good idea to check that the code works with a single file from the dataset you plan to process before submitting to CRAB, to avoid all of the jobs failing. 

Jobs are submitted to CRAB via `crabConfig_data.py` and `crabConfig_mc.py`. The datasets to be processed must be specificed with their DAS paths. We typically use the EGamma datasets and the DYJetsToLL_M-50 MadGraph-MLM mc samples in this analysis. A luminosity mask is specified with the variable `config.Data.lumiMask` and can be found in `/eos/user/c/cmsdqm/www/CAF/certification/` or [online](https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions23/), but the path specific must be accessible from lxplus. 

Everytime you login, the CRAB environment must be setup prior to submission with: 
```
cmsenv
source /cvmfs/cms.cern.ch/common/crab-setup.sh
```

The CRAB jobs are submitted with 
```
python3 crabConfig_data.py
```
which crates a directory `DataJobs` with a subdirectory named according to the variable `config.General.requestName`. The jobs can be monitored with `crab status DataJobs/RequestName` which also provides a grafana link.

# Step 2: Untuplizer
This step can proceed either interactively or via jobs with Condor. The interactive script can take a long time to run (5-10 hours, or more) and so it can be more convenient to use jobs. Both methods are described below

## Running Interactively
- Use hadd to combine the nTuple trees (recommended to have one final MC file and one final data file for each run range)
- Compare the EGamma cut-based ID for ECAL electrons in xAna macros (~L220) with [latest recommendations](https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2)
  **NOTE:** usually we have to use the ID from the year before or very preliminary IDs
- Add hadded nTuple paths in run macros (`run_data.C` and `run_mc.C`) and execute these with ROOT: `root -l run_data.C`

## Using Condor Jobs
Rather than hadding the all of the ggTree.root output files from the nTuplizer step, we will group them in to more manageable chunks and then run one job per chunk. 

Condor jobs require a submission script, `condor_submit.sub` and executable, `for_condor_xanadata.sh`. A bash script has also been created to help with submission, `submitUntuple.sh`. This helper script compiles the c++ code, creates necessary directories (if not present), and prepares a list of files for which to use as inputs for the condor jobs. The number of files per chunk defaults to 100 and is set by `filesInChunk`.

In order to submit jobs, the user must have a valid VOMS proxy and a way to access the storage location of the ggTree.root files, as well as the storage location for the output of this step. Currently, the `gfal` protocal is used for accessing data at different sites, and copying the job outputs from condor to the storage location.

The bash helper script `submitUntuple.sh` contains three lines at the top which must be changed for your specifications. 
```
export url=""
export era=EGamma0_Run2023B_0000
export copydir=${url}/eos/user/j/jnatoli/Untuplizer/${era}
```

- `url`: used if your storage site is not where you are running the code from. For example, if you are submitting from lxplus but the data is stored on the University of Wisconsin T3 cluster, the url will be `davs://cmsxrootd.hep.wisc.edu:1094`
- `era`: a unique name for the job, ideally descriptive of the task
- `copydir`: the storage location for the output, must be accessible from condor

Once these variables are set, the jobs can be submitted with 
```
./submitUntuple.sh [path to input files]
```
The following are examples for passing in input files located on `eos` and the Wisconsin T3 cluster
```
./submitUntuple.sh /eos/user/j/jnatoli/2023HF/EGamma0/crab_EGamma0_Run2023B_test/231105_135940/0000/
./submitUntuple.sh /store/user/jnatoli/2022HF/EGamma/crab_EGamma_Run2022F/231003_155006/0002/
```

### Useful Condor Links
- [Condor submit file documentation](https://htcondor.readthedocs.io/en/latest/users-manual/submitting-a-job.html)
- [Advanced Commands](https://indico.cern.ch/event/611296/contributions/2604401/attachments/1472675/2279456/TJs_Did_You_Know_Condor_Week_Madison_2017.pdf)

# Step 3: Analysis & Plotting
## Analysis
Now that the samples are Untupled, we can fill histograms (Analysis Step) and then plot data and mc together (Plotting Step). At this point, you will need to `hadd` the files from the Untuple step. They should be small enough by now that you can move them to whichever site you are actively working on, if they are not stored there already. An example is below:
```
hadd output_dataBCD_10Dec2022.root source1.root source2.root source3.root ... 
hadd output_DYJetsToLL_M-50_Winter22.root source1.root source2.root source3.root ... 
```
The names are arbitrary, as long as the data file contains the name `data`. A few values must be properly set the `Loop` function of `Analysis22.C` in prior to execution:
- `usePU`: set to `true` if you want to apply Pileup Corrections. These need to be derived from the plots. Default: `false`
- `useRaddam`: set to `true` if you want to apply radiation damage corrections. These also need to be derived. Default: `false`
- `numfactors`: for deriving the radition damage corrections, set to `0` if you do not want to do this. Default: `11`
- `finterval`: for deriving the radition damage corrections, the spacing between values used to plot the line. Default: `0.1`
- `tag`: a unique identifying name for the output root file which will contain the histograms

Once these are set properly, you can go about executing the Analysis code with interactive ROOT:
```
root -l Analysis22.C
root [0] 
Processing Analysis22.C...
(Analysis22) @0x6a24ac0
root [1] Analysis22 a("/Path/to/output_dataBCD_10Dec2022.root")
(Analysis22 &) @0x7f9a8e070208
root [2] a.Loop()
```
This step can take up to a few hours, depending on how many events are being analyzed.

If you have multiple files from the Untuple step and don't want to `hadd` them for some reason, you can pass a `TChain` to the Analysis22.C function as well. You **must** set a name for the TChain in order for the output file to be named appropriately.
```
root -l 
root [0] TChain *bb = new TChain("miniTree")
(TChain *) 0x55f7724e81f0
root [1] bb->Add("file1.root")
(int) 1
root [2] bb->Add("file2.root")
root [3] bb->SetName("output_data_files1_2.root")
root [4] .L Analysis22.C
root [5] Analysis22 a(bb)
(Analysis22 &) @0x7f2d5e9dd000
root [6] a.Loop()
```
## Plotting
Once **both** data and mc are analyzed, we can make plots. First, use the `makeFigDir.sh` script to create a directory with the necessary dependencies
```
./makeFigDir.sh NewFigDir2022
```
The following lines need to be changed in `MakePNGPlots22.C` according to your specifications, where `figdir` should match the directory you have just created. The files `fMC` and `fData` should be locations of the files produced in the previous Analysis step.
```
TString figdir = "Figures22_noPU/";
TFile *fMC = new TFile("outplots/outplots2022_mc_noPU.root");
TFile *fData = new TFile("outplots/outplots2022_data_noPU.root");
```

Execute this macro with ROOT to produce the plots
```
root -l MakePNGPlots22.C
```
The plots will be populated in `figdir`
## Deriving Corrections
This analysis focuses on assessing the radiation damage to HF and deriving appropriate corrections which can then be applied on the detector during data taking. The effects of pileup (PU) are also taken in to account. This typically does not change the results of the radiation damage corrections, but are still important to be applied to remove sources of error
### Radiation Damage 
To derive the radiation damage corrections, we must perform a few steps, running the Analysis22.C code twice more. These steps assume that you have already ran the Analysis22.C code on data and MC with **no** corrections applied and produced the plots.

1) Take the MC / Data ratios outputted to terminal by `MakePNGPlots22.C` and add them to `Raddam.C` just like the other ratios for the other years
2) Rerun `Analysis22.C`, now changing `numfactors` to some nonzero value. I usually test 11 values spaced 0.1 apart, which calculates factors of 1.0, 1.1, 1.2, ... , 2.0
3) Now run edit the following lines in `CalcRaddamFactors.C` to use the data file that was just produced. It should have `_radFactors_` in its name.
   
    ```
    TString figdir = "FactorFigures/";
    TFile *fMC = new TFile("outplots/outplots_mc.root");
    TFile *fData = new TFile("outplots/output_data_radFactors.root");
    ```
5) Take the factors outputted by the script and add them to `Raddam.C` just like the other factors for the other years
6) Rerun `Analysis22.C`, now changing `numfactors` back to **zero** and `useRaddam` to **true**
7) Lastly, run `MakePNGPlots22.C` on the output of the analysis script. It should have `_RaddCorr_` in it's name. Be sure to change the output `figdir` in `MakePNGPlots22.C` to something descriptive so that the original images aren't overwritten.

Now we have plots of the data with the appropriate radiation damage corrections applied 

**NB:** The MC file will stay the same throughout all of this

### Pileup 
The p<sub>T</sub> of both electrons (ECAL and HF) is corrected in both data and MC to remove the dependence of the reconstructed Z mass on the number of PU vertices in a given evnet. The corrections are applied in the following lines:
```
if (usePU == 1) { puCorrection = 1./(1.0 + 0.095/78.464*(nvtx-29)); } // MC (peak @ 29)
if (usePU == 1 && isData == 1 ) { puCorrection = 1./(1.0 + 0.078/68.909*(nvtx-27)); } // Data (peak @ 27)
```
The formula for the PU corrections are
$$\frac{1}{1 + \frac{m}{b}(x - p)}$$

## Typical Workflow
After the requisite data and mc samples have been processed through steps 1 and 2, the analysis/plotting step is run multiple times
- **Bare Comparisons:** First analyze both data and mc with **no** corrections applied, to make plots with the bare data/mc comparisons. The results of this step will be used to derive corrections if necessary. During the analysis step of data, you can derive the factors, it will not affect the plots
- **Deriving Corrections:** Next, follow the steps in [Deriving Corrections](#deriving-corrections). The radiation damage corrections affect the pileup corrections, so they should be derived first. After applying the radiation damage, the pileup corrections can be derived
- **Applying Corrections:** Now apply the corrections by changing appropriate lines in `Analysis22.C` and rerun the analysis code with the boolean values  `true` so that they are applied. 


