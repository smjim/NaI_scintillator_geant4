#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*) {
	std::cout << "hi" << std::endl;
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->OpenFile("output.root");
	man->CreateNtuple("Hits", "Photon Hits");
	man->CreateNtupleIColumn("eventID");
	man->CreateNtupleDColumn("time");
	man->CreateNtupleDColumn("zPos");
	man->FinishNtuple();
}

void MyRunAction::EndOfRunAction(const G4Run*) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->Write();
	man->CloseFile("output.root");
}
