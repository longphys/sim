#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{	
	G4NistManager *nist = G4NistManager::Instance();

// Define BC404

  G4Material *BC404 = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	// G4Material *BC404 = new G4Material("BC404", 1.032*g/cm3, 2);
	// BC404->AddElementByNumberOfAtoms(nist->FindOrBuildElement("C"),9);
	// BC404->AddElementByNumberOfAtoms(nist->FindOrBuildElement("H"),10);
	// BC404->AddElement(nist->FindOrBuildElement("C"),1000);
	// BC404->AddElement(nist->FindOrBuildElement("H"),1100);
	G4double pDens = BC404->GetDensity()/(kg/mm3);

  BC404->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

// Define Lead

	G4Material *Lead = nist->FindOrBuildMaterial("G4_Pb");

  G4Material *Al = nist->FindOrBuildMaterial("G4_Al");

// Material for Steel

	G4Material *Steel = new G4Material("Steel", 8.*g/cm3, 9);
	Steel->AddElement(nist->FindOrBuildElement("C"),0.07*perCent);
	Steel->AddElement(nist->FindOrBuildElement("Cr"),18.*perCent);
	Steel->AddElement(nist->FindOrBuildElement("Mn"),2.*perCent);
	Steel->AddElement(nist->FindOrBuildElement("Si"),1.*perCent);
	Steel->AddElement(nist->FindOrBuildElement("P"),0.045*perCent);
	Steel->AddElement(nist->FindOrBuildElement("S"),0.015*perCent);
	Steel->AddElement(nist->FindOrBuildElement("Ni"),9.*perCent);
	Steel->AddElement(nist->FindOrBuildElement("N"),0.1*perCent);
	Steel->AddElement(nist->FindOrBuildElement("Fe"),69.77*perCent);
	G4double sDens = Steel->GetDensity()/(kg/mm3);

// Material for World

	G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
	// G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

// Material for Scintillator

	G4Material *CsI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

// Material for PMT

	G4Material *matPMT = nist->FindOrBuildMaterial("G4_GLASS_PLATE");

// Cell_World
	
	G4double dWorld = 100.*cm;

	solidWorld = new G4Box("solidWorld", dWorld, dWorld, dWorld);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true); 

  G4RotationMatrix* rotY1 = new G4RotationMatrix();
  rotY1->rotateY(120.*deg);
  G4RotationMatrix* rotY2 = new G4RotationMatrix();
  rotY2->rotateY(-120.*deg);

//Al Box
  // G4Box* solidAlBox = new G4Box("solidAlBox", 18.*cm, 20.*cm, 52.*cm);
  // G4LogicalVolume* logicAlBox = new G4LogicalVolume(solidAlBox, Al, "logicAlBox");
  // G4VPhysicalVolume* physAlBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicAlBox, "physAlBox", logicWorld, false, 0, true);

//Air Box
  // G4Box* solidAirBox = new G4Box("solidAirBox", 15.*cm, 17.*cm, 50.*cm);
  // G4LogicalVolume* logicAirBox = new G4LogicalVolume(solidAirBox, worldMat, "logicAirBox");
  // G4VPhysicalVolume* physAirBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicAirBox, "physAirBox", logicAlBox, false, 0, true);

