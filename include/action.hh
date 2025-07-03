#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"
#include "event.hh"

class MyActionInitialization : public G4VUserActionInitialization {
public: 
	MyActionInitialization();
	~MyActionInitialization();

	virtual void Build() const;	// main function - runs particle gun and computes stepping
};

#endif
