#ifndef MyPrimaryGenerator_hh
#define MyPrimaryGenerator_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4RunManager.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"

#include "Randomize.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4RandomDirection.hh"
#include "G4PVPlacement.hh"

#include "MyDetectorConstruction.hh"
#include "MyTreeHandler.hh"

class MyPrimaryGenerator: public G4VUserPrimaryGeneratorAction
{
public:
	MyPrimaryGenerator();
	virtual ~MyPrimaryGenerator();
	
	virtual void GeneratePrimaries(G4Event*);
private:
	G4ParticleGun* fParticleGun;
};
#endif
