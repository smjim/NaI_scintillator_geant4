#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	// Create unique filename per run
	G4int runID = run->GetRunID();
	std::ostringstream fname;
	fname << "../output/output_run_" << runID << ".root";

	man->OpenFile(fname.str());
	man->CreateNtuple("Hits", "Photon Hits");
	man->CreateNtupleIColumn("eventID");
	man->CreateNtupleDColumn("time");
	man->CreateNtupleDColumn("zPos");
	man->FinishNtuple();
}

void MyRunAction::EndOfRunAction(const G4Run*) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->Write();
	man->CloseFile();
}
