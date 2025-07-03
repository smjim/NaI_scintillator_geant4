#include "detector.hh"

std::vector<G4double> MySensitiveDetector::arrivalTimes;

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {

}

MySensitiveDetector::~MySensitiveDetector() {

}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
	G4Track *track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);	// once a photon is detected, kill it so that it doesnt propagate any more

	// Get start and end points
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();	// when photon enters detector
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();	// when photon leaves detector

	/*
	// Get the detector id from detector for output
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();

	// Get the physical coordinates of the detector and particle
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4ThreeVector posPhoton = preStepPoint->GetPosition();
	G4ThreeVector momPhoton = preStepPoint->GetMomentumDirection();

	// Get particle statistics for output
	G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();	// Particle event ID
	*/
	G4double time = preStepPoint->GetGlobalTime();		// Particle impact global time (ns)
	/*
	G4double energy = preStepPoint->GetKineticEnergy(); // Particle energy (MeV)

	G4String creatorProcess = "primary";
	if (track->GetCreatorProcess())
		creatorProcess = track->GetCreatorProcess()->GetProcessName();

	// Save data to analysis manager for ROOT output
	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillNtupleIColumn(0, eventID);			// Particle event ID 
	analysisManager->FillNtupleDColumn(1, time);			// Particle impact global time (ns)
	analysisManager->FillNtupleDColumn(2, static_cast<double>(posPhoton.x()));	// Particle impact x position (cm)
	analysisManager->FillNtupleDColumn(3, static_cast<double>(posPhoton.y()));	// Particle impact y position (cm)
	analysisManager->FillNtupleDColumn(4, static_cast<double>(posPhoton.z()));	// Particle impact z position (cm)
	analysisManager->FillNtupleDColumn(5, energy*1e6);			// Particle energy (eV)
	analysisManager->FillNtupleDColumn(6, momPhoton.x());		// Particle momentum x (MeV/ c)
	analysisManager->FillNtupleDColumn(7, momPhoton.y());		// Particle momentum y (Mev/ c)
	analysisManager->FillNtupleDColumn(8, momPhoton.z());		// Particle momentum z (Mev/ c)
	analysisManager->FillNtupleSColumn(9, creatorProcess);	// Process responsible for creating particle 
	analysisManager->AddNtupleRow();
	*/

	// Save arrival times for event
	arrivalTimes.push_back(time);

	return true;

/*	// Print output
	G4cout << "Photon position: " << posPhoton << G4endl;	// output position of detection
	G4cout << "ID: " << copyNo << " Detector Position: " << posDetector << G4endl;	// output id of detector that detects photon 
	G4cout << "time: " << time/ 1e9 << " s" << G4endl;
*/
}
