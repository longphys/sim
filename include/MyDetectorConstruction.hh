#ifndef MyDetectorConstruction_hh
#define MyDetectorConstruction_hh
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Sphere.hh"
#include "G4MultiUnion.hh"
#include "G4UnionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public: // public to all classes
	MyDetectorConstruction();
	
	virtual ~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
	// Main function to construct geometry
	G4LogicalVolume* GetScoringVolumeDE() const { return fDEScoringVolume; }
	G4LogicalVolume* GetScoringVolumeDE1() const { return fDEScoringVolume1; }
	G4LogicalVolume* GetScoringVolumeDE2() const { return fDEScoringVolume2; }
	G4LogicalVolume* GetScoringVolumeDE3() const { return fDEScoringVolume3; }
	G4LogicalVolume* GetScoringVolumeDE4() const { return fDEScoringVolume4; }
	G4LogicalVolume* GetScoringVolumeDE5() const { return fDEScoringVolume5; }
	G4LogicalVolume* GetScoringVolumeDE6() const { return fDEScoringVolume6; }

	G4LogicalVolume* GetScoringVolumeE() const { return fEScoringVolume; }
	G4LogicalVolume* GetScoringVolumeE1() const { return fEScoringVolume1; }
	G4LogicalVolume* GetScoringVolumeE2() const { return fEScoringVolume2; }
	G4LogicalVolume* GetScoringVolumeE3() const { return fEScoringVolume3; }
	G4LogicalVolume* GetScoringVolumeE4() const { return fEScoringVolume4; }
	G4LogicalVolume* GetScoringVolumeE5() const { return fEScoringVolume5; }
	G4LogicalVolume* GetScoringVolumeE6() const { return fEScoringVolume6; }

	G4double GetRH() const { return RH; }
	G4double GetHH() const { return HH; }
	G4double GetRC() const { return RC; }
	G4double GetHC() const { return HC; }
	G4double GettrapA() const { return trapA; }

	G4Box* GetSolidWorld() const { return solidWorld; }
	G4Box* GetSolidPBox() const { return solidPBox; }
  G4Box* GetSolidSBox() const { return solidSBox; } 
	G4VPhysicalVolume* GetPhysPBox() const { return physPBox; }
 
	
protected: // only inhereting classes can access
  G4LogicalVolume *fDEScoringVolume, *fDEScoringVolume1, *fDEScoringVolume2, 
  *fDEScoringVolume3, *fDEScoringVolume4, 
  *fDEScoringVolume5, *fDEScoringVolume6,
  *fEScoringVolume, *fEScoringVolume1, *fEScoringVolume2,
  *fEScoringVolume3, *fEScoringVolume4,
  *fEScoringVolume5, *fEScoringVolume6;

	G4Box *solidWorld;
	G4VPhysicalVolume *physWorld;

	// G4double RH = 43.3; // Scintillator's inner-circle radius (mm)
  G4double RH = 5.*cm;
  // G4double HH = 75.;
  G4double HH = 7.5*cm;
  G4double RC = 78*mm/2;
	G4double HC = 15*mm;
  G4double trapA = 2.0*RH/sqrt(3); // hexagon side

	G4Box* solidPBox, *solidSBox;
	G4VPhysicalVolume* physPBox;
};
#endif
