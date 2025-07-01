#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv) {
	G4RunManager *runManager = new G4RunManager();

	// use to initialize detector
	runManager->SetUserInitialization(new MyDetectorConstruction());
	// use to initialize physics
	runManager->SetUserInitialization(new MyPhysicsList());
	// initialize action (particle gun, computation of applicable physics list)
	runManager->SetUserInitialization(new MyActionInitialization());

	runManager->Initialize();

	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	// Make UI manager visualize the stuff
	UImanager->ApplyCommand("/vis/open OGL");							// start the open gl viewer
	UImanager->ApplyCommand("/vis/drawVolume");							// draw the volumes that were defined for the detector
	UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0.2 0.2");	// set initial position on detector
	UImanager->ApplyCommand("/vis/viewer/zoom 1.4");	// set initial position on detector

//	UImanager->ApplyCommand("/tracking/verbose 1");						// verbose tracking of the particles

	UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");		// autorefresh so that the particle tracks are shown 
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");		// draw smooth trajectories of particles in simulation

	UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");	// Accumulate all events

	ui->SessionStart();

	return 0;
}
