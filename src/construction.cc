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

	G4Material* NaI = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

	// Optional: add scintillation properties
	G4MaterialPropertiesTable* mptNaI = new G4MaterialPropertiesTable();
	
	G4double energy[] = { 2.0*eV, 3.5*eV };		// Visible range
	G4double rindex[] = { 1.85, 1.85 };			// Approximate NaI index
	G4double scint[]  = { 1.0, 1.0 };			// Relative light yield
	G4double absorption[] = {1.0*cm, 1.0*cm};	// Absorption length in material
	G4double scintTimeConst = 250*ns;			// Typical decay time
	
	mptNaI->AddProperty("RINDEX", energy, rindex, 2);
	mptNaI->AddProperty("SCINTILLATIONCOMPONENT1", energy, scint, 2);
	mptNaI->AddProperty("ABSLENGTH", energy, absorption, 2);
	mptNaI->AddConstProperty("SCINTILLATIONYIELD", 1000./MeV);	// for testing
	//mptNaI->AddConstProperty("SCINTILLATIONYIELD", 38000./MeV);
	mptNaI->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptNaI->AddConstProperty("SCINTILLATIONTIMECONSTANT1", scintTimeConst);
	mptNaI->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
	
	NaI->SetMaterialPropertiesTable(mptNaI);

	// Ex. air:
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4double rindexWorld[2] = {1., 1.};

	// Create another material properties table so that the photons can transmit outside the cherenkov box
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

	worldMat->SetMaterialPropertiesTable(mptWorld);

	// Simple box world volume 
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	// Scintillation crystal
	G4Box* solidCrystal = new G4Box("solidCrystal", 5.6*cm/2, 10*cm/2, 43*cm/2);
	G4LogicalVolume* logicCrystal = new G4LogicalVolume(solidCrystal, NaI, "logicCrystal");
	new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicCrystal, "physCrystal", logicWorld, false, 0, true);

	// Reflectix lining of scintillation crystal
	// TODO reflectix 0.98 reflection?

	// Detectors
	// TODO change this to a singular PMT mounted on the +z end of the crystal with diameter 2 inches
	// make the PMT very realistic?
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
}

void MyDetectorConstruction::ConstructSDandField() {
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);
}
