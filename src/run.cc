#include "run.hh"
#include <cstdlib>	// for std::getenv

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	// Get outfile from environment variable
	const char* outfile_env = std::getenv("OUTFILE");
	
	// Default to output.root if not set
	G4String filename = (outfile_env != nullptr) ? G4String(outfile_env) : "output";
	G4cout << "Writing to " << filename << G4endl;

	// Sanity check
	G4int RunID = run->GetRunID();
	G4cout << ">>> Begin Run " << RunID << G4endl;

	man->SetFileName(filename);
	man->OpenFile();

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
	G4cout << ">>> End Run " << RunID << G4endl;

	man->Write();
	man->CloseFile();
}
