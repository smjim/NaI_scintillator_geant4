#include "generator.hh"

// constructor
MyPrimaryGenerator::MyPrimaryGenerator() {
	fParticleGun = new G4ParticleGun(1); // # particles per event
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
	// -------------
	// Source from back
	// -------------
	/*
	// Source position (cm), match with construction.cc
	G4double source_pos = -50.0; 	// - is behind, + is in front (PMT side)
	fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., source_pos*cm));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));	
	*/

	// -------------
	// Source from side closest to PMT
	// -------------
	fParticleGun->SetParticlePosition(G4ThreeVector(20.0*cm, 0, 15.0*cm));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1., 0., 0.));	

	// -------------

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* beta = particleTable->FindParticle("e-");
	G4ParticleDefinition* gamma = particleTable->FindParticle("gamma");
	
	// Generate branching ratio
	double rand = G4UniformRand();

	switch (fMode) {
		case GeneratorMode::CsOnly:		// use gamma gun at 661.7 keV
			fParticleGun->SetParticleDefinition(gamma);
			fParticleGun->SetParticleEnergy(661.7*keV);	
	
			fParticleGun->GeneratePrimaryVertex(anEvent);

			break;

		case GeneratorMode::CsAndCo:	// use gamma gun at 661.7 keV, 1173 keV, 1332 keV (Cobalt-60 and Cesium-137)
			fParticleGun->SetParticleDefinition(gamma);
	
			if (rand < 0.5) {			// Cs-137
				fParticleGun->SetParticleEnergy(661.7*keV);	
				fParticleGun->GeneratePrimaryVertex(anEvent);
	
			} else if (rand < 0.9994) {	// Co-60
				fParticleGun->SetParticleEnergy(1173.2*keV);	
				fParticleGun->GeneratePrimaryVertex(anEvent);
	
				fParticleGun->SetParticleEnergy(1332.5*keV);	
				fParticleGun->GeneratePrimaryVertex(anEvent);
	
			} else {					// Co-60
				fParticleGun->SetParticleEnergy(1332.5*keV);	
				fParticleGun->GeneratePrimaryVertex(anEvent);
	
			}

			break;

		case GeneratorMode::CsDecay:	// simulate Cs-137 ion decay (isotropic emission)
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
	
			if (rand < 0.946) {	// 94.6% chance of 0.512 MeV beta, then 0.6617 MeV gamma
				// Cs-137 -> Ba-137m
				fParticleGun->SetParticleDefinition(beta);
				fParticleGun->SetParticleEnergy(0.512 * MeV);
				fParticleGun->SetParticleMomentumDirection(RandomIsotropicDirection());
				fParticleGun->GeneratePrimaryVertex(anEvent);
	
				// Ba-137m -> Ba-137
				fParticleGun->SetParticleDefinition(gamma);
				fParticleGun->SetParticleEnergy(0.6617 * MeV);
				fParticleGun->SetParticleMomentumDirection(RandomIsotropicDirection());
				fParticleGun->GeneratePrimaryVertex(anEvent);
	
			} else {			
				// 5.4% chance of 1.174 MeV beta
				// Cs-137 -> Ba-137
				fParticleGun->SetParticleDefinition(beta);
				fParticleGun->SetParticleEnergy(1.174 * MeV);
				fParticleGun->SetParticleMomentumDirection(RandomIsotropicDirection());
				fParticleGun->GeneratePrimaryVertex(anEvent);
			}

			break;
	}

}
