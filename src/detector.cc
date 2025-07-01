#include "detector.hh"

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

	// Get the detector id from detector for output
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();

	// Get event ID and global time
	G4int eventID = 1; // TODO get eventID from events
	G4double time = preStepPoint->GetGlobalTime();

	// Get the physical coordinates of the detector
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4ThreeVector posPhoton = preStepPoint->GetPosition();

	G4cout << "Photon position: " << posPhoton << G4endl;	// output position of detection
	G4cout << "ID: " << copyNo << " Detector Position: " << posDetector << G4endl;	// output id of detector that detects photon 
	G4cout << "time: " << time/ 1e9 << " s" << G4endl;

	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillNtupleIColumn(0, eventID); // ntuple id, column id, value
	analysisManager->FillNtupleDColumn(1, time);  // time in ns
	analysisManager->FillNtupleDColumn(2, static_cast<double>(posPhoton.z())); // z position in cm
	analysisManager->AddNtupleRow();
}
