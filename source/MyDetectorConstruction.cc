#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{	
	G4NistManager *nist = G4NistManager::Instance();

// Define BC404

	G4Material *BC404 = new G4Material("BC404", 1.032*g/cm3, 2);
	BC404->AddElement(nist->FindOrBuildElement("C"),1000);
	BC404->AddElement(nist->FindOrBuildElement("H"),1100);
	G4double pDens = BC404->GetDensity()/(kg/mm3);

  //! Setting Birk's constant
  // BC404->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
  // BC404->GetIonisation()->SetBirksConstant(0.155*mm/MeV);
  BC404->GetIonisation()->SetBirksConstant(0.088*mm/MeV);

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

// Material for Scintillator

	G4Material *CsI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

// Material for PMT

	G4Material *matPMT = nist->FindOrBuildMaterial("G4_GLASS_PLATE");

// Cell_World
	
	G4double dWorld = 100.*cm;

	solidWorld = new G4Box("solidWorld", dWorld, dWorld, dWorld);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true); 

	G4double trapB = 4.0*RH/sqrt(3);

  G4RotationMatrix* rotY1 = new G4RotationMatrix();
  rotY1->rotateY(120.*deg);
  G4RotationMatrix* rotY2 = new G4RotationMatrix();
  rotY2->rotateY(-120.*deg);

//Al Box
  G4Box* solidAlBox = new G4Box("solidAlBox", 27.*cm, 2*RH+2.*cm, 27.*cm);
  G4LogicalVolume* logicAlBox = new G4LogicalVolume(solidAlBox, Al, "logicAlBox");
  // G4VPhysicalVolume* physAlBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicAlBox, "physAlBox", logicWorld, false, 0, true);

//Air Box
  G4Box* solidAirBox = new G4Box("solidAirBox", 25.*cm, 2*RH, 25.*cm);
  G4LogicalVolume* logicAirBox = new G4LogicalVolume(solidAirBox, worldMat, "logicAirBox");
  // G4VPhysicalVolume* physAirBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicAirBox, "physAirBox", logicAlBox, false, 0, true);

  G4Box* solidAlBox1 = new G4Box("solidAlBox1", 25.*cm, 1.*cm, 25.*cm);
	G4LogicalVolume *logicAlBox1 = new G4LogicalVolume(solidAlBox1, Al, "logicAlBox1");
	// G4VPhysicalVolume* physAlBox1 = new G4PVPlacement(0, G4ThreeVector(0., -(RH + 1.*cm), -((trapA/sin(60*deg)/2) + (HH+HC)/2)), logicAlBox1, "physAlBox1", logicWorld, false, 0, true);


  G4Box* solidAlBox2 = new G4Box("solidAlBox2", 25.*cm, 2.5*cm, 25.*cm);
	G4LogicalVolume *logicAlBox2 = new G4LogicalVolume(solidAlBox2, Al, "logicAlBox2");
	// G4VPhysicalVolume* physAlBox2 = new G4PVPlacement(0, G4ThreeVector(0., (RH + 2.5*cm) + 5*cm, -((trapA/sin(60*deg)/2) + (HH+HC)/2)), logicAlBox2, "physAlBox2", logicWorld, false, 0, true);

//! Source Steel Box
  G4Box* solidSourceSteelBox = new G4Box("solidSourceSteelBox", 10.*cm, 10.*cm, 10.*cm);
  G4LogicalVolume* logicSourceSteelBox = new G4LogicalVolume(solidSourceSteelBox, Steel, "logicSourceSteelBox");
  double zPar = 50.*cm;
  // G4VPhysicalVolume* physSourceSteelBox = new G4PVPlacement(0, G4ThreeVector(0., 0., -zPar), logicSourceSteelBox, "physSourceSteelBox", logicWorld, false, 0, true);

//! Source Air Box
  G4Box* solidSourceAirBox = new G4Box("solidSourceAirBox", (10.)*cm - 50.*um, (10.)*cm - 50.*um, (10.)*cm - 50.*um);
  G4LogicalVolume* logicSourceAirBox = new G4LogicalVolume(solidSourceAirBox, worldMat, "logicSourceAirBox");
  // G4VPhysicalVolume* physSourceAirBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicSourceAirBox, "physSourceAirBox", logicSourceSteelBox, false, 0, true);

