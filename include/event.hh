#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

class MyEventAction : public G4UserEventAction {
public:
    MyEventAction();
    ~MyEventAction();

    virtual void EndOfEventAction(const G4Event*);
};

#endif

