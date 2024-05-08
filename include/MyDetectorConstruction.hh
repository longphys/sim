#ifndef MyDetectorConstruction_hh
#define MyDetectorConstruction_hh
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
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
	G4LogicalVolume* GetScoringVolumeDEL() const { return fDEScoringVolumeL; }
	G4LogicalVolume* GetScoringVolumeDER() const { return fDEScoringVolumeR; }

	G4LogicalVolume* GetScoringVolumeE() const { return fEScoringVolume; }
	G4LogicalVolume* GetScoringVolumeEL() const { return fEScoringVolumeL; }
	G4LogicalVolume* GetScoringVolumeER() const { return fEScoringVolumeR; }

	G4double GetRH() const { return RH; }
	G4double GetHH() const { return HH; }
	G4double GettrapA() const { return trapA; }

	G4Box* GetSolidWorld() const { return solidWorld; }
	G4Box* GetSolidPBox() const { return solidPBox; }
  G4Box* GetSolidSBox() const { return solidSBox; } 
	G4VPhysicalVolume* GetPhysPBox() const { return physPBox; }
 
	
protected: // only inhereting classes can access
  G4LogicalVolume *fDEScoringVolume, *fDEScoringVolumeL, *fDEScoringVolumeR,
  *fEScoringVolume, *fEScoringVolumeL, *fEScoringVolumeR;

	G4Box *solidWorld;
	G4VPhysicalVolume *physWorld;

	G4double RH = 50.; // Scintillator's inner-circle radius (mm)
	G4double HH = 0.75*RH;
  G4double trapA = 2.0*RH/sqrt(3); // hexagon side

	G4Box* solidPBox, *solidSBox;
	G4VPhysicalVolume* physPBox;
};
#endif
