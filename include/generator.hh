#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh" // analogous to NIST table
#include "G4IonTable.hh"

#include "Randomize.hh"

enum class GeneratorMode {
	CsOnly,		// use Cs-137 decay (Ba) gamma gun 
	CsAndCo,	// use Cs-137 decay (Ba) gamma gun and Co-60 decay gamma gun
	CsDecay		//imulate Cs-137 ion sitting there and emitting isotropically
};

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction {
public: 
	MyPrimaryGenerator();
	~MyPrimaryGenerator();

	virtual void GeneratePrimaries(G4Event*);	// creates primaries(?) which can be used by the action initialization 

	void SetGeneratorMode(GeneratorMode mode) { fMode = mode; }

// Define the particle gun:
private:
	G4ParticleGun *fParticleGun;
	GeneratorMode fMode = GeneratorMode::CsOnly;

	G4ThreeVector RandomIsotropicDirection();
};

#endif