// Module World
  // G4double xMWorld = trapB_mylar/2;
  // G4double yMWorld = h_mylar;
  // G4double zMWorld = (HH + HC)/2 + mylar_thickness;

  G4double xMWorld = trapB_mylar/2 + tape_thickness;
  G4double yMWorld = h_mylar + tape_thickness;
  G4double zMWorld = (HH + HC)/2 + mylar_thickness + tape_thickness;

  G4Box* solidMWorld = new G4Box("solidMWorld", xMWorld, yMWorld, zMWorld);
  G4LogicalVolume* logicMWorld = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld");
  G4LogicalVolume* logicMWorld1 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld1");
  G4LogicalVolume* logicMWorld2 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld2");
  G4LogicalVolume* logicMWorld3 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld3");
  G4LogicalVolume* logicMWorld4 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld4");
  G4LogicalVolume* logicMWorld5 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld5");
  G4LogicalVolume* logicMWorld6 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld6");

	G4RotationMatrix* rotMWorld = new G4RotationMatrix();
  rotMWorld->rotateX(0.*deg);
  // rotMWorld->rotateX(-15.*deg);
  G4VPhysicalVolume* physMWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicMWorld, "physMWorld", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld = new G4PVPlacement(rotMWorld, G4ThreeVector(0., 1.0*cm, 0.), logicMWorld, "physMWorld", logicWorld, false, 0, true);

  // G4VPhysicalVolume* physMWorld1 = new G4PVPlacement(0, G4ThreeVector(0., 2.*h_mylar, 0.), logicMWorld1, "physMWorld1", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld2 = new G4PVPlacement(0, G4ThreeVector(0., -2.*h, 0.), logicMWorld2, "physMWorld2", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld3 = new G4PVPlacement(0, G4ThreeVector((trapA+trapB)/2., h, 0.), logicMWorld3, "physMWorld3", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld4 = new G4PVPlacement(0, G4ThreeVector(-(trapA+trapB)/2., -h, 0.), logicMWorld4, "physMWorld4", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld5 = new G4PVPlacement(0, G4ThreeVector(-(trapA+trapB)/2., h, 0.), logicMWorld5, "physMWorld5", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld6 = new G4PVPlacement(0, G4ThreeVector((trapA+trapB)/2., -h, 0.), logicMWorld6, "physMWorld6", logicWorld, false, 0, true);

// PMT
	// Scoring PMT
	G4Tubs *solidPMT = new G4Tubs("solidPMT", 0, RC, HC/2, 0.*deg, 360.*deg);
  G4LogicalVolume* logicPMT[7];
	logicPMT[0] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT");
	G4VPhysicalVolume *physPMT = new G4PVPlacement(0, G4ThreeVector(0., 0., HH_mylar/2), logicPMT[0], "physPMT", logicMWorld, false, 0, true);
	// G4VPhysicalVolume *physPMT = new G4PVPlacement(0, G4ThreeVector(0., 0., HH_mylar/2+tape_thickness), logicPMT[0], "physPMT", logicMWorld, false, 0, true);

	// Left PMT
	logicPMT[1] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT1");
	G4VPhysicalVolume *physPMT1 = new G4PVPlacement(0, G4ThreeVector(0., 0., HH_mylar/2), logicPMT[1], "physPMT1", logicMWorld1, false, 0, true);

	// Right PMT
	logicPMT[2] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT2");
	G4VPhysicalVolume *physPMT2 = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMT[2], "physPMT2", logicMWorld2, false, 0, true);
		
	logicPMT[3] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT3");
	G4VPhysicalVolume *physPMT3 = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMT[3], "physPMT3", logicMWorld3, false, 0, true);

	logicPMT[4] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT4");
	G4VPhysicalVolume *physPMT4 = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMT[4], "physPMT4", logicMWorld4, false, 0, true);

	logicPMT[5] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT5");
	G4VPhysicalVolume *physPMT5 = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMT[5], "physPMT5", logicMWorld5, false, 0, true);

	logicPMT[6] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT6");
	G4VPhysicalVolume *physPMT6 = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMT[6], "physPMT6", logicMWorld6, false, 0, true);

// Scintillator
	G4Trd *solidScint1 = new G4Trd("solidScint1", trapB/2, trapA/2, HH/2, HH/2, h/2);

	G4Trd *solidScint2 = new G4Trd("solidScint2", trapA/2, trapB/2, HH/2, HH/2, h/2);

	G4RotationMatrix rotMatr1 = G4RotationMatrix();
  rotMatr1.rotateX(90.*deg);
  G4ThreeVector position1 = G4ThreeVector(0., -h/2, 0.);

  G4RotationMatrix rotMatr2 = G4RotationMatrix();
  rotMatr2.rotateX(90.*deg);
  G4ThreeVector position2 = G4ThreeVector(0., h/2, 0.);
  
  G4Transform3D tr1 = G4Transform3D(rotMatr1, position1);
  G4Transform3D tr2 = G4Transform3D(rotMatr2, position2);

G4MultiUnion* solidScint = new G4MultiUnion("solidScint");

  solidScint->AddNode(*solidScint1, tr1);
  solidScint->AddNode(*solidScint2, tr2);
  solidScint->Voxelize();

// G4Tubs *solidScint = new G4Tubs("solidtest", 0, RH, HH/2, 0.*deg, 360.*deg);
// G4Tubs *solidtest = new G4Tubs("solidtest", 0, RH, HH/2, 0.*deg, 360.*deg);
// G4LogicalVolume* logictest = new G4LogicalVolume(solidtest, BC404, "logictest");
// G4VPhysicalVolume *phystest = new G4PVPlacement(0, G4ThreeVector(0., 0., -(HH+HC/2.)), logictest, "physScint", logicWorld, false, 0, true);

