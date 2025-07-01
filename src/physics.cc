#include "physics.hh"

// Most of the interesting and useful physics is already defined in Geant, so just load those
// use only the physics that is required, because more physics = more calculation

// the goal of this particular simulation will be a cherenkov light detector
MyPhysicsList::MyPhysicsList() {
	RegisterPhysics (new G4EmStandardPhysics());		// EM interactions
	RegisterPhysics (new G4DecayPhysics());				// radioactive decay
	RegisterPhysics (new G4RadioactiveDecayPhysics());	// radioactive decay
	
	// optics with scintillation
	//RegisterPhysics (new G4OpticalPhysics());			// Optical Physics

	G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
	//opticalPhysics->SetScintillationYieldFactor(1.0);
	//opticalPhysics->SetTrackSecondariesFirst(kScintillation, true);
	//opticalPhysics->SetScintillationExcitiationRatio(0.0); // adjust as needed
	RegisterPhysics (opticalPhysics); 
}

MyPhysicsList::~MyPhysicsList() {
	// nothing for now(?)
}
