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
    config.Data.lumiMask        = '/afs/cern.ch/user/n/naislam/HF_Raddam_2/2025/2025C/CMSSW_15_0_6_patch1/src/RadDam/HFmonitoring/nTuplizer/ggAnalysis/ggNtuplizer/test/LumiMasks/Cert_Collisions2025_391658_393446_Golden.json'
    config.Data.unitsPerJob     = 20
    config.Data.ignoreLocality  = False
    config.Data.publication     = False
    config.Data.allowNonValidInputDataset     = True
    #config.Site.storageSite     = 'T2_US_Wisconsin'
    config.Site.storageSite     = 'T3_CH_CERNBOX'

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
    '''

    Run2022B, trying the PromptReco set?
    config.General.requestName = 'EGamma_Run2022B'
    config.Data.inputDataset   = '/EGamma/Run2022B-PromptReco-v1/MINIAOD'
    config.Data.outLFNDirBase  = '/store/user/jnatoli/2022HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()
    '''
    #Run2024I                                  
    config.General.requestName = 'EGamma3_Run2025C-PromptReco_v2'                                                  
    config.Data.inputDataset   = '/EGamma3/Run2025C-PromptReco-v2/MINIAOD'                                   
    config.Data.outLFNDirBase  = '/store/user/naislam/HF_Raddam_2/2025/2025C/Tuplizer/'
    #config.Data.outLFNDirBase  = '/eos/cms/store/group/dpg_hcal/comm_hcal/Naila/HF_Raddam_2/2025/2025C/Tuplizer'                        
    p = Process(target=submit, args=(config,))                                                                        
    p.start()                                                                                                 
    p.join()
    
