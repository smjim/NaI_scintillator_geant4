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

	// Get the physical coordinates of the detector and particle
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4ThreeVector posPhoton = preStepPoint->GetPosition();

	// Get particle statistics for output
	G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();	// Particle event ID
	G4double time = preStepPoint->GetGlobalTime();		// Particle impact global time (ns)
	G4double energy = preStepPoint->GetKineticEnergy(); // Particle energy (MeV)
	G4double zpos = static_cast<double>(posPhoton.z());	// Particle impact z position (cm)

	// Save data to analysis manager for ROOT output
	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillNtupleIColumn(0, eventID);	// ntuple id, column id, value
	analysisManager->FillNtupleDColumn(1, time);	// time in ns
	analysisManager->FillNtupleDColumn(2, zpos);	// z position in cm
	analysisManager->FillNtupleDColumn(3, energy);	// particle energy (MeV)
	analysisManager->AddNtupleRow();

/*	// Print output
	G4cout << "Photon position: " << posPhoton << G4endl;	// output position of detection
	G4cout << "ID: " << copyNo << " Detector Position: " << posDetector << G4endl;	// output id of detector that detects photon 
	G4cout << "time: " << time/ 1e9 << " s" << G4endl;
*/
}
