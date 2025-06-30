#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction() {

}

MyDetectorConstruction::~MyDetectorConstruction() {

}

// All the physics processes occur within the boundary defined by worldvolume
// It is returned at the end as the result of the simulation
G4VPhysicalVolume *MyDetectorConstruction::Construct() {
	// Use this to implement parameters which are predefined for different materials
	G4NistManager *nist = G4NistManager::Instance(); 

	// Ex. aerogel detector:
	// Params: <name>, <density>, <#components>
	G4Material *SiO2 = new G4Material("SiO2", 2.2021*g/cm3, 2);
	SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
	SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

	// Ex. water:
	G4Material *H2O = new G4Material("H2O", 1.*g/cm3, 2);
	H2O->AddElement(nist->FindOrBuildElement("H"), 2);
	H2O->AddElement(nist->FindOrBuildElement("O"), 1);

	// Ex. carbon:
	G4Element *C = nist->FindOrBuildElement("C");

	// Ex. aerogel: 
	G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement(C, 0.1*perCent);

	// tell geant4 what is the refractive index for a specific photon momentum:
	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};	// blue vs red light
	//G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};	// this is the order from tutorial, but outputs error message that energies should be in increasing order
	G4double rindexAerogel[2] = {1.1, 1.1};	// between 1.05 and 1.2, approximately constant
	G4double rindexWorld[2] = {1., 1.};	

	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);	// refractive index

	Aerogel->SetMaterialPropertiesTable(mptAerogel);

	// Ex. air:
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

	// Create another material properties table so that the photons can transmit outside the cherenkov box
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

	worldMat->SetMaterialPropertiesTable(mptWorld);

	// Simple world volume example: a box
	// arguments: <name>, <1/2 size x>, <1/2 size y>, <1/2 size z> 
	// standard size in Geant is mm, so specify m
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);

	// Need to insert material into the world volume:
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

	// Need to create physical volume:
	// parameters: <rotation>, <position>, <logical volume>, <name for phys volume>, <mother volume - if nesting>, boolean if you want to do that, copy number(?), whether it should check for overlaps (give warning)
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	// Make the detector box (aerogel)
	G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
	G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
	G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true); 

	G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);
	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
	// Creating array of sensitive detectors is slightly more tricky:
	// you have to specify the position as a function of i, j, and also the detector number
	for (G4int i = 0; i < 100; i++) {
		for (G4int j = 0; j < 100; j++) {
			G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m + (i+0.5)*m/100, -0.5*m + (j+0.5)*m/100, (0.5-0.01)*m), logicDetector, "physDetector", logicWorld, false, j+i*100, true);
		} 
	}

	return physWorld;
	// if you want to create more detector parts, place inside world volume
	// if you want to create another mother volume you need another daughter volume
}

void MyDetectorConstruction::ConstructSDandField() {
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);
}