//Source Al Sphere
  G4Sphere* solidSourceAlSphere = new G4Sphere("solidSourceAlSphere", 0.5*cm, 2.*cm, 0*degree, 360*degree, 0*degree, 360*degree);
  G4LogicalVolume* logicSourceAlSphere = new G4LogicalVolume(solidSourceAlSphere, Al, "logicSourceAlSphere");
  // G4VPhysicalVolume* physSourceAlSphere = new G4PVPlacement(0, G4ThreeVector(0., 0., -zPar), logicSourceAlSphere, "physSourceAlSphere", logicAirBox, false, 0, true);

// Module World
  G4double xMWorld = trapA;
  G4double yMWorld = RH;
  G4double zMWorld = (HH + HC)/2;

  G4Box* solidMWorld = new G4Box("solidMWorld", xMWorld, yMWorld, zMWorld);
  G4LogicalVolume* logicMWorld = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld");
  G4LogicalVolume* logicMWorld1 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld1");
  G4LogicalVolume* logicMWorld2 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld2");
  G4LogicalVolume* logicMWorld3 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld3");
  G4LogicalVolume* logicMWorld4 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld4");
  G4LogicalVolume* logicMWorld5 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld5");
  G4LogicalVolume* logicMWorld6 = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld6");

  G4double a = ((HH + HC)/2) / sin(60*deg);
  G4double triSide = 2*a + 2*trapA;
  G4double h = triSide *sin(60*deg);
  triSide = (h + (HH + HC)/2) / sin(60*deg);
  G4double b = triSide/4;
  h = (h + (HH + HC)/2)/2;

  G4VPhysicalVolume* physMWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicMWorld, "physMWorld", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld1 = new G4PVPlacement(0, G4ThreeVector(0., 2.*RH, 0.), logicMWorld1, "physMWorld1", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld2 = new G4PVPlacement(0, G4ThreeVector(0., -2.*RH, 0.), logicMWorld2, "physMWorld2", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld3 = new G4PVPlacement(0, G4ThreeVector((trapA+trapB)/2., RH, 0.), logicMWorld3, "physMWorld3", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld4 = new G4PVPlacement(0, G4ThreeVector(-(trapA+trapB)/2., -RH, 0.), logicMWorld4, "physMWorld4", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld5 = new G4PVPlacement(0, G4ThreeVector(-(trapA+trapB)/2., RH, 0.), logicMWorld5, "physMWorld5", logicWorld, false, 0, true);
  // G4VPhysicalVolume* physMWorld6 = new G4PVPlacement(0, G4ThreeVector((trapA+trapB)/2., -RH, 0.), logicMWorld6, "physMWorld6", logicWorld, false, 0, true);

// PMT
	// Scoring PMT
	G4Tubs *solidPMT = new G4Tubs("solidPMT", 0, RC, HC/2, 0.*deg, 360.*deg);
  G4LogicalVolume* logicPMT[7];
	logicPMT[0] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT");
	G4VPhysicalVolume *physPMT = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMT[0], "physPMT", logicMWorld, false, 0, true);

	// Left PMT
	logicPMT[1] = new G4LogicalVolume(solidPMT, matPMT, "logicPMT1");
	G4VPhysicalVolume *physPMT1 = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMT[1], "physPMT1", logicMWorld1, false, 0, true);

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
	G4Trd *solidScint1 = new G4Trd("solidScint1", trapB/2, trapA/2, HH/2, HH/2, RH/2);

	G4Trd *solidScint2 = new G4Trd("solidScint2", trapA/2, trapB/2, HH/2, HH/2, RH/2);

	G4RotationMatrix rotMatr1 = G4RotationMatrix();
  rotMatr1.rotateX(90.*deg);
  G4ThreeVector position1 = G4ThreeVector(0., -RH/2, 0.);

  G4RotationMatrix rotMatr2 = G4RotationMatrix();
  rotMatr2.rotateX(90.*deg);
  G4ThreeVector position2 = G4ThreeVector(0., RH/2, 0.);
  
  G4Transform3D tr1 = G4Transform3D(rotMatr1, position1);
  G4Transform3D tr2 = G4Transform3D(rotMatr2, position2);

G4MultiUnion* solidScint = new G4MultiUnion("solidScint");

  solidScint->AddNode(*solidScint1, tr1);
  solidScint->AddNode(*solidScint2, tr2);
  solidScint->Voxelize();
	// Scoring Scintillator
  G4LogicalVolume* logicScint[7];
	logicScint[0] = new G4LogicalVolume(solidScint, BC404, "logicScint");
	G4VPhysicalVolume *physScint = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint[0], "physScint", logicMWorld, false, 0, true);
	
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
