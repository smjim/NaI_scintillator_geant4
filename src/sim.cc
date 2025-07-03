#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

#include "Randomize.hh"
#include <ctime>	// for time()

int main(int argc, char** argv) {
	// Initialize with random seed
	G4long seed = time(nullptr);
	G4Random::setTheSeed(seed);

	G4RunManager *runManager = new G4RunManager();

	// Initialize user classes
	runManager->SetUserInitialization(new MyDetectorConstruction());	// initialize detector	
	runManager->SetUserInitialization(new MyPhysicsList());				// initialize physics
	runManager->SetUserInitialization(new MyActionInitialization());	// initialize action (particle gun / physics list)
	runManager->Initialize();

	// Get UI manager
	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	// ----------------------------------------------
	// GUI mode
	// ----------------------------------------------
	if (argc == 1) {

		// Display Settings
		G4bool show_tracks = true;
		G4bool show_verbose = false;

		G4UIExecutive *ui = new G4UIExecutive(argc, argv);
		G4VisManager *visManager = new G4VisExecutive();
		visManager->Initialize();

		// Visualization commands
		UImanager->ApplyCommand("/vis/open OGL");								// start the open gl viewer
		UImanager->ApplyCommand("/vis/drawVolume");								// draw the volumes that were defined for the detector
		UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0.2 0.2");	// set initial position on detector
		UImanager->ApplyCommand("/vis/viewer/zoom 1.4");						// set initial position on detector
	
		if (show_verbose) {
			UImanager->ApplyCommand("/tracking/verbose 1");						// verbose tracking of the particles
		}
	
		if (show_tracks) {
			UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");		// autorefresh so that the particle tracks are shown 
			UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");		// draw smooth trajectories of particles in simulation
	
			UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");	// Accumulate all events
		}
	
		ui->SessionStart();
	
		delete visManager;
		delete ui;

	// ----------------------------------------------
	// Batch mode: run the macro provided as argument
	// ----------------------------------------------
	} else {
		
		G4String macroFile = argv[1];
		G4String command = "/control/execute " + macroFile;
		UImanager->ApplyCommand(command);

	}

	// Cleanup
	delete runManager;

	return 0;
}
