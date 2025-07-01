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

/* /////////////////////////////////////
	For 55Cs137 decay, 0.512 MeV and 1.174 MeV beta- particles emitted to decay to 56Ba137m
	56Ba137m decays to 56Ba137 through release of 0.6617MeV gamma
*/ /////////////////////////////////////

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
	// use the particle gun	
	// TODO radioactive decay of cesium?
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

	// find properties of particle 
	// gamma 
	G4String particleName="gamma";
	G4ParticleDefinition *particle = particleTable->FindParticle("gamma");	

	// low energy beta
	//auto particle = G4ParticleTable::GetParticleTable()->FindParticle("e-");

	G4ThreeVector pos(0., 0., -50.0*cm);
	G4ThreeVector mom(0., 0., 1.);	// convention to create particle in z direction

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(661.7*keV);	// standard energy unit in Geant is MeV
	fParticleGun->SetParticleDefinition(particle);	// combine all the above to particle

	fParticleGun->GeneratePrimaryVertex(anEvent);	// generates one vertex (particle) for the event(?)

}
