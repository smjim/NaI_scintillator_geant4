#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	std::ostringstream fname;
	fname << "../output/output.root";
	//G4cout << "Writing to " << fname << G4endl;

	// Sanity check
	G4int RunID = run->GetRunID();
	G4cout << " >>> Begin Run " << RunID << G4endl;

	man->OpenFile(fname.str());
	/*
	man->CreateNtuple("TimeHist", "Photon Arrival Time Histograms");
	man->CreateNtupleIColumn("eventID");
	man->CreateNtupleIColumn("time_hist", std::vector<int>(nbins));	// time histogram for each event

	man->CreateNtupleDColumn("globalTime");
	man->CreateNtupleDColumn("xPos");
	man->CreateNtupleDColumn("yPos");
	man->CreateNtupleDColumn("zPos");
	man->CreateNtupleDColumn("kineticEnergy");
	man->CreateNtupleDColumn("px");
	man->CreateNtupleDColumn("py");
	man->CreateNtupleDColumn("pz");
	man->CreateNtupleSColumn("creatorProcess");

	man->FinishNtuple();
	*/
}

void MyRunAction::EndOfRunAction(const G4Run* run) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	G4int RunID = run->GetRunID();
	G4cout << " >>> End Run " << RunID << G4endl;

	man->Write();
	man->CloseFile();
}
