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

    config.General.workArea     = 'DataJobs'
    config.General.transferLogs = False
    config.JobType.maxMemoryMB = 2000
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.pluginName   = 'Analysis' 
    config.JobType.psetName     = 'run_data.py'
    config.JobType.sendExternalFolder = True
    config.Data.inputDBS        = 'global'    
    config.Data.splitting       = 'LumiBased' 
    # Change this...
    # config.Data.lumiMask        = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt' # 58.83 /fb
    config.Data.lumiMask        = '/afs/cern.ch/work/j/jnatoli/private/HFCalib/CMSSW_12_3_7/src/RadDam/HFmonitoring/nTuplizer/ggAnalysis/ggNtuplizer/test/LumiMasks/Cert_Collisions2022_355100_362760_Golden.json'
    config.Data.unitsPerJob     = 20
    config.Data.ignoreLocality  = False
    config.Data.publication     = False
    config.Data.allowNonValidInputDataset     = True
    config.Site.storageSite     = 'T2_US_Wisconsin'
    # config.Site.storageSite     = 'T3_CH_CERNBOX'

    # Little sanity check...
    cmssw = os.getenv("CMSSW_BASE")
    proxy = os.getenv("X509_USER_PROXY")
    print(f"Using: {cmssw}")
    print(f"Proxy: {proxy}")

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print(hte.headers)

    # dataset dependent configuration
    # DAS SEARCH "dataset=/EGamma/Run2022*/MINIAOD"

    # Run2022A is all commissioning

    # Run2022B
    # config.General.requestName = 'EGamma_Run2022B'
    # config.Data.inputDataset   = '/EGamma/Run2022B-10Dec2022-v1/MINIAOD'
    # config.Data.outLFNDirBase  = '/store/user/jnatoli/2022HF/'
    # p = Process(target=submit, args=(config,))
    # p.start()
    # p.join()

    # Run2022C
    config.General.requestName = 'EGamma_Run2022C'
    config.Data.inputDataset   = '/EGamma/Run2022C-10Dec2022-v1/MINIAOD'
    config.Data.outLFNDirBase  = '/store/user/jnatoli/2022HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()

    # Run2022D
    config.General.requestName = 'EGamma_Run2022D'
    config.Data.inputDataset   = '/EGamma/Run2022D-10Dec2022-v1/MINIAOD'
    config.Data.outLFNDirBase  = '/store/user/jnatoli/2022HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()

    # E, F, and G only have PromptReco as of April 27, 2023

    # Run2022B, trying the PromptReco set?
    # config.General.requestName = 'EGamma_Run2022B'
    # config.Data.inputDataset   = '/EGamma/Run2022B-PromptReco-v1/MINIAOD'
    # config.Data.outLFNDirBase  = '/store/user/jnatoli/2022HF/'
    # p = Process(target=submit, args=(config,))
    # p.start()
    # p.join()

    