//! outer mylar
	G4Trd *solidMylar1 = new G4Trd("solidMylar1", trapB_mylar/2, trapA_mylar/2, HH_mylar/2, HH_mylar/2, h_mylar/2);

	G4Trd *solidMylar2 = new G4Trd("solidMylar2", trapA_mylar/2, trapB_mylar/2, HH_mylar/2, HH_mylar/2, h_mylar/2);

  G4ThreeVector position1_Mylar = G4ThreeVector(0., -h_mylar/2, 0.);

  G4ThreeVector position2_Mylar = G4ThreeVector(0., h_mylar/2, 0.);
  
  G4Transform3D tr1_Mylar = G4Transform3D(rotMatr1, position1_Mylar);
  G4Transform3D tr2_Mylar = G4Transform3D(rotMatr2, position2_Mylar);

G4MultiUnion* solidMylar = new G4MultiUnion("solidMylar");

  solidMylar->AddNode(*solidMylar1, tr1_Mylar);
  solidMylar->AddNode(*solidMylar2, tr2_Mylar);
  solidMylar->Voxelize();

  G4Material* mylar = nist->FindOrBuildMaterial("G4_MYLAR");
  G4Material* pet = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* aluminium = nist->FindOrBuildMaterial("G4_Al");
  G4Material* vinyl2 = nist->FindOrBuildMaterial("G4_POLYVINYLIDENE_CHLORIDE");
  G4SubtractionSolid* solidMylar_subtracted = new G4SubtractionSolid("solidMylar_subtracted", solidMylar, solidScint);
	G4LogicalVolume* logicMylar = new G4LogicalVolume(solidMylar_subtracted, mylar, "logicMylar");
	G4VPhysicalVolume *physMylar = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicMylar, "physMylar", logicMWorld, false, 0, true);
	// G4LogicalVolume* logicMylar1 = new G4LogicalVolume(solidMylar_subtracted, mylar, "logicMylar1");
	// G4VPhysicalVolume *physMylar1 = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicMylar1, "physMylar1", logicMWorld1, false, 0, true);
  
//! outer tape
	G4Trd *solidTape1 = new G4Trd("solidTape1", trapB_tape/2, trapA_tape/2, HH_tape/2, HH_tape/2, h_tape/2);

	G4Trd *solidTape2 = new G4Trd("solidTape2", trapA_tape/2, trapB_tape/2, HH_tape/2, HH_tape/2, h_tape/2);

  G4ThreeVector position1_tape = G4ThreeVector(0., -h_tape/2, 0.);

  G4ThreeVector position2_tape = G4ThreeVector(0., h_tape/2, 0.);
  
  G4Transform3D tr1_tape = G4Transform3D(rotMatr1, position1_tape);
  G4Transform3D tr2_tape = G4Transform3D(rotMatr2, position2_tape);

G4MultiUnion* solidTape = new G4MultiUnion("solidTape");

  solidTape->AddNode(*solidTape1, tr1_tape);
  solidTape->AddNode(*solidTape2, tr2_tape);
  solidTape->Voxelize();

  G4Material* vinyl = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
  G4SubtractionSolid* solidTape_subtracted = new G4SubtractionSolid("solidTape_subtracted", solidTape, solidMylar);
	G4LogicalVolume* logicTape = new G4LogicalVolume(solidTape_subtracted, vinyl, "logicTape");
	// G4VPhysicalVolume *physTape = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicTape, "physTape", logicMWorld, false, 0, true);
  
