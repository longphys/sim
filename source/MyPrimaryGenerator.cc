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
struct Point{
    G4double x, y;
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
  for(G4int i = 0; i < hullSize; i++)
  {
    std::cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
  }
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
	// fParticleGun->SetParticleEnergy(.6616553*MeV);
  
  //! Na22
  // if(randParE <= 0.643885404789054){
  //   fParticleGun->SetParticleEnergy(0.511*MeV);
  // }
  // else{
  //   fParticleGun->SetParticleEnergy(1.274537*MeV);
  // }
	
  //! Co60
  if(randParE <= 0.500331777697933){
    fParticleGun->SetParticleEnergy(1.173492*MeV);
  }
  else{
    fParticleGun->SetParticleEnergy(1.332228*MeV);
  }

	fParticleGun->SetParticleDefinition(particle);

	G4double random = G4UniformRand();
  for (G4int i = 0; i < 1; i++)
  {
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

  // pos2x = dWorld;
	// pos2y = dWorld;
	// pos2z = dWorld;
  // Vertices 3D
  std::vector <G4double> verX, verY, verZ;
  verX.push_back(XposPBox + pBoxDepth/2.); verY.push_back(YposPBox + bWidth/2.); verZ.push_back(ZposPBox + bHeight/2.);
  verX.push_back(XposPBox + pBoxDepth/2.); verY.push_back(YposPBox + bWidth/2.); verZ.push_back(ZposPBox - bHeight/2.);
  verX.push_back(XposPBox + pBoxDepth/2.); verY.push_back(YposPBox - bWidth/2.); verZ.push_back(ZposPBox + bHeight/2.);
  verX.push_back(XposPBox + pBoxDepth/2.); verY.push_back(YposPBox - bWidth/2.); verZ.push_back(ZposPBox - bHeight/2.);
  verX.push_back(XposPBox - pBoxDepth/2. - sBoxDepth); verY.push_back(YposPBox + bWidth/2.); verZ.push_back(ZposPBox + bHeight/2.);
  verX.push_back(XposPBox - pBoxDepth/2. - sBoxDepth); verY.push_back(YposPBox + bWidth/2.); verZ.push_back(ZposPBox - bHeight/2.);
  verX.push_back(XposPBox - pBoxDepth/2. - sBoxDepth); verY.push_back(YposPBox - bWidth/2.); verZ.push_back(ZposPBox + bHeight/2.);
  verX.push_back(XposPBox - pBoxDepth/2. - sBoxDepth); verY.push_back(YposPBox - bWidth/2.); verZ.push_back(ZposPBox - bHeight/2.);

  std::vector <G4double> dirX, dirY, dirZ;

  for(G4int i = 0; i < 8; i++)
  {
    // G4cout << "verX[" << i << "]: " << verX[i] 
    // << "; verY[" << i << "]: " << verY[i] 
    // << "; verZ[" << i << "]: " << verZ[i] << "\n";

    dirX.push_back(verX[i] - pos2x);
    dirY.push_back(verY[i] - pos2y);
    dirZ.push_back(verZ[i] - pos2z);

    G4ThreeVector pos2(pos2x, pos2y, pos2z);
    G4ThreeVector dir(dirX[i], dirY[i], dirZ[i]);
    fParticleGun->SetParticlePosition(pos2);
    fParticleGun->SetParticleMomentumDirection(dir);
	  // fParticleGun->GeneratePrimaryVertex(event);
  }

  G4double XposBoxCombined = XposPBox - sBoxDepth/2; // middle point of combined box

  G4ThreeVector normalDirCenter
  (XposBoxCombined - pos2x,
  YposPBox - pos2y,
  ZposPBox - pos2z);
  
  G4double aPlane = XposBoxCombined - pos2x;
  G4double bPlane = YposPBox - pos2y;
  G4double cPlane = ZposPBox - pos2z;
  G4double dPlane = -(aPlane*XposBoxCombined + bPlane*YposPBox + cPlane*ZposPBox);
  // plane equation is: aPlane*x + bPlane*y + cPlane*z + dPlane = 0

  // G4cout << "a = " << aPlane << "; b = " << bPlane << "; c = " << cPlane << "; d = " << dPlane << "\n";

  G4ThreeVector planeXdef(bPlane, -aPlane, 0);
  G4ThreeVector planeYdef(normalDirCenter.cross(planeXdef)); //not checked

  std::vector <G4double> 
  intX, intY, intZ, 
  disPlaceX, disPlaceY, disPlaceZ, 
  intPlaneX, intPlaneY;

  for(G4int i = 0; i < 8; i++)
  {
    G4double t = -dPlane/(aPlane*dirX[i] + bPlane*dirY[i] + cPlane*dirZ[i]);
    t = -(aPlane*pos2x + bPlane*pos2y + cPlane*pos2z + dPlane)/(aPlane*dirX[i] + bPlane*dirY[i] + cPlane*dirZ[i]);

    intX.push_back(pos2x + dirX[i]*t);
    intY.push_back(pos2y + dirY[i]*t);
    intZ.push_back(pos2z + dirZ[i]*t);

    // G4cout << "intX = " << intX[i] << "; intY = " << intY[i] << "; intZ = " << intZ[i] << "\n";

    G4ThreeVector newdir(intX[i] - pos2x, intY[i] - pos2y, intZ[i] - pos2z);
    fParticleGun->SetParticleMomentumDirection(newdir);
	  // fParticleGun->GeneratePrimaryVertex(event);

    disPlaceX.push_back(intX[i] - XposBoxCombined);
    disPlaceY.push_back(intY[i] - YposPBox);
    disPlaceZ.push_back(intZ[i] - ZposPBox);

    G4ThreeVector disPlace(disPlaceX[i], disPlaceY[i], disPlaceZ[i]);

    intPlaneX.push_back(disPlace.dot(planeXdef)/planeXdef.mag());
    intPlaneY.push_back(disPlace.dot(planeYdef)/planeYdef.mag());
  }

  //! Convex hull algorithm
  Point points[] = {{intPlaneX[0], intPlaneY[0]}, 
  {intPlaneX[1], intPlaneY[1]},
  {intPlaneX[2], intPlaneY[2]},
  {intPlaneX[3], intPlaneY[3]},
  {intPlaneX[4], intPlaneY[4]},
  {intPlaneX[5], intPlaneY[5]},
  {intPlaneX[6], intPlaneY[6]},
  {intPlaneX[7], intPlaneY[7]}};
  G4int n = sizeof(points) / sizeof(points[0]);
  convexHull(points, n);

  //! K40
  fParticleGun->SetParticleEnergy(1.460822*MeV);
	// fParticleGun->GeneratePrimaryVertex(event);

  //! Get X', Y' coordinates in order
  std::vector <G4double> newintX, newintY, newintZ, newintPlaneX, newintPlaneY;
  for (G4int l = 0; l < hullSize; l++)
  {
    for (G4int i = 0; i < 8; i++)
    {
      if (intPlaneX[i] == hull[l].x && intPlaneY[i] == hull[l].y)
      {
        G4cout << "2D coordinates: \n(" << hull[l].x << ", " << hull[l].y << ") \n";
        G4cout << "3D coordinates: \n(" << intX[i] << ", " << intY[i] << ", " << intZ[i] << ") \n";
        newintPlaneX.push_back(intPlaneX[i]);
        newintPlaneY.push_back(intPlaneY[i]);

        newintX.push_back(intX[i]);
        newintY.push_back(intY[i]);
        newintZ.push_back(intZ[i]);
      }
    }
  }

  // G4cout << "size = " << newintPlaneX.size() << "\n";
  // G4cout << "size = " << newintPlaneY.size() << "\n";

  // G4cout << "size = " << newintX.size() << "\n";
  // G4cout << "size = " << newintY.size() << "\n";
  // G4cout << "size = " << newintZ.size() << "\n";

  for (G4int i = 0; i < newintX.size(); i++)
  {
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(newintX[i] - pos2x, newintY[i] - pos2y, newintZ[i] - pos2z));
	  // fParticleGun->GeneratePrimaryVertex(event);
  }
  
  // for (G4int i = 0; i < hullSize; i++)
  // {
  //   if(i != hullSize -1)
  //   { // connect newint i and newint i + 1
  //     G4cout << "hullpoint " << i + 1 << " = (" << newintX[i] << ", " << newintY[i] << ", " << newintZ[i] << ") and "
  //   << "hullpoint " << i + 2 << " = (" << newintX[i+1] << ", " << newintY[i+1] << ", " << newintZ[i+1] << ")\n";
  //   }
  //   else
  //   {// connect last newint i and newint 0
  //     G4cout << "hullpoint " << i + 1 << " = (" << newintX[i] << ", " << newintY[i] << ", " << newintZ[i] << ") and "
  //   << "hullpoint 0 = (" << newintX[0] << ", " << newintY[0] << ", " << newintZ[0] << ")\n";
  //   }
  // }

  G4double phirand;
  
}