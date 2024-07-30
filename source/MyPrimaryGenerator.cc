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

	G4double RH = detectorConstruction->GetRH(); // Get RH from Detector Construction (it is in milimeter)
	G4double HH = detectorConstruction->GetHH();
  G4double HC = detectorConstruction->GetHC();
  G4double trapA = detectorConstruction->GettrapA();
	G4double zPar = (trapA/sin(60*deg)/2) + (HH+HC)/2;
	G4double zDis = zPar - (HH+HC)/2;

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

	G4ThreeVector pos1(0., 0., -zPar); // source position
	
	fParticleGun->SetParticlePosition(pos1);
  fParticleGun->SetParticleDefinition(particle);

  G4double parE = 1*G4UniformRand();

	G4double random = G4UniformRand();
	
  // for (G4int i = 0; i < 1; i++)
  // {
    G4double RHrand = RH*G4UniformRand();
    G4double phirand = twopi*G4UniformRand();

    G4double a = RHrand;
    G4double x = a*cos(phirand);
    G4double y = a*sin(phirand);
    G4double z = zDis;

  //   if (random < (1./3.))
  //   {
  //     G4ThreeVector* zTrans = new G4ThreeVector(x, y, z);

  //     fParticleGun->SetParticleMomentumDirection(zTrans->rotateY(-120*deg));
  //     fParticleGun->GeneratePrimaryVertex(event);
  //   }
  //   else if (random > (2./3.))
  //   {
  //     G4ThreeVector* zTrans = new G4ThreeVector(x, y, z);

  //     fParticleGun->SetParticleMomentumDirection(zTrans->rotateY(120*deg));
  //     fParticleGun->GeneratePrimaryVertex(event);
  //   }
  //   else
  //   {	
  //     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
  //     fParticleGun->GeneratePrimaryVertex(event);
  //   }
  // }

  G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi),
  uy = sinTheta*std::sin(phi),
  uz = cosTheta;

  //! Cs137
	// fParticleGun->SetParticleEnergy(.6616553*MeV);
  //! Co60
  if(parE < 0.500331777697933){
    fParticleGun->SetParticleEnergy(1.173492*MeV);
  }
  else{
    fParticleGun->SetParticleEnergy(1.332228*MeV);
  }
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
  fParticleGun->GeneratePrimaryVertex(event);

  // //! Na22 0.511 MeV Annihilation gamma
  // fParticleGun->SetParticleEnergy(0.511*MeV);

  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
  // fParticleGun->GeneratePrimaryVertex(event);

  // //! Na22 Second 0.511 MeV 
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-ux,-uy,-uz));
  // fParticleGun->GeneratePrimaryVertex(event);

  // //! Na22 1.2 MeV
  // fParticleGun->SetParticleEnergy(1.274537*MeV);
  // if(parE < 0.99){
  //   cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
  //   sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  //   ux = sinTheta*std::cos(phi),
  //   uy = sinTheta*std::sin(phi),
  //   uz = cosTheta;  
  //   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
  //   fParticleGun->GeneratePrimaryVertex(event);
  // }

  //! Na22 1.2 MeV
  // fParticleGun->SetParticleEnergy(1.274537*MeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
  fParticleGun->GeneratePrimaryVertex(event);
  
  // fParticleGun->SetParticleEnergy(0.511*MeV);
  // G4double odds = 0.92*(180.7/2.)*(100./99.94)/100;
  // if(parE < odds){
  //   //! Na22 0.511 MeV Annihilation gamma
  //   cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
  //   sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  //   ux = sinTheta*std::cos(phi),
  //   uy = sinTheta*std::sin(phi),
  //   uz = cosTheta;  
  //   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
  //   fParticleGun->GeneratePrimaryVertex(event);
  //   //! Na22 Second 0.511 MeV 
  //   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-ux,-uy,-uz));
  //   fParticleGun->GeneratePrimaryVertex(event);
  // }
}