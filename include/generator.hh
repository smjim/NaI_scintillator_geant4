#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh" // analogous to NIST table

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction {
public: 
	MyPrimaryGenerator();
	~MyPrimaryGenerator();

	virtual void GeneratePrimaries(G4Event*);	// creates primaries(?) which can be used by the action initialization 

// Define the particle gun:
private:
	G4ParticleGun *fParticleGun;
};

#endif
