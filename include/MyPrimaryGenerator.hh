#ifndef MyPrimaryGenerator_hh
#define MyPrimaryGenerator_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4RunManager.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh" // For calling particle type, for example, protons
#include "G4IonTable.hh"

#include "Randomize.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4RandomDirection.hh"
#include "G4PVPlacement.hh"

#include "MyDetectorConstruction.hh"

class MyPrimaryGenerator: public G4VUserPrimaryGeneratorAction // Inhereting from Geant4 class
{
public:
	MyPrimaryGenerator();
	virtual ~MyPrimaryGenerator();
	
	virtual void GeneratePrimaries(G4Event*);
	// A "GeneratePrimaries" function from Geant4 Generator class (virtual, the same as that of "action.hh"), which will create primaries, which will be used by "action.cc" with an argument "G4Event"
	
private:
	G4ParticleGun* fParticleGun; // a Particle Gun
  struct Point{
      G4double x, y; // coordinates in 2D system
  };
  std::vector<Point> hull;
  G4int hullSize;

  int orientation(Point p, Point q, Point r){ // given 3 points
    G4double val = (q.y-p.y)*(r.x-q.x)-(q.x-p.x)*(r.y-q.y);
    // find the angle between p;q and q;r
    if(val == 0) return 0; // all 3 points on same line
    return (val > 0)?1:2; // right: 2; left: 1
  }

  void convexHull(Point points[], G4int n){
    hull.clear();
    if(n < 3) return;
    // if 2 points, no hull
    // if 3 points, hull = triangle
    G4int l = 0;
    for(G4int i = 1; i < n; i++)
    {
        if(points[i].x < points[l].x) // compare
        {
          l = i; // find the leftmost point
        }
    }
      
    G4int p = l,q;
    do{
      hull.push_back(points[p]);
      q = (p + 1) % n;
      for(G4int i = 0; i < n; i++)
      {
        if(orientation(points[p], points[i], points[q]) == 2)
        {
          q = i;
        }
      }
      p = q;
    } while (p != l);
    hullSize = hull.size();
    // for(G4int i = 0; i < hullSize; i++)
    // {
    //   std::cout << "(" << hull[i].x << hull[i].y << ")\n";
    // }
  }
};
#endif
