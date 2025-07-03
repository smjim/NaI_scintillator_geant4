#include "G4AnalysisManager.hh"
#include "G4Event.hh"

#include "event.hh"
#include "run.hh"
#include "detector.hh"


MyEventAction::MyEventAction() {}
MyEventAction::~MyEventAction() {}

void MyEventAction::EndOfEventAction(const G4Event* event) {
    auto analysisManager = G4AnalysisManager::Instance();

    const int nbins = MyRunAction::nbins;
    const double tmin = 0.0;     // adjust to match your detector time window
    const double tmax = 200.0;   // in ns

	// Create unique histogram per event
	std::ostringstream histName;
	histName << "arrivalTimes_evt" << event->GetEventID();

	// Create histogram 1d for this event
	int histID = analysisManager->CreateH1(histName.str(), "Photon Arrival Times", nbins, tmin, tmax);

	// Fill histogram 
	for (auto t : MySensitiveDetector::arrivalTimes) {
		analysisManager->FillH1(histID, t);
	}

	// Clear for next event
	MySensitiveDetector::arrivalTimes.clear();

	G4cout << " >> Ending EventAction for event " << event->GetEventID() << G4endl;

	/*
    std::vector<int> hist(nbins, 0);

    for (auto t : MySensitiveDetector::arrivalTimes) {
        int bin = static_cast<int>((t - tmin) / (tmax - tmin) * nbins);
        if (bin >= 0 && bin < nbins) hist[bin]++;
    }

    analysisManager->FillNtupleIColumn(0, event->GetEventID());
    analysisManager->FillNtupleIColumn(1, hist);  // fill vector<int> column
    analysisManager->AddNtupleRow();

    MySensitiveDetector::arrivalTimes.clear();
	*/
}

