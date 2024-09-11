import FWCore.ParameterSet.Config as cms

# For Run3, need to do this now!
# https://bytemeta.vip/repo/cms-sw/cmssw/issues/36944
from Configuration.Eras.Era_Run3_cff import Run3
process = cms.Process('ggKit', Run3)

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '130X_dataRun3_Prompt_v3')
# process.GlobalTag = GlobalTag(process.GlobalTag, '124X_dataRun3_Prompt_v10')

# process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Sep2018Rereco_v1')
# process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Prompt_v11')
# process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Prompt_v14'

process.GlobalTag = GlobalTag(process.GlobalTag, '140X_dataRun3_Prompt_v4')
# process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 250

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('/store/data/Run2024F/EGamma0/MINIAOD/PromptReco-v1/000/382/250/00000/133c3dd0-3b4d-46cd-af21-f5c2da6333db.root'))

process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

process.TFileService = cms.Service("TFileService", fileName = cms.string('ggTree.root'))

from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
  process,
  jetSource = cms.InputTag('slimmedJets'),
  labelName = 'UpdatedJEC',
  jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'None')
)

process.load("ggAnalysis.ggNtuplizer.ggNtuplizer_miniAOD_cfi")

process.p = cms.Path(
  process.ggNtuplizer
)