//! steel surface
  G4Box* solidSurface = new G4Box("solidSurface", trapB_tape/2, h, surfaceThickness/2);
	G4LogicalVolume* logicSurface = new G4LogicalVolume(solidSurface, Steel, "logicSurface");

	const MyPrimaryGenerator* primaryGenerator
  	= static_cast<const MyPrimaryGenerator*>
  	(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  const G4double dis_from_surface = 4.4*cm;
	const G4double zSurface = 37.*cm;
  G4double zPar = zSurface + dis_from_surface;

  G4VPhysicalVolume *physSurface = new G4PVPlacement(0, G4ThreeVector(0., 0., -(zSurface + (HH+HC)/2 + solidSurface->GetZHalfLength())), logicSurface, "physSurface", logicWorld, false, 0, true);

	// Scoring Scintillator
  G4LogicalVolume* logicScint[7];
	logicScint[0] = new G4LogicalVolume(solidScint, BC404, "logicScint");
	// logicScint[0] = new G4LogicalVolume(solidScint, worldMat, "logicScint");
	// logicScint[0] = new G4LogicalVolume(solidScint, Lead, "logicScint");
	G4VPhysicalVolume *physScint = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint[0], "physScint", logicMWorld, false, 0, true);
	
  // G4double maxStep = 0.5*mm;
  G4double maxStep = std::min(tape_thickness, mylar_thickness)/10;
  G4UserLimits* myStepLimit = new G4UserLimits(100*nm);
  // logicSurface->SetUserLimits(myStepLimit);
  // logicScint[0]->SetUserLimits(myStepLimit);
  
	logicScint[1] = new G4LogicalVolume(solidScint, BC404, "logicScint1");
	G4VPhysicalVolume *physScint1 = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint[1], "physScint1", logicMWorld1, false, 0, true);
	
	//Right Scintillator
	logicScint[2] = new G4LogicalVolume(solidScint, BC404, "logicScint2");
	G4VPhysicalVolume *physScint2 = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint[2], "physScint2", logicMWorld2, false, 0, true);

	logicScint[3] = new G4LogicalVolume(solidScint, BC404, "logicScint3");
	G4VPhysicalVolume *physScint3 = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint[3], "physScint3", logicMWorld3, false, 0, true);

	logicScint[4] = new G4LogicalVolume(solidScint, BC404, "logicScint4");
	G4VPhysicalVolume *physScint4 = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint[4], "physScint4", logicMWorld4, false, 0, true);

	logicScint[5] = new G4LogicalVolume(solidScint, BC404, "logicScint5");
	G4VPhysicalVolume *physScint5 = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint[5], "physScint5", logicMWorld5, false, 0, true);

	logicScint[6] = new G4LogicalVolume(solidScint, BC404, "logicScint6");
	G4VPhysicalVolume *physScint6 = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint[6], "physScint6", logicMWorld6, false, 0, true);
	
  //! Air gap
  // G4ThreeVector physSurface_translation = physSurface->GetTranslation();
  // G4Tubs* solidAirgap = new G4Tubs("solidAirgap", 0, RH+5*cm, physSurface_translation.getZ() - , 0.*deg, 360.*deg);

  //Plastic Box
	G4double bHeight = 4*RH;
	G4double bWidth = 4*RH;
	G4double pBoxDepth = (1/pDens)/(bHeight*bWidth);

	solidPBox = new G4Box("solidPBox", pBoxDepth/2., bWidth/2., bHeight/2.);
	G4LogicalVolume *logicPBox = new G4LogicalVolume(solidPBox, matPMT, "logicPBox");
	// physPBox = new G4PVPlacement(0, G4ThreeVector(-(trapA + pBoxDepth/2.), 0., 0.), logicPBox, "physPBox", logicWorld, false, 0, true);

	//Steel Box
	G4double sBoxDepth = (1/sDens)/(bHeight*bWidth);

  solidSBox = new G4Box("solidSBox", sBoxDepth/2., bWidth/2., bHeight/2.);
	G4LogicalVolume *logicSBox = new G4LogicalVolume(solidSBox, Steel, "logicSBox");
	// G4VPhysicalVolume *physSBox = new G4PVPlacement(0, G4ThreeVector(-(trapA + pBoxDepth + sBoxDepth/2.), 0., 0.), logicSBox, "physSBox", logicWorld, false, 0, true);

  G4double yAl = 5.*mm;

  G4Box* solidAlStick = new G4Box("AlStick", xMWorld, yAl, zMWorld);
	G4LogicalVolume* logicAlStick = new G4LogicalVolume(solidAlStick, Al, "logicAlStick");
	// G4VPhysicalVolume* physAlStick = new G4PVPlacement(0, G4ThreeVector(0., -(yMWorld + yAl), 0.), logicAlStick, "physAlStick", logicWorld, false, 0, true);

// Select scoring volume
for(int i = 0; i <= 6; i++){
	fDEScoringVolume[i] = logicScint[i];
	fEScoringVolume[i] = logicPMT[i];
  }
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct() 
{
	return physWorld;
}
