#include "generator.hh"

// constructor
MyPrimaryGenerator::MyPrimaryGenerator() {
	fParticleGun = new G4ParticleGun(1); // # particles per event
	// note: in geant4, you have 1 run, which has several events, and each event can have several particles (or just one)
}

// destructor
MyPrimaryGenerator::~MyPrimaryGenerator() {
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
	// use the particle gun	
	// define what kind of particles to create
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	// find properties of particle to be used (akin to NIST table)
	// in this example, get a proton
	G4String particleName="proton";
	G4ParticleDefinition *particle = particleTable->FindParticle("proton");	// finds corresp. particle and copies information to the *particle

	G4ThreeVector pos(0., 0., 0.);
	G4ThreeVector mom(0., 0., 1.);	// convention to create particle in z direction

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(100.*GeV);	// standard energy unit in Geant is MeV
	fParticleGun->SetParticleDefinition(particle);	// combine all the above to particle

	fParticleGun->GeneratePrimaryVertex(anEvent);	// generates one vertex (particle) for the event(?)

}
