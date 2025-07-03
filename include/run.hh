#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "G4AnalysisManager.hh" // instead of g4root.hh

#include <map>

class MyRunAction : public G4UserRunAction {
public:
	MyRunAction();
	~MyRunAction();

	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);

	static const int nbins = 20;	// number of bins for event time histogram 

	// Map eventID -> histogram ID to keep track if needed
	std::map<int, int> eventHistMap;
};

#endif

