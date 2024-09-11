import FWCore.ParameterSet.Config as cms

ggNtuplizer = cms.EDAnalyzer("ggNtuplizer",

                             VtxLabel             = cms.InputTag("offlineSlimmedPrimaryVertices"),
                             rhoLabel             = cms.InputTag("fixedGridRhoFastjetAll"),
                             rhoCentralLabel      = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
                             electronSrc          = cms.InputTag("slimmedElectrons"),
                             calibelectronSrc     = cms.InputTag("slimmedElectrons"),
                             ebReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedEBRecHits"),
                             eeReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedEERecHits"),
                             esReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedESRecHits"),
                             ak4JetSrc                 = cms.InputTag("slimmedJets"),
                             packedPFCands   = cms.InputTag("packedPFCandidates"),
                             doGenParticles   = cms.bool(True),
                             runOnParticleGun = cms.bool(False),
                             genParticleSrc   = cms.InputTag("prunedGenParticles"),
                             generatorLabel   = cms.InputTag("generator"),
                             newParticles     = cms.vint32(4000011, 4000013, 1000006, 1000022, 1000024, 1000025),
                             pileupCollection = cms.InputTag("addPileupInfo"),

)
