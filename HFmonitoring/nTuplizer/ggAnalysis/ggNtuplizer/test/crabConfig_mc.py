if __name__ == '__main__':

# Usage : python crabConfig.py (to create jobs)
#         ./multicrab -c status -w <work area> (to check job status)

    import os
    from CRABAPI.RawCommand import crabCommand
    from http.client import HTTPException

    from CRABClient.UserUtilities import config
    config = config()
    
    from multiprocessing import Process

    # Common configuration

    config.General.workArea     = 'MCJobs'
    config.General.transferLogs = False
    config.JobType.maxMemoryMB = 5000
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.pluginName   = 'Analysis' 
    config.JobType.psetName     = 'run_mc.py'
    config.JobType.sendExternalFolder = True
    config.Data.inputDBS        = 'global'    
    config.Data.splitting       = 'FileBased' 
    config.Data.unitsPerJob     = 10
    config.Data.ignoreLocality  = False
    config.Data.publication     = False
    config.Site.storageSite     = 'T2_US_Wisconsin'

    # Little sanity check...
    cmssw = os.getenv("CMSSW_BASE")
    print(f"Using: {cmssw}")

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print(hte.headers)

    # dataset dependent configuration
    # DAS SEARCH "dataset=/DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3*/MINIAODSIM"
    # Part 1
    # config.General.requestName = 'DYJetsToLL_M-50_Winter22'
    # config.Data.inputDataset   = '/DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9_ext1-v1/MINIAODSIM'
    # config.Data.outLFNDirBase  = '/store/user/jnatoli/2022HF/'
    # p = Process(target=submit, args=(config,))
    # p.start()
    # p.join()

    # Part 2
    config.General.requestName = 'DYJetsToLL_M-50_Winter22_v2'
    config.Data.inputDataset   = '/DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9_ext2-v2/MINIAODSIM'
    config.Data.outLFNDirBase  = '/store/user/jnatoli/2022HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()

    




