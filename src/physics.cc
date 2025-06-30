#include "physics.hh"

// Most of the interesting and useful physics is already defined in Geant, so just load those
// use only the physics that is required, because more physics = more calculation

// the goal of this particular simulation will be a cherenkov light detector
MyPhysicsList::MyPhysicsList() {
	RegisterPhysics (new G4EmStandardPhysics()); // EM interactions
	RegisterPhysics (new G4OpticalPhysics()); // optics
}

MyPhysicsList::~MyPhysicsList() {
	// nothing for now(?)
}
