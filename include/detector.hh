#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

#include <vector> 

class MySensitiveDetector : public G4VSensitiveDetector {
public: 
	MySensitiveDetector(G4String);
	~MySensitiveDetector();

	static std::vector<G4double> arrivalTimes;

// Needed in order to process the hits:
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif
