#include "MyPrimaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() :G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
	fParticleGun = new G4ParticleGun();
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *event)
{
	const MyDetectorConstruction* detectorConstruction
  	= static_cast<const MyDetectorConstruction*>
  	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

// Active source
	G4double RH = detectorConstruction->GetRH(); // Get RH from Detector Construction (it is in milimeter)
	G4double HH = 0.75*RH;
  G4double HC = 0.5*HH;
  G4double trapA = detectorConstruction->GettrapA();
	G4double zPar = (trapA/sin(60*deg)/2) + (HH+HC)/2;
	G4double zDis = zPar - (HH+HC)/2;

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

	G4ThreeVector pos1(0., 0., -zPar); // source position
	
	fParticleGun->SetParticlePosition(pos1);
	fParticleGun->SetParticleEnergy(.662*MeV);
  // G4double parE = 1*G4UniformRand();
  // if(parE <= 0.5){
  //   fParticleGun->SetParticleEnergy(1.173*MeV);
  // }
  // else{
  //   fParticleGun->SetParticleEnergy(1.332*MeV);
  // }
	fParticleGun->SetParticleDefinition(particle);

	G4double random = G4UniformRand();
	
  for (G4int i = 0; i < 1; i++)
  {
    G4double RHrand = RH*G4UniformRand();
    G4double phirand = twopi*G4UniformRand();

    G4double a = RHrand;
    G4double x = a*cos(phirand);
    G4double y = a*sin(phirand);
    G4double z = zDis;

    // fParticleGun->SetNumberOfParticles(4);
    // random = 0.1;
    if (random < (1./3.))
    {
      G4ThreeVector* zTrans = new G4ThreeVector(x, y, z);

      fParticleGun->SetParticleMomentumDirection(zTrans->rotateY(-120*deg));
      fParticleGun->GeneratePrimaryVertex(event);
    }
    else if (random > (2./3.))
    {
      G4ThreeVector* zTrans = new G4ThreeVector(x, y, z);

      fParticleGun->SetParticleMomentumDirection(zTrans->rotateY(120*deg));
      fParticleGun->GeneratePrimaryVertex(event);
    }
    else
    {	
      fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
      fParticleGun->GeneratePrimaryVertex(event);
    }
  }
// Ray tracing problem
	// G4Box* solidPBox = detectorConstruction->GetSolidPBox();
  // G4Box* solidSBox = detectorConstruction->GetSolidSBox();
	// G4VPhysicalVolume* physPBox = detectorConstruction->GetPhysPBox();

	// G4double pBoxDepth = 2*solidPBox->GetXHalfLength();
  // G4double sBoxDepth = 2*solidSBox->GetXHalfLength();
	// G4double bWidth = 2*solidPBox->GetYHalfLength();
	// G4double bHeight = 2*solidPBox->GetZHalfLength();

	// G4ThreeVector posPBox = physPBox->GetTranslation();
  // G4double XposPBox = posPBox.getX();
  // G4double YposPBox = posPBox.getY();
  // G4double ZposPBox = posPBox.getZ();

	// G4double dWorld = detectorConstruction->GetSolidWorld()->GetXHalfLength();

	// G4double pos2x, pos2y, pos2z;

  // pos2x = (2*G4UniformRand() - 1)*dWorld;
	// pos2y = (2*G4UniformRand() - 1)*dWorld;
	// pos2z = (2*G4UniformRand() - 1)*dWorld;

	// if(random < (1./3.))
	// {		
	// 	if(pos2x < dWorld && pos2x > -dWorld)
	// 	{
	// 		pos2y = (2*((rand() % 10) % 2) - 1)*dWorld;
	// 	}
	// }
	// else if(random > (2./3.))
	// {		
	// 	if(pos2y < dWorld && pos2y > -dWorld)
	// 	{
	// 		pos2z = (2*((rand() % 10) % 2) - 1)*dWorld;
	// 	}
	// }
	// else
	// {
	// 	if(pos2z < dWorld && pos2z > -dWorld)
	// 	{
	// 		pos2x = (2*((rand() % 10) % 2) - 1)*dWorld;
	// 	}
	// }

  // // pos2x = dWorld;
	// // pos2y = dWorld;
	// // pos2z = dWorld;
  // // Vertices 3D
  // std::vector <G4double> verX, verY, verZ;
  // verX.push_back(XposPBox + pBoxDepth/2.); verY.push_back(YposPBox + bWidth/2.); verZ.push_back(ZposPBox + bHeight/2.);
  // verX.push_back(XposPBox + pBoxDepth/2.); verY.push_back(YposPBox + bWidth/2.); verZ.push_back(ZposPBox - bHeight/2.);
  // verX.push_back(XposPBox + pBoxDepth/2.); verY.push_back(YposPBox - bWidth/2.); verZ.push_back(ZposPBox + bHeight/2.);
  // verX.push_back(XposPBox + pBoxDepth/2.); verY.push_back(YposPBox - bWidth/2.); verZ.push_back(ZposPBox - bHeight/2.);
  // verX.push_back(XposPBox - pBoxDepth/2. - sBoxDepth); verY.push_back(YposPBox + bWidth/2.); verZ.push_back(ZposPBox + bHeight/2.);
  // verX.push_back(XposPBox - pBoxDepth/2. - sBoxDepth); verY.push_back(YposPBox + bWidth/2.); verZ.push_back(ZposPBox - bHeight/2.);
  // verX.push_back(XposPBox - pBoxDepth/2. - sBoxDepth); verY.push_back(YposPBox - bWidth/2.); verZ.push_back(ZposPBox + bHeight/2.);
  // verX.push_back(XposPBox - pBoxDepth/2. - sBoxDepth); verY.push_back(YposPBox - bWidth/2.); verZ.push_back(ZposPBox - bHeight/2.);

  // std::vector <G4double> dirX, dirY, dirZ;

  // for(G4int i = 0; i < 8; i++)
  // {
  //   // G4cout << "verX[" << i << "]: " << verX[i] 
  //   // << "; verY[" << i << "]: " << verY[i] 
  //   // << "; verZ[" << i << "]: " << verZ[i] << "\n";

  //   dirX.push_back(verX[i] - pos2x);
  //   dirY.push_back(verY[i] - pos2y);
  //   dirZ.push_back(verZ[i] - pos2z);

  //   G4ThreeVector pos2(pos2x, pos2y, pos2z);
  //   G4ThreeVector dir(dirX[i], dirY[i], dirZ[i]);
  //   fParticleGun->SetParticlePosition(pos2);
  //   fParticleGun->SetParticleMomentumDirection(dir);
	//   // fParticleGun->GeneratePrimaryVertex(event);
  // }

  // G4double XposBoxCombined = XposPBox - sBoxDepth/2; // middle point of combined box

  // G4ThreeVector normalDirCenter
  // (XposBoxCombined - pos2x,
  // YposPBox - pos2y,
  // ZposPBox - pos2z);
  
  // G4double aPlane = XposBoxCombined - pos2x;
  // G4double bPlane = YposPBox - pos2y;
  // G4double cPlane = ZposPBox - pos2z;
  // G4double dPlane = -(aPlane*XposBoxCombined + bPlane*YposPBox + cPlane*ZposPBox);
  // // plane equation is: aPlane*x + bPlane*y + cPlane*z + dPlane = 0
    
  // // G4cout << "a = " << aPlane << "; b = " << bPlane << "; c = " << cPlane << "; d = " << dPlane << "\n";

  // G4ThreeVector planeXdef(bPlane, -aPlane, 0);
  // G4ThreeVector planeYdef(normalDirCenter.cross(planeXdef)); //not checked

  // std::vector <G4double> 
  // intX, intY, intZ, 
  // disPlaceX, disPlaceY, disPlaceZ, 
  // intPlaneX, intPlaneY;

  // for(G4int i = 0; i < 8; i++)
  // {
  //   G4double t = -dPlane/(aPlane*dirX[i] + bPlane*dirY[i] + cPlane*dirZ[i]);
  //   t = -(aPlane*pos2x + bPlane*pos2y + cPlane*pos2z + dPlane)/(aPlane*dirX[i] + bPlane*dirY[i] + cPlane*dirZ[i]);

  //   intX.push_back(pos2x + dirX[i]*t);
  //   intY.push_back(pos2y + dirY[i]*t);
  //   intZ.push_back(pos2z + dirZ[i]*t);

  //   // G4cout << "intX = " << intX[i] << "; intY = " << intY[i] << "; intZ = " << intZ[i] << "\n";

  //   G4ThreeVector newdir(intX[i] - pos2x, intY[i] - pos2y, intZ[i] - pos2z);
  //   fParticleGun->SetParticleMomentumDirection(newdir);
	//   // fParticleGun->GeneratePrimaryVertex(event);

  //   disPlaceX.push_back(intX[i] - XposBoxCombined);
  //   disPlaceY.push_back(intY[i] - YposPBox);
  //   disPlaceZ.push_back(intZ[i] - ZposPBox);

  //   G4ThreeVector disPlace(disPlaceX[i], disPlaceY[i], disPlaceZ[i]);

  //   intPlaneX.push_back(disPlace.dot(planeXdef)/planeXdef.mag());
  //   intPlaneY.push_back(disPlace.dot(planeYdef)/planeYdef.mag());

  //   // G4cout << "X' = " << intPlaneX[i] <<  "; Y' = " << intPlaneY[i] << "\n";

  // }

  // Point points[] = {{intPlaneX[0], intPlaneY[0]}, 
  // {intPlaneX[1], intPlaneY[1]},
  // {intPlaneX[2], intPlaneY[2]},
  // {intPlaneX[3], intPlaneY[3]},
  // {intPlaneX[4], intPlaneY[4]},
  // {intPlaneX[5], intPlaneY[5]},
  // {intPlaneX[6], intPlaneY[6]},
  // {intPlaneX[7], intPlaneY[7]}};
  // G4int n = sizeof(points) / sizeof(points[0]);
  // convexHull(points, n);
  
  // std::vector <G4double> newintX, newintY, newintZ;
  //   for (G4int l = 0; l < hullSize; l++)
  //   {
  //     for (G4int i = 0; i < 8; i++)
  //     {
  //       if (intPlaneX[i] == hull[l].x && intPlaneY[i] == hull[l].y)
  //       {
  //         newintX.push_back(intX[i]);
  //         newintY.push_back(intY[i]);
  //         newintZ.push_back(intZ[i]);
  //       }
  //     }
  //   }

  // // G4cout << "size = " << newintX.size() << "\n";
  // // G4cout << "size = " << newintY.size() << "\n";
  // // G4cout << "size = " << newintZ.size() << "\n";

  // auto maxX = std::max_element(newintX.begin(), newintX.end());
  // auto maxY = std::max_element(newintY.begin(), newintY.end());
  // auto minX = std::min_element(newintX.begin(), newintX.end());
  // auto minY = std::min_element(newintY.begin(), newintY.end());

  // // for (G4int i = 0; i < newintX.size(); i++)
  // // {
  // //   G4cout << "newintX[" << i << "] = " << newintX[i] << "; newintY[" << i << "] = " << newintY[i] << "; newintZ[" << i << "] = " << newintZ[i] << "\n";
  // //   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(newintX[i] - pos2x, newintY[i] - pos2y, newintZ[i] - pos2z));
	// //   fParticleGun->GeneratePrimaryVertex(event);
  // // }

  // // G4cout << "maxX = " << *maxX << "; maxY = " << *maxY << "; maxZ = " << -(aPlane*(*maxX) + bPlane*(*maxY) + dPlane)/cPlane << "\n";
  // // G4cout << "minX = " << *minX << "; minY = " << *minY << "; minZ = " << -(aPlane*(*minX) + bPlane*(*minY) + dPlane)/cPlane << "\n";  
  
  // G4double x = (*maxX - *minX)*G4UniformRand() + *minX;
  // G4double y = (*maxY - *minY)*G4UniformRand() + *minY;
  // G4double z = (aPlane*x + bPlane*y + dPlane)/-cPlane;
  // // z = 190;
  
  // // G4cout << "x = " << x << "; y = " << y << "; z = " << z << "\n";
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x - pos2x, y - pos2y, z - pos2z));
  // fParticleGun->SetParticleEnergy(1.460*MeV);
	// // fParticleGun->GeneratePrimaryVertex(event);
  
  // // for (G4int i = 0; i < hullSize; i++)
  // // {
    
  // //   if(i != hullSize -1)
  // //   {
  // //     G4cout << "hullpoint " << i + 1 << " = " << hull[i].x << "; " << hull[i].y << " and "
  // //   << "hullpoint " << i + 2 << " = " << hull[i+1].x << "; " << hull[i+1].y << "\n";
  // //   // connect newint i and newint i + 1
  // //   }
  // //   else
  // //   {
  // //     G4cout << "hullpoint " << i + 1 << hull[i].x << "; " << hull[i].y << " and "
  // //   << "hullpoint 0 " << hull[0].x << "; " << hull[0].y << "\n";
  // //   }
  // //   // connect last newint i and newint 0
  // // }
  
}