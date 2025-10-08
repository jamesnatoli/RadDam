{ 
  gROOT->LoadMacro("xAna.C+");
  
  const char* inpaths[] = {
  	"/eos/user/n/naislam/HF_Raddam_2/2025/2025C/MC/WJ/Tuplizer/WJetsToLNu_TuneCP5_13p6TeV_madgraphMLM-pythia8/crab_WJetsToLNu/250909_132410/0000/ggTree_mc_76.root"
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022F_0000-250-499.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022F_0000-500-749.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022F_0000-750-999.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022F_0001-0-249.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022F_0001-250-499.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022F_0001-500_749.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022F_0001-750-999.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022F_0002.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022G_0000.root"
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022B_230427_102334_0000.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022C_230427_133150_0000.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022C_230427_133150_0001.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022D_230427_133210_0000.root"
    // "/eos/user/j/jnatoli/HFCalib/2022HF/EGamma/ggTree_EGamma_Run2022B_230427_102334_0000.root"    
    // "file:/cms/heindl/2018/HF_calibration/EGamma/crab_EGamma_Run2018D/181127_130219/ggTree.root"
  };
  
  xAna(inpaths, (sizeof(inpaths) / sizeof(inpaths[0])));
}
