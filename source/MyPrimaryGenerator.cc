#include "MyPrimaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() :G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
	fParticleGun = new G4ParticleGun();
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

  //! Convex hull algorithm
std::vector<G4TwoVector> hull;
G4int hullSize;

int orientation(G4TwoVector p, G4TwoVector q, G4TwoVector r){ // given 3 points
  G4double val = (q.y()-p.y())*(r.x()-q.x())-(q.x()-p.x())*(r.y()-q.y());
  // find the angle between p;q and q;r
  if(val == 0) return 0; // all 3 points on same line
  return (val > 0)?1:2; // right: 2; left: 1
}

void convexHull(G4TwoVector points[], G4int n){
  hull.clear();
  if(n < 3) return;
  // if 2 points, no hull
  // if 3 points, hull = triangle
  G4int l = 0;
  for(G4int i = 1; i < n; i++)
  {
    if(points[i].x() < points[l].x()) // compare
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
  //   std::cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
  // }
}

//! Ray tracing problem
G4ThreeVector rayTrace(std::vector <G4ThreeVector> ver, G4ThreeVector origin, G4ThreeVector pos){
 
  std::vector <G4ThreeVector> dir;
  for(G4int i = 0; i < ver.size(); i++)
  {
    dir.push_back(ver[i] - pos);

    // fParticleGun->SetParticlePosition(pos);
    // fParticleGun->SetParticleMomentumDirection(dir[i]);
	  // fParticleGun->GeneratePrimaryVertex(event);

  // G4cout << "vertices x = " << ver[i].getX() << "; " << "y = " << ver[i].getY() << "; " << "z = " << ver[i].getZ() << "\n";    
  }
  
  //! Normal vector of the plane
  G4ThreeVector normalDirCenter = origin - pos;
  // G4cout << "origin x = " << origin.getX() << "; " << "y = " << origin.getY() << "; " << "z = " << origin.getZ() << "\n";
  // G4cout << "pos x = " << pos.getX() << "; " << "y = " << pos.getY() << "; " << "z = " << pos.getZ() << "\n";
  // G4cout << "norm x = " << normalDirCenter.getX() << "; " << "y = " << normalDirCenter.getY() << "; " << "z = " << normalDirCenter.getZ() << "\n";
  
  //! Plane equation is: aPlane*x + bPlane*y + cPlane*z + dPlane = 0
  G4double aPlane = normalDirCenter.getX();
  G4double bPlane = normalDirCenter.getY();
  G4double cPlane = normalDirCenter.getZ();

  //! d = -(ax + by + cz) with (x,y,z) belongs to plane
  G4double dPlane = -(aPlane*origin.getX() + bPlane*origin.getY() + cPlane*origin.getZ());

  // G4cout << "a = " << aPlane << "; b = " << bPlane << "; c = " << cPlane << "; d = " << dPlane << "\n";

  //! X' and Y' axes in 3D coordinates
  G4ThreeVector planeYdef(bPlane, -aPlane, 0);
  G4ThreeVector planeXdef((-normalDirCenter).cross(planeYdef));

  // fParticleGun->SetParticlePosition(origin);
  // fParticleGun->SetParticleMomentumDirection(planeXdef - origin);
	// fParticleGun->GeneratePrimaryVertex(event);
  // fParticleGun->SetParticleMomentumDirection(planeYdef - origin);
	// fParticleGun->GeneratePrimaryVertex(event);

  std::vector <G4ThreeVector> interSect, disPlace;
  G4TwoVector intPrime[ver.size()];

  for(G4int i = 0; i < ver.size(); i++)
  {
    //! Solve t by substituting parametric line equation to plane equation
    G4double t = -(aPlane*pos.getX() + bPlane*pos.getY() + cPlane*pos.getZ() + dPlane) / (aPlane*dir[i].getX() + bPlane*dir[i].getY() + cPlane*dir[i].getZ());

    //! Parametric equation of the line
    interSect.push_back(G4ThreeVector(pos.getX() + dir[i].getX()*t, pos.getY() + dir[i].getY()*t, pos.getZ() + dir[i].getZ()*t));

    // fParticleGun->SetParticleMomentumDirection(interSect[i] - pos);
	  // fParticleGun->GeneratePrimaryVertex(event);

    //! Displacement vector from the origin O of the OX'Y' system
    disPlace.push_back(interSect[i] - origin);
    // G4cout << "interSect[" << i << "] = (" << interSect[i].getX() << ", " << interSect[i].getY() << ", " << interSect[i].getZ() << ")\n";
    // G4cout << "origin[" << i << "] = (" << origin.getX() << ", " << origin.getY() << ", " << origin.getZ() << ")\n";
    // G4cout << "disPlace[" << i << "] = (" << disPlace[i].getX() << ", " << disPlace[i].getY() << ", " << disPlace[i].getZ() << ")\n";
    
    //! Conversion intersection from OXYZ to OX'Y' coordinates
    intPrime[i] = (G4TwoVector(disPlace[i].dot(planeXdef)/planeXdef.mag(), disPlace[i].dot(planeYdef)/planeYdef.mag()));
    // G4cout << "intPrime[" << i << "] = (" << disPlace[i].dot(planeXdef)/planeXdef.mag() << ", " << disPlace[i].dot(planeYdef)/planeYdef.mag() << ")\n";
    // G4cout << "intPrime[" << i << "] = (" << intPrime[i].x() << ", " << intPrime[i].y() << ")\n";
  }

  //! Convex hull algorithm
  G4int n = sizeof(intPrime) / sizeof(intPrime[0]);
  convexHull(intPrime, n);

  // G4cout << "hull size = " << hullSize << "\n";

  std::vector <G4ThreeVector> hull3D;

  //! Convert hulls to 3D coordinates
  for (G4int i = 0; i < hullSize; i++)
  {
    // G4cout << "hullpoint [" << i << "] = (" << hull[i].x() << ", " << hull[i].y() << ") \n";

    G4ThreeVector dX = (hull[i].x())*(planeXdef)/planeXdef.mag();
    G4ThreeVector dY = (hull[i].y())*(planeYdef)/planeYdef.mag();

    hull3D.push_back(dX + dY + origin);
    // hull3D.push_back(hull[i].x()*planeXdef/planeXdef.mag() + (hull[i].y())*planeYdef/planeXdef.mag() + origin);

    // fParticleGun->SetParticleMomentumDirection(hull3D[i] - pos);
	  // fParticleGun->GeneratePrimaryVertex(event);
  }

  //! new OX' start from first hull
  planeXdef = hull3D[0] - origin; // convert to 3D then minus origin
  planeYdef = normalDirCenter.cross(planeXdef);

  // G4cout << "angle between 2 def =" << planeXdef.angle(planeYdef)/deg;

  // fParticleGun->SetParticlePosition(origin);
  // fParticleGun->SetParticleMomentumDirection(planeXdef - origin);
	// fParticleGun->GeneratePrimaryVertex(event);
  // fParticleGun->SetParticleMomentumDirection(planeYdef - origin);
	// fParticleGun->GeneratePrimaryVertex(event);

  std::vector <G4ThreeVector> newintPrime;
  for (G4int i = 0; i < hullSize; i++)
  {
    G4ThreeVector newdisPlace = hull3D[i] - origin;
    newintPrime.push_back(G4TwoVector(newdisPlace.dot(planeXdef)/planeXdef.mag(), newdisPlace.dot(planeYdef)/planeYdef.mag()));
  }

  //! Connect each points
  std::vector <G4double> slope, intercept, angle1, angle2;
  G4double dAngle = 0.;

  for(G4int i = 0; i < hullSize; i++)
  {
    if(i < hullSize-1)
    { //! connect newint i and newint i + 1
      // G4cout << "newintPrime [" << i << "] = (" << newintPrime[i].x() << ", " << newintPrime[i].y() << ") and "
    // << "newintPrime [" << i + 1 << "] = (" << newintPrime[i+1].x() << ", " << newintPrime[i+1].y() << ")\n";
      
      slope.push_back((newintPrime[i+1].y() - newintPrime[i].y()) / (newintPrime[i+1].x() - newintPrime[i].x()));
      intercept.push_back(newintPrime[i].y() - slope[i]*newintPrime[i].x());

      // G4cout << "slope [" << i << "] = " << slope[i] << "\n";
      // G4cout << "intercept [" << i << "] = " << intercept[i] << "\n";

      angle1.push_back(dAngle);
      angle2.push_back(dAngle+ newintPrime[i].angle(newintPrime[i+1])/deg);
      dAngle = dAngle + newintPrime[i].angle(newintPrime[i+1])/deg;

      // G4cout << "angle1 [" << i << "] = " << angle1[i] << "\n";
      // G4cout << "angle2 [" << i << "] = " << angle2[i] << "\n";
    }
    else
    { //! connect last newint i and newint 0
      // G4cout << "newintPrime [" << i << "] = (" << newintPrime[i].x() << ", " << newintPrime[i].y() << ") and "
    // << "newintPrime [0] = (" << newintPrime[0].x() << ", " << newintPrime[0].y() << ")\n";

      slope.push_back((newintPrime[0].y() - newintPrime[hullSize-1].y()) / (newintPrime[0].x() - newintPrime[hullSize-1].x()));
      intercept.push_back(newintPrime[hullSize-1].y() - slope[hullSize-1]*newintPrime[hullSize-1].x());

      // G4cout << "slope [" << hullSize-1 << "] = " << slope[hullSize-1] << "\n";
      // G4cout << "intercept [" << hullSize-1 << "] = " << intercept[hullSize-1] << "\n";
      
      angle1.push_back(dAngle);
      angle2.push_back(dAngle+ newintPrime[hullSize-1].angle(newintPrime[0])/deg);
      dAngle = dAngle + newintPrime[hullSize-1].angle(newintPrime[0])/deg;

      // G4cout << "angle1 [" << hullSize-1 << "] = " << angle1[hullSize-1] << "\n";
      // G4cout << "angle2 [" << hullSize-1 << "] = " << angle2[hullSize-1] << "\n";
    }
  }

  G4double phiRand = twopi*G4UniformRand()/deg;
  // G4cout << "phiRand = " << phiRand << "\n";

  G4double r;

  for(G4int i = 0; i < hullSize; i++)
  {
    if(phiRand <= angle2[i] && phiRand > angle1[i])
    {
      // G4cout << "angle is between angle1[" << i << "] = " << angle1[i] << " and angle2[" << i << "] = " << angle2[i] << "\n";
      r = abs((intercept[i] / (sin(phiRand*deg) - slope[i]*cos(phiRand*deg))));
      // G4cout << "rRand = " << r << "\n";
    }
    // G4cout << "rRand = " << rRand << "\n";
  }

  G4double rRand = r*G4UniformRand();

  // G4cout << "phirand = " << phirand << "\n";
  // G4cout << "cos phi rand = " << cos(phiRand*deg) << "\n";
  // G4cout << "sin phi rand = " << sin(phiRand*deg) << "\n";

  G4double x = rRand*cos(phiRand*deg);
  G4double y = rRand*sin(phiRand*deg);

  // G4cout << "x = " << x << "\n";
  // G4cout << "y = " << y << "\n";
 
  //! Conversion from OX'Y' to OXYZ coordinates
  G4ThreeVector dX = x*(planeXdef)/planeXdef.mag();
  G4ThreeVector dY = y*(planeYdef)/planeYdef.mag();

  G4ThreeVector finalCoor(dX + dY + origin);

  return finalCoor;
}

//! Start of primaries
void MyPrimaryGenerator::GeneratePrimaries(G4Event *event)
{
	const MyDetectorConstruction* detectorConstruction
  = static_cast<const MyDetectorConstruction*>
  (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	G4double RH = detectorConstruction->GetRH(); // Get RH from Detector Construction (it is in milimeter)
	G4double HH = 0.75*RH;
	G4double zPar = 4.*RH;
	G4double zDis = zPar + HH/2;

	G4ThreeVector pos1(0., 0., -zPar); // source position
	
// 	fParticleGun->SetParticlePosition(pos1);
//   G4double randParE = 1*G4UniformRand();

//   //! Cs137
  
//   //! Na22

//   //! Co60
//   if(randParE <= 0.500331777697933){
//     fParticleGun->SetParticleEnergy(1.173492*MeV);
//   }
//   else{
//     fParticleGun->SetParticleEnergy(1.332228*MeV);
//   }

// 	fParticleGun->SetParticleDefinition(particle);

// 	 G4double random = G4UniformRand();
//   G4double RHrand = RH*G4UniformRand();
//   G4double theta = atan(RH/zDis);
//   G4double alpha1 = atan(2.*RH/zDis);
//   G4double alpha2 = alpha1 - theta;
//   G4double phirand = twopi*G4UniformRand();

//   G4double a = RHrand;
//   G4double b = sqrt((a*a + zDis*zDis))*sin(alpha2);

//   random = G4UniformRand();
//   if (random < (1./3.))
//   {
//     G4double x = a*cos(phirand);
//     G4double y = b*sin(phirand);
//     G4double z = sqrt((RH*RH + zDis*zDis))*cos(alpha2);

//     G4ThreeVector* zTrans = new G4ThreeVector(x, y, z);

//     fParticleGun->SetParticleMomentumDirection(zTrans->rotateX(-atan(2.*RH/zDis)));
//     // fParticleGun->GeneratePrimaryVertex(event);
//     delete zTrans;
//   }
//   else if (random > (2./3.))
//   {
//     G4double x = a*cos(phirand);
//     G4double y = b*sin(phirand);
//     G4double z = sqrt((RH*RH + zDis*zDis))*cos(alpha2);

//     G4ThreeVector* zTrans = new G4ThreeVector(x, y, z);

//     fParticleGun->SetParticleMomentumDirection(zTrans->rotateX(atan(2.*RH/zDis)));
//     // fParticleGun->GeneratePrimaryVertex(event);

//     delete zTrans;
//   }
//   else
//   {	
//     G4double x = a*cos(phirand);
//     G4double y = a*sin(phirand);
//     G4double z = zDis;

//     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
//     // fParticleGun->GeneratePrimaryVertex(event);
//   }

// //! Annihilation 511 gammas
//   if(fParticleGun->GetParticleEnergy() == 1.274537*MeV){
//     fParticleGun->SetParticleEnergy(0.511*MeV);
//     G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
//     G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
//     G4double ux = sinTheta*std::cos(phi),
//     uy = sinTheta*std::sin(phi),
//     uz = cosTheta;

//     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
//     // fParticleGun->GeneratePrimaryVertex(event);
//     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-ux,-uy,-uz));
//     // fParticleGun->GeneratePrimaryVertex(event);
//   }
  
	G4Box* solidPBox = detectorConstruction->GetSolidPBox();
  G4Box* solidSBox = detectorConstruction->GetSolidSBox();
	// G4VPhysicalVolume* physPBox = detectorConstruction->GetPhysPBox();

	G4double pBoxDepth = 2*solidPBox->GetXHalfLength();
  G4double sBoxDepth = 2*solidSBox->GetXHalfLength();
	G4double bWidth = 2*solidPBox->GetYHalfLength();
	G4double bHeight = 2*solidPBox->GetZHalfLength();

	// G4ThreeVector posPBox = physPBox->GetTranslation();
  G4double XposPBox = (detectorConstruction->GetPhysPBox()->GetTranslation()).getX();
  G4double YposPBox = (detectorConstruction->GetPhysPBox()->GetTranslation()).getY();
  G4double ZposPBox = (detectorConstruction->GetPhysPBox()->GetTranslation()).getZ();

	G4double dWorld = detectorConstruction->GetSolidWorld()->GetXHalfLength();

	G4double pos2x, pos2y, pos2z;

  pos2x = (2*G4UniformRand() - 1)*dWorld;
	pos2y = (2*G4UniformRand() - 1)*dWorld;
	pos2z = (2*G4UniformRand() - 1)*dWorld;

  G4double random = G4UniformRand();

	if(random < (1./3.))
	{		
		if(pos2x < dWorld && pos2x > -dWorld)
		{
			pos2y = (2*((rand() % 10) % 2) - 1)*dWorld;
		}
	}
	else if(random > (2./3.))
	{		
		if(pos2y < dWorld && pos2y > -dWorld)
		{
			pos2z = (2*((rand() % 10) % 2) - 1)*dWorld;
		}
	}
	else
	{
		if(pos2z < dWorld && pos2z > -dWorld)
		{
			pos2x = (2*((rand() % 10) % 2) - 1)*dWorld;
		}
	}
  
  // G4ThreeVector pos2(pos2x, pos2y, pos2z);
  G4ThreeVector pos2(500. , 500. , 500.);

  //! Vertices coordinates in 3D
  std::vector <G4ThreeVector> ver1;
  ver1.push_back(G4ThreeVector(XposPBox + pBoxDepth/2., YposPBox + bWidth/2., ZposPBox + bHeight/2.));
  ver1.push_back(G4ThreeVector(XposPBox + pBoxDepth/2., YposPBox + bWidth/2., ZposPBox - bHeight/2.));
  ver1.push_back(G4ThreeVector(XposPBox + pBoxDepth/2., YposPBox - bWidth/2., ZposPBox + bHeight/2.));
  ver1.push_back(G4ThreeVector(XposPBox + pBoxDepth/2., YposPBox - bWidth/2., ZposPBox - bHeight/2.));
  ver1.push_back(G4ThreeVector(XposPBox - pBoxDepth/2. - sBoxDepth, YposPBox + bWidth/2., ZposPBox + bHeight/2.));
  ver1.push_back(G4ThreeVector(XposPBox - pBoxDepth/2. - sBoxDepth, YposPBox + bWidth/2., ZposPBox - bHeight/2.));
  ver1.push_back(G4ThreeVector(XposPBox - pBoxDepth/2. - sBoxDepth, YposPBox - bWidth/2., ZposPBox + bHeight/2.));
  ver1.push_back(G4ThreeVector(XposPBox - pBoxDepth/2. - sBoxDepth, YposPBox - bWidth/2., ZposPBox - bHeight/2.));

  G4double XposBoxCombined = XposPBox - sBoxDepth/2; // middle point of combined box

  //! Origin of the plane
  G4ThreeVector origin(XposBoxCombined, YposPBox, ZposPBox);
 
  // std::vector <G4ThreeVector> dir;
  // for(G4int i = 0; i < ver.size(); i++)
  // {
  //   dir.push_back(ver[i] - pos2);

  //   fParticleGun->SetParticlePosition(pos2);
  //   // fParticleGun->SetParticleMomentumDirection(dir[i]);
	//   // fParticleGun->GeneratePrimaryVertex(event);
  // }
  
  // //! Normal vector of the plane
  // G4ThreeVector normalDirCenter = origin - pos2;
  // // G4cout << "origin x = " << origin.getX() << "; " << "y = " << origin.getY() << "; " << "z = " << origin.getZ() << "\n";
  // // G4cout << "pos2 x = " << pos2.getX() << "; " << "y = " << pos2.getY() << "; " << "z = " << pos2.getZ() << "\n";
  // // G4cout << "norm x = " << normalDirCenter.getX() << "; " << "y = " << normalDirCenter.getY() << "; " << "z = " << normalDirCenter.getZ() << "\n";
  
  // //! Plane equation is: aPlane*x + bPlane*y + cPlane*z + dPlane = 0
  // G4double aPlane = normalDirCenter.getX();
  // G4double bPlane = normalDirCenter.getY();
  // G4double cPlane = normalDirCenter.getZ();

  // //! d = -(ax + by + cz) with (x,y,z) belongs to plane
  // G4double dPlane = -(aPlane*origin.getX() + bPlane*origin.getY() + cPlane*origin.getZ());

  // // G4cout << "a = " << aPlane << "; b = " << bPlane << "; c = " << cPlane << "; d = " << dPlane << "\n";

  // //! X' and Y' axes in 3D coordinates
  // G4ThreeVector planeYdef(bPlane, -aPlane, 0);
  // G4ThreeVector planeXdef((-normalDirCenter).cross(planeYdef));

  // // fParticleGun->SetParticlePosition(origin);
  // // fParticleGun->SetParticleMomentumDirection(planeXdef - origin);
	// // fParticleGun->GeneratePrimaryVertex(event);
  // // fParticleGun->SetParticleMomentumDirection(planeYdef - origin);
	// // fParticleGun->GeneratePrimaryVertex(event);

  // std::vector <G4ThreeVector> interSect, disPlace;
  // G4TwoVector intPrime[ver.size()];

  // for(G4int i = 0; i < ver.size(); i++)
  // {
  //   //! Solve t by substituting parametric line equation to plane equation
  //   G4double t = -(aPlane*pos2.getX() + bPlane*pos2.getY() + cPlane*pos2.getZ() + dPlane) / (aPlane*dir[i].getX() + bPlane*dir[i].getY() + cPlane*dir[i].getZ());

  //   //! Parametric equation of the line
  //   interSect.push_back(G4ThreeVector(pos2.getX() + dir[i].getX()*t, pos2.getY() + dir[i].getY()*t, pos2.getZ() + dir[i].getZ()*t));

  //   fParticleGun->SetParticleMomentumDirection(interSect[i] - pos2);
	//   // fParticleGun->GeneratePrimaryVertex(event);

  //   //! Displacement vector from the origin O of the OX'Y' system
  //   disPlace.push_back(interSect[i] - origin);
  //   // G4cout << "interSect[" << i << "] = (" << interSect[i].getX() << ", " << interSect[i].getY() << ", " << interSect[i].getZ() << ")\n";
  //   // G4cout << "origin[" << i << "] = (" << origin.getX() << ", " << origin.getY() << ", " << origin.getZ() << ")\n";
  //   // G4cout << "disPlace[" << i << "] = (" << disPlace[i].getX() << ", " << disPlace[i].getY() << ", " << disPlace[i].getZ() << ")\n";
    
  //   //! Conversion intersection from OXYZ to OX'Y' coordinates
  //   intPrime[i] = (G4TwoVector(disPlace[i].dot(planeXdef)/planeXdef.mag(), disPlace[i].dot(planeYdef)/planeYdef.mag()));
  //   // G4cout << "intPrime[" << i << "] = (" << disPlace[i].dot(planeXdef)/planeXdef.mag() << ", " << disPlace[i].dot(planeYdef)/planeYdef.mag() << ")\n";
  //   // G4cout << "intPrime[" << i << "] = (" << intPrime[i].x() << ", " << intPrime[i].y() << ")\n";
  // }

  // //! Convex hull algorithm
  // G4int n = sizeof(intPrime) / sizeof(intPrime[0]);
  // convexHull(intPrime, n);

  // // G4cout << "hull size = " << hullSize << "\n";

  // std::vector <G4ThreeVector> hull3D;

  // //! Convert hulls to 3D coordinates
  // for (G4int i = 0; i < hullSize; i++)
  // {
  //   // G4cout << "hullpoint [" << i << "] = (" << hull[i].x() << ", " << hull[i].y() << ") \n";

  //   G4ThreeVector dX = (hull[i].x())*(planeXdef)/planeXdef.mag();
  //   G4ThreeVector dY = (hull[i].y())*(planeYdef)/planeYdef.mag();

  //   hull3D.push_back(dX + dY + origin);
  //   // hull3D.push_back(hull[i].x()*planeXdef/planeXdef.mag() + (hull[i].y())*planeYdef/planeXdef.mag() + origin);

  //   fParticleGun->SetParticleMomentumDirection(hull3D[i] - pos2);
	//   // fParticleGun->GeneratePrimaryVertex(event);
  // }

  // //! new OX' start from first hull
  // planeXdef = hull3D[0] - origin; // convert to 3D then minus origin
  // planeYdef = normalDirCenter.cross(planeXdef);

  // // G4cout << "angle between 2 def =" << planeXdef.angle(planeYdef)/deg;

  // // fParticleGun->SetParticlePosition(origin);
  // // fParticleGun->SetParticleMomentumDirection(planeXdef - origin);
	// // fParticleGun->GeneratePrimaryVertex(event);
  // // fParticleGun->SetParticleMomentumDirection(planeYdef - origin);
	// // fParticleGun->GeneratePrimaryVertex(event);

  // std::vector <G4ThreeVector> newintPrime;
  // for (G4int i = 0; i < hullSize; i++)
  // {
  //   G4ThreeVector newdisPlace = hull3D[i] - origin;
  //   newintPrime.push_back(G4TwoVector(newdisPlace.dot(planeXdef)/planeXdef.mag(), newdisPlace.dot(planeYdef)/planeYdef.mag()));
  // }

  // //! Connect each points
  // std::vector <G4double> slope, intercept, angle1, angle2;
  // G4double dAngle = 0.;

  // for(G4int i = 0; i < hullSize; i++)
  // {
  //   if(i < hullSize-1)
  //   { //! connect newint i and newint i + 1
  //     // G4cout << "newintPrime [" << i << "] = (" << newintPrime[i].x() << ", " << newintPrime[i].y() << ") and "
  //   // << "newintPrime [" << i + 1 << "] = (" << newintPrime[i+1].x() << ", " << newintPrime[i+1].y() << ")\n";
      
  //     slope.push_back((newintPrime[i+1].y() - newintPrime[i].y()) / (newintPrime[i+1].x() - newintPrime[i].x()));
  //     intercept.push_back(newintPrime[i].y() - slope[i]*newintPrime[i].x());

  //     // G4cout << "slope [" << i << "] = " << slope[i] << "\n";
  //     // G4cout << "intercept [" << i << "] = " << intercept[i] << "\n";

  //     angle1.push_back(dAngle);
  //     angle2.push_back(dAngle+ newintPrime[i].angle(newintPrime[i+1])/deg);
  //     dAngle = dAngle + newintPrime[i].angle(newintPrime[i+1])/deg;

  //     // G4cout << "angle1 [" << i << "] = " << angle1[i] << "\n";
  //     // G4cout << "angle2 [" << i << "] = " << angle2[i] << "\n";
  //   }
  //   else
  //   { //! connect last newint i and newint 0
  //     // G4cout << "newintPrime [" << i << "] = (" << newintPrime[i].x() << ", " << newintPrime[i].y() << ") and "
  //   // << "newintPrime [0] = (" << newintPrime[0].x() << ", " << newintPrime[0].y() << ")\n";

  //     slope.push_back((newintPrime[0].y() - newintPrime[hullSize-1].y()) / (newintPrime[0].x() - newintPrime[hullSize-1].x()));
  //     intercept.push_back(newintPrime[hullSize-1].y() - slope[hullSize-1]*newintPrime[hullSize-1].x());

  //     // G4cout << "slope [" << hullSize-1 << "] = " << slope[hullSize-1] << "\n";
  //     // G4cout << "intercept [" << hullSize-1 << "] = " << intercept[hullSize-1] << "\n";
      
  //     angle1.push_back(dAngle);
  //     angle2.push_back(dAngle+ newintPrime[hullSize-1].angle(newintPrime[0])/deg);
  //     dAngle = dAngle + newintPrime[hullSize-1].angle(newintPrime[0])/deg;

  //     // G4cout << "angle1 [" << hullSize-1 << "] = " << angle1[hullSize-1] << "\n";
  //     // G4cout << "angle2 [" << hullSize-1 << "] = " << angle2[hullSize-1] << "\n";
  //   }
  // }

  // G4double phiRand = twopi*G4UniformRand()/deg;
  // // G4cout << "phiRand = " << phiRand << "\n";

  // G4double r;

  // for(G4int i = 0; i < hullSize; i++)
  // {
  //   if(phiRand <= angle2[i] && phiRand > angle1[i])
  //   {
  //     // G4cout << "angle is between angle1[" << i << "] = " << angle1[i] << " and angle2[" << i << "] = " << angle2[i] << "\n";
  //     r = abs((intercept[i] / (sin(phiRand*deg) - slope[i]*cos(phiRand*deg))));
  //     // G4cout << "rRand = " << r << "\n";
  //   }
  //   // G4cout << "rRand = " << rRand << "\n";
  // }

  // G4double rRand = r*G4UniformRand();

  // // G4cout << "phirand = " << phirand << "\n";
  // // G4cout << "cos phi rand = " << cos(phiRand*deg) << "\n";
  // // G4cout << "sin phi rand = " << sin(phiRand*deg) << "\n";

  // G4double x = rRand*cos(phiRand*deg);
  // G4double y = rRand*sin(phiRand*deg);

  // // G4cout << "x = " << x << "\n";
  // // G4cout << "y = " << y << "\n";
 
  // //! Conversion from OX'Y' to OXYZ coordinates
  // G4ThreeVector dX = x*(planeXdef)/planeXdef.mag();
  // G4ThreeVector dY = y*(planeYdef)/planeYdef.mag();

  // G4ThreeVector finalCoor(dX + dY + origin);

  G4double XposMWorld = (detectorConstruction->GetPhysMWorld()->GetTranslation()).getX();
  G4double YposMWorld = (detectorConstruction->GetPhysMWorld()->GetTranslation()).getY();
  G4double ZposMWorld = (detectorConstruction->GetPhysMWorld()->GetTranslation()).getZ();

  G4double xMWorld = detectorConstruction->GetSolidMWorld()->GetXHalfLength();
  G4double yMWorld = detectorConstruction->GetSolidMWorld()->GetYHalfLength();
  G4double zMWorld = detectorConstruction->GetSolidMWorld()->GetZHalfLength();

  std::vector <G4ThreeVector> verTest;
  verTest.push_back(G4ThreeVector(XposMWorld + xMWorld, YposMWorld + yMWorld, ZposMWorld + zMWorld));
  verTest.push_back(G4ThreeVector(XposMWorld + xMWorld, YposMWorld + yMWorld, ZposMWorld - zMWorld));
  verTest.push_back(G4ThreeVector(XposMWorld + xMWorld, YposMWorld - yMWorld, ZposMWorld + zMWorld));
  verTest.push_back(G4ThreeVector(XposMWorld + xMWorld, YposMWorld - yMWorld, ZposMWorld - zMWorld));
  verTest.push_back(G4ThreeVector(XposMWorld - xMWorld, YposMWorld + yMWorld, ZposMWorld + zMWorld));
  verTest.push_back(G4ThreeVector(XposMWorld - xMWorld, YposMWorld + yMWorld, ZposMWorld - zMWorld));
  verTest.push_back(G4ThreeVector(XposMWorld - xMWorld, YposMWorld - yMWorld, ZposMWorld + zMWorld));
  verTest.push_back(G4ThreeVector(XposMWorld - xMWorld, YposMWorld - yMWorld, ZposMWorld - zMWorld));

  G4ThreeVector originTest(XposMWorld, YposMWorld, ZposMWorld);

  //! Input to rayTrace for cube
  // G4ThreeVector finalCoor1 = rayTrace(ver1, origin, pos1);
  //? rayTrace(array of all vertices, origin of perpendicular plane, source position)

  fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("gamma"));
  fParticleGun->SetParticleEnergy(0.6616553*MeV);
  fParticleGun->SetParticlePosition(pos2);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(rayTrace(ver1, originTest, pos2) - pos2));
  fParticleGun->GeneratePrimaryVertex(event);

  G4ThreeVector pos3(-500., 500. , 500.);
  fParticleGun->SetParticlePosition(pos3);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(rayTrace(ver1, originTest, pos3) - pos3));
  fParticleGun->GeneratePrimaryVertex(event);
}