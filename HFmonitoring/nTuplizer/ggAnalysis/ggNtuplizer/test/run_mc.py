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

process.GlobalTag = GlobalTag(process.GlobalTag, '142X_mcRun3_2025_realistic_v9')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('/store/mc/Run3Winter25MiniAOD/WJetsToLNu_TuneCP5_13p6TeV_madgraphMLM-pythia8/MINIAODSIM/142X_mcRun3_2025_realistic_v7-v2/100000/42b1b758-2ff9-4100-b23c-97a77ea86612.root'))

process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

process.TFileService = cms.Service("TFileService", fileName = cms.string('ggTree_mc.root'))

from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJets'),
    labelName = 'UpdatedJEC',
    jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None')
    )

process.load("ggAnalysis.ggNtuplizer.ggNtuplizer_miniAOD_cfi")

process.ggNtuplizer.doGenParticles=cms.bool(True)
process.p = cms.Path(
    process.ggNtuplizer
    )

