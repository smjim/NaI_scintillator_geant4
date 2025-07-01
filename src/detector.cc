#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {

}

MySensitiveDetector::~MySensitiveDetector() {

}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
	G4Track *track = aStep->GetTrack();

	track->SetTrackStatus(fStopAndKill);	// once a photon is detected, kill it so that it doesnt propagate any more

	// after every step process a charged particle will have both
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();	// when photon enters detector
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();	// when photon leaves detector

	G4ThreeVector posPhoton = preStepPoint->GetPosition();

	G4cout << "Photon position: " << posPhoton << G4endl;	// output position of detection

	// Get the detector id from each detector for output
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();

	// Get the physical coordinate of the detector
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();

	G4cout << "ID: " << copyNo << " Detector Position: " << posDetector << G4endl;	// output id of detector that detects photon 


}
