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
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4UserLimits.hh"
#include "MyPrimaryGenerator.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public: // public to all classes
	MyDetectorConstruction();
	
	virtual ~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
	// Main function to construct geometry
	G4LogicalVolume* GetScoringVolumeDE(int NoDet) const { return fDEScoringVolume[NoDet]; }

	G4LogicalVolume* GetScoringVolumeE(int NoDet) const { return fEScoringVolume[NoDet]; }

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
  G4LogicalVolume* fDEScoringVolume[7];
  G4LogicalVolume* fEScoringVolume[7];

	G4Box *solidWorld;
	G4VPhysicalVolume *physWorld;
  
  // G4double surfaceThickness = .025*mm;
  G4double surfaceThickness = .075*mm;
  // G4double surfaceThickness = .1*mm;
  // G4double surfaceThickness = .2*mm;

  G4double RH = 5.*cm; //! BC404 Hexagon circumventing circle radius (mm)
  G4double HH = 7.5*cm; //! BC404 Hexagon thickness (mm)
  G4double RC = 78*mm/2; //! PMT radius
	G4double HC = 15*mm; //! PMT thickness
  G4double trapA = RH; //! smaller side of trapezoid
	G4double trapB = 2*RH; //! larger side of trapezoid
  G4double h = 8.66*cm/2; //! BC404 hexagon's inner-circle radius (mm)

  // G4double mylar_thickness = 10.*mm;
  G4double mylar_thickness = 1.5*mm;
  // G4double mylar_thickness = 0.5*mm;
  // G4double mylar_thickness = 1.0*mm;
  // G4double mylar_size_thickness = 1.5*mm;
  // G4double mylar_bottom_thickness = 1.5*mm;

  // double tape_thickness = 1.0*mm;
  G4double tape_thickness = 0.15*mm;
  // double tape_thickness = 3.0*mm;
  // double tape_thickness = 2.0*mm;
  // double tape_thickness = 1.5*mm; //! minor bump near 4 MeV
  // G4double tape_thickness = 1.25*mm; //! a step at 6-7 MeV
  // double tape_thickness = 300*um;
  // double tape_thickness = 10*mm;
  // double tape_thickness = 0.15*mm;
  // double tape_thickness = 0.25*mm;
  // G4double tape_thickness = 0.3*mm;
  // G4double tape_thickness = .75*mm;
  // G4double tape_thickness = 0.15*mm;

	G4double trapB_mylar = trapB + mylar_thickness*2; //! larger side of trapezoid
	G4double trapA_mylar = trapB_mylar/2; //! larger side of trapezoid
  G4double h_mylar = h + mylar_thickness; //! BC404 hexagon's inner-circle radius (mm)
  G4double HH_mylar = HH + mylar_thickness*2; //! BC404 Hexagon thickness (mm)

	G4double trapB_tape = trapB + tape_thickness*2 + mylar_thickness*2; //! larger side of trapezoid
	G4double trapA_tape = trapB_tape/2; //! larger side of trapezoid
  G4double h_tape = h + tape_thickness + mylar_thickness; //! BC404 hexagon's inner-circle radius (mm)
  G4double HH_tape = HH + tape_thickness*2 + mylar_thickness*2; //! BC404 Hexagon thickness (mm)

	G4Box* solidPBox, *solidSBox;
	G4VPhysicalVolume* physPBox;
};
#endif
