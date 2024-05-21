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

void MyPrimaryGenerator::GeneratePrimaries(G4Event *event)
{
	const MyDetectorConstruction* detectorConstruction
  	= static_cast<const MyDetectorConstruction*>
  	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

// Active source
	G4double RH = detectorConstruction->GetRH(); // Get RH from Detector Construction (it is in milimeter)
	G4double HH = 0.75*RH;
	G4double zPar = 4.*RH;
	G4double zDis = zPar + HH/2;

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

	G4ThreeVector pos1(0., 0., -zPar); // source position
	
	fParticleGun->SetParticlePosition(pos1);
  G4double randParE = 1*G4UniformRand();

  //! Cs137
  
  //! Na22

  //! Co60
  if(randParE <= 0.500331777697933){
    fParticleGun->SetParticleEnergy(1.173492*MeV);
  }
  else{
    fParticleGun->SetParticleEnergy(1.332228*MeV);
  }

	fParticleGun->SetParticleDefinition(particle);

	G4double random = G4UniformRand();
  G4double RHrand = RH*G4UniformRand();
  G4double theta = atan(RH/zDis);
  G4double alpha1 = atan(2.*RH/zDis);
  G4double alpha2 = alpha1 - theta;
  G4double phirand = twopi*G4UniformRand();

  G4double a = RHrand;
  G4double b = sqrt((a*a + zDis*zDis))*sin(alpha2);

  random = G4UniformRand();
  if (random < (1./3.))
  {
    G4double x = a*cos(phirand);
    G4double y = b*sin(phirand);
    G4double z = sqrt((RH*RH + zDis*zDis))*cos(alpha2);

    G4ThreeVector* zTrans = new G4ThreeVector(x, y, z);

    fParticleGun->SetParticleMomentumDirection(zTrans->rotateX(-atan(2.*RH/zDis)));
    // fParticleGun->GeneratePrimaryVertex(event);
  }
  else if (random > (2./3.))
  {
    G4double x = a*cos(phirand);
    G4double y = b*sin(phirand);
    G4double z = sqrt((RH*RH + zDis*zDis))*cos(alpha2);

    G4ThreeVector* zTrans = new G4ThreeVector(x, y, z);

    fParticleGun->SetParticleMomentumDirection(zTrans->rotateX(atan(2.*RH/zDis)));
    // fParticleGun->GeneratePrimaryVertex(event);
  }
  else
  {	
    G4double x = a*cos(phirand);
    G4double y = a*sin(phirand);
    G4double z = zDis;

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
    // fParticleGun->GeneratePrimaryVertex(event);
  }

//! Annihilation 511 gammas
  if(fParticleGun->GetParticleEnergy() == 1.274537*MeV){
    fParticleGun->SetParticleEnergy(0.511*MeV);
    G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double ux = sinTheta*std::cos(phi),
    uy = sinTheta*std::sin(phi),
    uz = cosTheta;

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
    // fParticleGun->GeneratePrimaryVertex(event);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-ux,-uy,-uz));
    // fParticleGun->GeneratePrimaryVertex(event);
  }
  
//! Ray tracing problem
	G4Box* solidPBox = detectorConstruction->GetSolidPBox();
  G4Box* solidSBox = detectorConstruction->GetSolidSBox();
	G4VPhysicalVolume* physPBox = detectorConstruction->GetPhysPBox();

	G4double pBoxDepth = 2*solidPBox->GetXHalfLength();
  G4double sBoxDepth = 2*solidSBox->GetXHalfLength();
	G4double bWidth = 2*solidPBox->GetYHalfLength();
	G4double bHeight = 2*solidPBox->GetZHalfLength();

	G4ThreeVector posPBox = physPBox->GetTranslation();
  G4double XposPBox = posPBox.getX();
  G4double YposPBox = posPBox.getY();
  G4double ZposPBox = posPBox.getZ();

	G4double dWorld = detectorConstruction->GetSolidWorld()->GetXHalfLength();

	G4double pos2x, pos2y, pos2z;

  pos2x = (2*G4UniformRand() - 1)*dWorld;
	pos2y = (2*G4UniformRand() - 1)*dWorld;
	pos2z = (2*G4UniformRand() - 1)*dWorld;

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
  G4ThreeVector pos2(dWorld/2. , dWorld/2. , dWorld/2.);

  //! Vertices coordinates in 3D
  std::vector <G4ThreeVector> ver;
  std::vector <G4double> verX, verY, verZ;
  ver.push_back(G4ThreeVector(XposPBox + pBoxDepth/2., YposPBox + bWidth/2., ZposPBox + bHeight/2.));
  ver.push_back(G4ThreeVector(XposPBox + pBoxDepth/2., YposPBox + bWidth/2., ZposPBox - bHeight/2.));
  ver.push_back(G4ThreeVector(XposPBox + pBoxDepth/2., YposPBox - bWidth/2., ZposPBox + bHeight/2.));
  ver.push_back(G4ThreeVector(XposPBox + pBoxDepth/2., YposPBox - bWidth/2., ZposPBox - bHeight/2.));
  ver.push_back(G4ThreeVector(XposPBox - pBoxDepth/2. - sBoxDepth, YposPBox + bWidth/2., ZposPBox + bHeight/2.));
  ver.push_back(G4ThreeVector(XposPBox - pBoxDepth/2. - sBoxDepth, YposPBox + bWidth/2., ZposPBox - bHeight/2.));
  ver.push_back(G4ThreeVector(XposPBox - pBoxDepth/2. - sBoxDepth, YposPBox - bWidth/2., ZposPBox + bHeight/2.));
  ver.push_back(G4ThreeVector(XposPBox - pBoxDepth/2. - sBoxDepth, YposPBox - bWidth/2., ZposPBox - bHeight/2.));

  std::vector <G4ThreeVector> dir;
  for(G4int i = 0; i < 8; i++)
  {
    dir.push_back(ver[i] - pos2);

    fParticleGun->SetParticlePosition(pos2);
    fParticleGun->SetParticleMomentumDirection(dir[i]);
	  // fParticleGun->GeneratePrimaryVertex(event);
  }

  G4double XposBoxCombined = XposPBox - sBoxDepth/2; // middle point of combined box

  //! Origin of the plane
  G4ThreeVector origin(XposBoxCombined, YposPBox, ZposPBox);

  //! Normal vector of the plane
  G4ThreeVector normalDirCenter = origin - pos2;
  
  //! Plane equation is: aPlane*x + bPlane*y + cPlane*z + dPlane = 0
  G4double aPlane = origin.getX() - pos2x;
  G4double bPlane = origin.getY() - pos2y;
  G4double cPlane = origin.getZ() - pos2z;

  //! d = -(ax + by + cz) with (x,y,z) belongs to plane
  G4double dPlane = -(aPlane*origin.getX() + bPlane*origin.getY() + cPlane*origin.getZ());

  G4cout << "a = " << aPlane << "; b = " << bPlane << "; c = " << cPlane << "; d = " << dPlane << "\n";

  //! X' and Y' axes in 3D coordinates
  G4ThreeVector planeXdef(bPlane, -aPlane, 0);
  G4ThreeVector planeYdef(normalDirCenter.cross(planeXdef));

  //! Normalize
  planeXdef = planeXdef/planeXdef.mag();
  planeYdef = planeYdef/planeYdef.mag();

  std::vector <G4ThreeVector> interSect, disPlace;
  std::vector <G4TwoVector> intPrime;

  for(G4int i = 0; i < 8; i++)
  {
    //! Solve t by substituting parametric line equation to plane equation
    G4double t = -(aPlane*pos2x + bPlane*pos2y + cPlane*pos2z + dPlane)/(aPlane*dir[i].getX() + bPlane*dir[i].getY() + cPlane*dir[i].getZ());

    //! Parametric equation of the line
    interSect.push_back(G4ThreeVector(pos2x + dir[i].getX()*t, pos2y + dir[i].getY()*t, pos2z + dir[i].getZ()*t));

    // G4cout << "intX = " << interSect[i].getX() << "; intY = " << interSect[i].getY() << "; intZ = " << interSect[i].getZ() << "\n";

    G4ThreeVector newdir(interSect[i].getX() - pos2x, interSect[i].getY() - pos2y, interSect[i].getZ() - pos2z);
    fParticleGun->SetParticleMomentumDirection(newdir);
	  // fParticleGun->GeneratePrimaryVertex(event);

    //! Displacement vector from the origin O of the OX'Y' system
    disPlace.push_back(interSect[i] - origin);
    
    //! Conversion intersection from OXYZ to OX'Y' coordinates
    intPrime.push_back(G4TwoVector(disPlace[i].dot(planeXdef), disPlace[i].dot(planeYdef)));
  }

  //! Convex hull algorithm
  G4TwoVector points[] = {intPrime[0], intPrime[1],
  intPrime[2], intPrime[3],
  intPrime[4], intPrime[5],
  intPrime[6], intPrime[7]};
  G4int n = sizeof(points) / sizeof(points[0]);
  convexHull(points, n);

  //! K40
  // fParticleGun->SetParticleEnergy(1.460822*MeV);
	// fParticleGun->GeneratePrimaryVertex(event);

  //! Convert hulls to 3D coordinates
  for (G4int i = 0; i < hullSize; i++)
  {
    disPlace[i] = hull[i].x()*planeXdef + (hull[i].y())*planeYdef;
  }

  //! new OX' start from first hull
  planeXdef = (hull[0].x())*(planeXdef) + (hull[0].y())*(planeYdef); // convert to 3D then minus origin
  planeYdef = normalDirCenter.cross(planeXdef);

  //! Normalize
  planeXdef = planeXdef/planeXdef.mag();
  planeYdef = planeYdef/planeYdef.mag();

  for (G4int i = 0; i < hullSize; i++)
  {
    intPrime[i] = G4TwoVector(disPlace[i].dot(planeXdef), disPlace[i].dot(planeYdef));
  }

  //! Connect each points
  std::vector <G4double> slope, intercept, angle1, angle;
  double dAngle = 0.;

  for(G4int i = 0; i < hullSize; i++)
  {
    if(i < hullSize -1)
    { //! connect newint i and newint i + 1
    //   G4cout << "hullpoint " << i + 1 << " = (" << intPrime[i].x() << ", " << intPrime[i].y() << ") and "
    // << "hullpoint " << i + 2 << " = (" << intPrime[i+1].x() << ", " << intPrime[i+1].y() << ")\n";
      
      slope.push_back((intPrime[i+1].y() - intPrime[i].y()) / (intPrime[i+1].x() - intPrime[i+1].x()));
      intercept.push_back(intPrime[i].y() - slope[i]*intPrime[i].x());

      dAngle = dAngle + intPrime[i].angle(intPrime[i+1])/deg;

      angle.push_back(dAngle);

      // G4cout << "angle " << i << " = " << angle[i] << "\n";
    }
    else
    { //! connect last newint i and newint 0
    //   G4cout << "hullpoint " << i + 1 << " = (" << intPrime[i].x() << ", " << intPrime[i].y() << ") and "
    // << "hullpoint 0 = (" << intPrime[0].x() << ", " << intPrime[0].y() << ")\n";

      slope.push_back((intPrime[hullSize -1].y() - intPrime[0].y()) / (intPrime[hullSize -1].x() - intPrime[0].x()));
      intercept.push_back(intPrime[hullSize -1].y() - slope[hullSize -1]*intPrime[hullSize -1].x());
      
      dAngle = dAngle + intPrime[hullSize - 1].angle(intPrime[0])/deg;
      
      angle.push_back(dAngle);
      // G4cout << "angle final = " << angle[hullSize - 1] << "\n";
    }
  }
  
  // for(G4int i = 0; i < hullSize; i++)
  // {
  //   angle[i] = ;
  // }

  // G4double 
  phirand = twopi*G4UniformRand()/deg;
  G4double rRand;

  for(G4int i = 0; i < hullSize; i++)
  {
    if(phirand <= angle[i])
    {
      rRand = G4UniformRand()*(intercept[i] / (1/sin(phirand) - slope[i]/cos(phirand)));
    }
    else{continue;}
  }

  G4double x = rRand*cos(phirand);
  G4double y = rRand*sin(phirand);

  G4ThreeVector dX = x*(planeXdef);
  G4ThreeVector dY = y*(planeYdef);

  G4ThreeVector finalCoor(dX + dY + origin);
  fParticleGun->SetParticleMomentumDirection(finalCoor - pos2);
  fParticleGun->GeneratePrimaryVertex(event); 

  //! Conversion from OX'Y' to OXYZ coordinates
  // std::vector<G4ThreeVector> p;

  // for (G4int i = 0; i < hullSize; i++)
  // {
  //   // G4cout << "2D coordinates: \n(" << hull[i].x() << ", " << hull[i].y() << ") \n";
  //   G4ThreeVector dX = (hull[i].x())*(planeXdef);
  //   G4ThreeVector dY = (hull[i].y())*(planeYdef);

  //   p.push_back(dX + dY + origin);

  //   fParticleGun->SetParticleMomentumDirection(p[i] - pos2);
	//   fParticleGun->GeneratePrimaryVertex(event);
  // }
}