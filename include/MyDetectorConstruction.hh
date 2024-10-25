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
	G4LogicalVolume* GetScoringVolumeDEL() const { return fDEScoringVolumeL; }
	G4LogicalVolume* GetScoringVolumeDER() const { return fDEScoringVolumeR; }

	G4LogicalVolume* GetScoringVolumeE() const { return fEScoringVolume; }
	G4LogicalVolume* GetScoringVolumeEL() const { return fEScoringVolumeL; }
	G4LogicalVolume* GetScoringVolumeER() const { return fEScoringVolumeR; }

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
  G4LogicalVolume *fDEScoringVolume, *fDEScoringVolumeL, *fDEScoringVolumeR,
  *fEScoringVolume, *fEScoringVolumeL, *fEScoringVolumeR;

	G4Box *solidWorld;
	G4VPhysicalVolume *physWorld;

  G4double RH = 5.*cm; //! BC404 Hexagon circumventing circle radius (mm)
  G4double HH = 7.5*cm; //! BC404 Hexagon thickness (mm)
  G4double RC = 78*mm/2; //! PMT radius
	G4double HC = 15*mm; //! PMT thickness
  G4double trapA = RH; //! smaller side of trapezoid
  G4double trapB = 2*RH; //! larger side of trapezoid
  G4double h_trap = 8.66*cm/2; //! BC404 hexagon's inner-circle radius (mm)

	G4Box* solidPBox, *solidSBox;
	G4VPhysicalVolume* physPBox;
};
#endif
