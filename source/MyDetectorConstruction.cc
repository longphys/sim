#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{	
	G4NistManager *nist = G4NistManager::Instance();

// Define BC404

	G4Material *BC404 = new G4Material("BC404", 1.032*g/cm3, 2);
	BC404->AddElement(nist->FindOrBuildElement("C"),1000);
	BC404->AddElement(nist->FindOrBuildElement("H"),1100);
	G4double pDens = BC404->GetDensity()/(kg/mm3);

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

	G4Material *matScint = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

// Material for PMT

	G4Material *matPMT = nist->FindOrBuildMaterial("G4_GLASS_PLATE");

// Cell_World
	
	G4double dWorld = 40.*cm;

	solidWorld = new G4Box("solidWorld", dWorld, dWorld, dWorld);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true); 

	G4double trapB = 4.0*RH/sqrt(3);
	G4double RC = 78*mm/2;
	G4double HC = 15*mm;

  G4RotationMatrix* rotY1 = new G4RotationMatrix();
  rotY1->rotateY(120.*deg);
  G4RotationMatrix* rotY2 = new G4RotationMatrix();
  rotY2->rotateY(-120.*deg);

//Al Box
  G4Box* solidAlBox = new G4Box("solidAlBox", 27.*cm, 2*RH+2.*cm, 27.*cm);
  G4LogicalVolume* logicAlBox = new G4LogicalVolume(solidAlBox, Al, "logicAlBox");
  G4VPhysicalVolume* physAlBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicAlBox, "physAlBox", logicWorld, false, 0, true);

//Air Box
  G4Box* solidAirBox = new G4Box("solidAirBox", 25.*cm, 2*RH, 25.*cm);
  G4LogicalVolume* logicAirBox = new G4LogicalVolume(solidAirBox, worldMat, "logicAirBox");
  G4VPhysicalVolume* physAirBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicAirBox, "physAirBox", logicAlBox, false, 0, true);

  G4Box* solidAlBox1 = new G4Box("solidAlBox1", 25.*cm, 1.*cm, 25.*cm);
	G4LogicalVolume *logicAlBox1 = new G4LogicalVolume(solidAlBox1, Al, "logicAlBox1");
	// G4VPhysicalVolume* physAlBox1 = new G4PVPlacement(0, G4ThreeVector(0., -(RH + 1.*cm), -((trapA/sin(60*deg)/2) + (HH+HC)/2)), logicAlBox1, "physAlBox1", logicWorld, false, 0, true);


  G4Box* solidAlBox2 = new G4Box("solidAlBox2", 25.*cm, 2.5*cm, 25.*cm);
	G4LogicalVolume *logicAlBox2 = new G4LogicalVolume(solidAlBox2, Al, "logicAlBox2");
	// G4VPhysicalVolume* physAlBox2 = new G4PVPlacement(0, G4ThreeVector(0., (RH + 2.5*cm) + 5*cm, -((trapA/sin(60*deg)/2) + (HH+HC)/2)), logicAlBox2, "physAlBox2", logicWorld, false, 0, true);

//Source Al Box
  G4Box* solidSourceAlBox = new G4Box("solidSourceAlBox", 2.*cm, 2.*cm, 2.*cm);
  G4LogicalVolume* logicSourceAlBox = new G4LogicalVolume(solidSourceAlBox, Al, "logicSourceAlBox");
  double zPar = (trapA/sin(60*deg)/2) + (HH+HC)/2;
  // G4VPhysicalVolume* physSourceAlBox = new G4PVPlacement(0, G4ThreeVector(0., 0., -zPar), logicSourceAlBox, "physSourceAlBox", logicAirBox, false, 0, true);

//Source Air Box
  G4Box* solidSourceAirBox = new G4Box("solidSourceAirBox", 0.5*cm, 0.5*cm, 0.5*cm);
  G4LogicalVolume* logicSourceAirBox = new G4LogicalVolume(solidSourceAirBox, worldMat, "logicSourceAirBox");
  // G4VPhysicalVolume* physSourceAirBox = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicSourceAirBox, "physSourceAirBox", logicSourceAlBox, false, 0, true);

// Module World
  G4double xMWorld = trapA;
  G4double yMWorld = RH;
  G4double zMWorld = (HH + HC)/2;

  G4Box* solidMWorld = new G4Box("solidMWorld", xMWorld, yMWorld, zMWorld);
  G4LogicalVolume* logicMWorld = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorld");
  G4LogicalVolume* logicMWorldL = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorldL");
  G4LogicalVolume* logicMWorldR = new G4LogicalVolume(solidMWorld, worldMat, "logicMWorldR");

  G4double a = ((HH + HC)/2) / sin(60*deg);
  G4double triSide = 2*a + 2*trapA;
  G4double h = triSide *sin(60*deg);
  triSide = (h + (HH + HC)/2) / sin(60*deg);
  G4double b = triSide/4;
  h = (h + (HH + HC)/2)/2;
  G4VPhysicalVolume* physMWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0), logicMWorld, "physMWorld", logicAirBox, false, 0, true);
  G4VPhysicalVolume* physMWorldL = new G4PVPlacement(rotY1, G4ThreeVector(-b, 0., -h), logicMWorldL, "physMWorldL", logicAirBox, false, 0, true);
  G4VPhysicalVolume* physMWorldR = new G4PVPlacement(rotY2, G4ThreeVector(b, 0., -h), logicMWorldR, "physMWorldR", logicAirBox, false, 0, true);

// PMT
	// Scoring PMT
	G4Tubs *solidPMT = new G4Tubs("solidPMT", 0, RC, HC/2, 0.*deg, 360.*deg);
	G4LogicalVolume *logicPMT = new G4LogicalVolume(solidPMT, matPMT, "logicPMT");
	G4VPhysicalVolume *physPMT = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMT, "physPMT", logicMWorld, false, 0, true);

	// Left PMT
	G4LogicalVolume *logicPMTL = new G4LogicalVolume(solidPMT, matPMT, "logicPMTL");
	G4VPhysicalVolume *physPMTL = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMTL, "physPMTL", logicMWorldL, false, 0, true);

	// Right PMT
	G4LogicalVolume *logicPMTR = new G4LogicalVolume(solidPMT, matPMT, "logicPMTR");
	G4VPhysicalVolume *physPMTR = new G4PVPlacement(0, G4ThreeVector(0., 0., HH/2), logicPMTR, "physPMTR", logicMWorldR, false, 0, true);
		
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
	G4LogicalVolume *logicScint = new G4LogicalVolume(solidScint, BC404, "logicScint");
	G4VPhysicalVolume *physScint = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScint, "physScint", logicMWorld, false, 0, true);
	
	//Left Scintillator
	G4LogicalVolume *logicScintL = new G4LogicalVolume(solidScint, BC404, "logicScintL");
	G4VPhysicalVolume *physScintL = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScintL, "physScintL", logicMWorldL, false, 0, true);
	
	//Right Scintillator
	G4LogicalVolume *logicScintR = new G4LogicalVolume(solidScint, BC404, "logicScintR");
	G4VPhysicalVolume *physScintR = new G4PVPlacement(0, G4ThreeVector(0., 0., -HC/2.), logicScintR, "physScintR", logicMWorldR, false, 0, true);

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

// Select scoring volume
	fDEScoringVolume = logicScint;
	fDEScoringVolumeL = logicScintL;
	fDEScoringVolumeR = logicScintR;
	
	fEScoringVolume = logicPMT;
	fEScoringVolumeL = logicPMTL;
	fEScoringVolumeR = logicPMTR;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct() 
{
	return physWorld;
}
