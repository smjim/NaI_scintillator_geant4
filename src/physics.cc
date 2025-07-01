#include "physics.hh"

// NaI scintillator with PMT 
MyPhysicsList::MyPhysicsList() {
	RegisterPhysics (new G4EmStandardPhysics());		// EM interactions
	RegisterPhysics (new G4DecayPhysics());				// radioactive decay
	RegisterPhysics (new G4RadioactiveDecayPhysics());	// radioactive decay
	
	RegisterPhysics (new G4OpticalPhysics());			// Optical Physics

/*	// Modular physics list optics initialization
	G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
	opticalPhysics->SetScintillationYieldFactor(1.0);
	opticalPhysics->SetTrackSecondariesFirst(kScintillation, true);
	opticalPhysics->SetScintillationExcitiationRatio(0.0); // adjust as needed
	RegisterPhysics (opticalPhysics); 
	*/
}

MyPhysicsList::~MyPhysicsList() {
	// nothing for now(?)
}
