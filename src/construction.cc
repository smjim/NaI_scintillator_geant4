#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction() {

}

MyDetectorConstruction::~MyDetectorConstruction() {

}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
	G4NistManager *nist = G4NistManager::Instance(); 

	// ===================================================================
	// Material Properties
	// ===================================================================

	// ----------------------------------------
	// Material Properties of Scintillator (NaI (Tl)) 
	// ----------------------------------------
	G4Material* NaI = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
	G4MaterialPropertiesTable* mptNaI = new G4MaterialPropertiesTable();
	
	G4double energy[] = { 2.0*eV, 3.5*eV };		// Visible range
	G4double rindex[] = { 1.85, 1.85 };			// Approximate NaI index
	G4double scint[]  = { 1.0, 1.0 };			// Relative light yield
	G4double absorption[] = {20.0*cm, 20.0*cm};	// Absorption length in material
	G4double scintTimeConst = 250*ns;			// Typical decay time
	
	mptNaI->AddProperty("RINDEX", energy, rindex, 2);
	mptNaI->AddProperty("SCINTILLATIONCOMPONENT1", energy, scint, 2);
	mptNaI->AddProperty("ABSLENGTH", energy, absorption, 2);
	mptNaI->AddConstProperty("SCINTILLATIONYIELD", 38000./MeV);
	mptNaI->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptNaI->AddConstProperty("SCINTILLATIONTIMECONSTANT1", scintTimeConst);
	mptNaI->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
	NaI->SetMaterialPropertiesTable(mptNaI);

	// ----------------------------------------
	// Material properties of world volume (Air)
	// ----------------------------------------
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4double rindexWorld[2] = {1., 1.};
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	worldMat->SetMaterialPropertiesTable(mptWorld);

	// ----------------------------------------
	// Material properties of reflectix
	// ----------------------------------------
	G4Material* reflectixMat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
	G4MaterialPropertiesTable* mptReflectix = new G4MaterialPropertiesTable();
	G4double reflectivity[] = {0.98, 0.98};  // 98% reflectivity in visible range
	mptReflectix->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
	
	G4OpticalSurface* reflectixSurface = new G4OpticalSurface("ReflectixSurface");
	reflectixSurface->SetType(dielectric_dielectric);
	reflectixSurface->SetModel(unified);
	reflectixSurface->SetFinish(groundfrontpainted);
	reflectixSurface->SetMaterialPropertiesTable(mptReflectix);

	// ----------------------------------------
	// Material properties in PMT
	// ----------------------------------------
	G4Material* pmtMat = nist->FindOrBuildMaterial("G4_Pyrex_Glass");
	
	// Define optical surface between crystal and PMT
	G4OpticalSurface* pmtSurface = new G4OpticalSurface("PMTSurface");
	pmtSurface->SetType(dielectric_metal);
	pmtSurface->SetModel(unified);
	pmtSurface->SetFinish(polished);

	// Set photon detection efficiency (idealized for now)
	G4MaterialPropertiesTable* mptPMT = new G4MaterialPropertiesTable();
	G4double efficiency[] = {1.0, 1.0};  // 100% QE for testing
	mptPMT->AddProperty("EFFICIENCY", energy, efficiency, 2);
	pmtSurface->SetMaterialPropertiesTable(mptPMT);

	// ===================================================================
	// Construction and placement of objects
	// ===================================================================

	// ----------------------------------------
	// Simple box world volume 
	// ----------------------------------------
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	// ----------------------------------------
	// Scintillation crystal
	// ----------------------------------------
	G4Box* solidCrystal = new G4Box("solidCrystal", 5.6*cm/2, 10*cm/2, 43*cm/2);
	G4LogicalVolume* logicCrystal = new G4LogicalVolume(solidCrystal, NaI, "logicCrystal");
	G4VPhysicalVolume* physCrystal = new G4PVPlacement(
		0, G4ThreeVector(0., 0., 0.),
		logicCrystal, "physCrystal", logicWorld, false, 0, true);

	// ----------------------------------------
	// Reflectix lining of scintillation crystal
	// ----------------------------------------
	// Place a border surface between the crystal and the world volume to simulate reflective wrapping
	// Apply reflectixSurface to all six faces of the crystal (idealized)
	new G4LogicalBorderSurface("ReflectixBorder", physCrystal, physWorld, reflectixSurface);

	// ----------------------------------------
	// 2'' diameter PMT coupled to front of crystal
	// ----------------------------------------

	G4double pmtRadius = 2.54 * cm;  // 2-inch diameter
	G4double pmtThickness = 0.5 * cm;
	
	/*
	G4Tubs* solidPMT = new G4Tubs("solidPMT", 0., pmtRadius, pmtThickness / 2, 0., 360. * deg);
	G4LogicalVolume* logicPMT = new G4LogicalVolume(solidPMT, pmtMat, "logicPMT");
	*/
	
	// Place PMT just outside +z face of the crystal
	G4double crystalHalfZ = 43.0 * cm / 2;
	G4double pmtZ = crystalHalfZ + pmtThickness / 2;
	
	/*
	G4VPhysicalVolume* physPMT = new G4PVPlacement(
		0, G4ThreeVector(0., 0., pmtZ),
		logicPMT, "physPMT", logicWorld, false, 0, true);
	*/
	
	// Create optical surface between crystal and PMT
	/*
	new G4LogicalBorderSurface("CrystalPMTSurface", physCrystal, physPMT, pmtSurface);
	*/

	// Create detector at face of PMT
	// -------------
	G4Tubs* solidDetector = new G4Tubs("solidDetector", 0., pmtRadius, pmtThickness / 2, 0., 360. * deg);
	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(
		0, G4ThreeVector(0., 0., pmtZ), 
		logicDetector, "physDetector", logicWorld, false, 0, true);
	// -------------

	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	logicDetector->SetSensitiveDetector(sensDet);
}
