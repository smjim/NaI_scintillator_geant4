#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*) {
	std::cout << "hi" << std::endl;
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	G4cout << "Filling: eventID = " << eventID << ", time = " << time << ", z pos = " << posPhoton.z << G4endl;
	man->OpenFile("output.root");
	man->CreateNtuple("Hits", "Photon Hits");
	man->CreateNtupleIColumn("eventID");
	man->CreateNtupleIColumn("time");
	man->CreateNtupleIColumn("posPhoton");
	man->FinishNtuple();
}

void MyRunAction::EndOfRunAction(const G4Run*) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->Write();
	man->CloseFile("output.root");
}
