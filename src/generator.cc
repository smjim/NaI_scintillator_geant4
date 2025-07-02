#include "generator.hh"

// constructor
MyPrimaryGenerator::MyPrimaryGenerator() {
	fParticleGun = new G4ParticleGun(1000); // # particles per event
}

// destructor
MyPrimaryGenerator::~MyPrimaryGenerator() {
	delete fParticleGun;
}

G4ThreeVector MyPrimaryGenerator::RandomIsotropicDirection() {
	double cosTheta = 2.*G4UniformRand() - 1.;
	double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
	double phi = 2.*CLHEP::pi*G4UniformRand();
	double x = sinTheta * std::cos(phi);
	double y = sinTheta * std::sin(phi);
	double z = cosTheta;
	return G4ThreeVector(x,y,z);
}

/* /////////////////////////////////////
	For 55Cs137 decay, 0.512 MeV and 1.174 MeV beta- particles emitted to decay to 56Ba137m
	56Ba137m decays to 56Ba137 through release of 0.6617MeV gamma
*/ /////////////////////////////////////

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
	if (useDecay) {	// simulate Cs-137 ion decay
		// Simulate the Cs atom sitting there
		/*	
		G4IonTable* ionTable = G4ParticleTable::GetParticleTable()->GetIonTable();
		G4ParticleDefinition* ion = ionTable->GetIon(55, 137, 0.*keV);	// Cs 137 (Last parameter in particle definition is internal excitation)
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleEnergy(0.*keV);
		fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -50.0*cm));
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));	// if particle has 0 kinetic energy (stationary 137Cs) then this momentum direction is irrelevant
		fParticleGun->GeneratePrimaryVertex(anEvent);
		*/

		// Manually simulate the decay processes associated with Cs-137
		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* beta = particleTable->FindParticle("e-");
		G4ParticleDefinition* gamma = particleTable->FindParticle("gamma");

		// Source position
		G4ThreeVector sourcePos(0., 0., -50.0*cm);

		// Generate branching ratio
		double rand = G4UniformRand();
		if (rand < 0.946) {	// 94.6% chance of 0.512 MeV beta, then 0.6617 MeV gamma
				// Cs-137 -> Ba-137m
				fParticleGun->SetParticleDefinition(beta);
				fParticleGun->SetParticleEnergy(0.512 * MeV);
				fParticleGun->SetParticlePosition(sourcePos);
				fParticleGun->SetParticleMomentumDirection(RandomIsotropicDirection());
				fParticleGun->GeneratePrimaryVertex(anEvent);

				// Ba-137m -> Ba-137
				fParticleGun->SetParticleDefinition(gamma);
				fParticleGun->SetParticleEnergy(0.6617 * MeV);
				fParticleGun->SetParticlePosition(sourcePos);
				fParticleGun->SetParticleMomentumDirection(RandomIsotropicDirection());
				fParticleGun->GeneratePrimaryVertex(anEvent);

		} else {			// 5.4% chance of 1.174 MeV beta
				// Cs-137 -> Ba-137
				fParticleGun->SetParticleDefinition(beta);
				fParticleGun->SetParticleEnergy(1.174 * MeV);
				fParticleGun->SetParticlePosition(sourcePos);
				fParticleGun->SetParticleMomentumDirection(RandomIsotropicDirection());
				fParticleGun->GeneratePrimaryVertex(anEvent);
		}

	} else {		// use gamma gun at 661.7 keV
		G4ParticleDefinition *gamma = G4ParticleTable::GetParticleTable()->FindParticle("gamma");	
		fParticleGun->SetParticleDefinition(gamma);
		fParticleGun->SetParticleEnergy(661.7*keV);	
		fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -50.0*cm));
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));	
		fParticleGun->GeneratePrimaryVertex(anEvent);
	}

}
