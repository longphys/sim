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

	G4double RH = detectorConstruction->GetRH(); //! Get RH from Detector Construction (it is in milimeter)
  double pixel_side = 3.0*cm;

	RH = pixel_side;
	// RH = (pixel_side/2);
	// RH = (pixel_side/4);
  //? radius - 5. mm
  //? radius - 10. mm
  //? radius + 5.0*cm;
	G4double HH = detectorConstruction->GetHH();
  G4double HC = detectorConstruction->GetHC();
	G4double zDis = zPar + (HH+HC)/2;
	// G4double zDis = zPar - (HH+HC)/2;

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	// G4ParticleDefinition *particle = particleTable->FindParticle("neutron");

  G4IonTable* ionTable = G4IonTable::GetIonTable();
  int A = 18;
  int Z = 8;
	G4ParticleDefinition *particle = ionTable->GetIon(Z, A, 0);

  double mean_test = 0.;
  // double stdDev_test = 1.0;
  double stdDev_test = pixel_side/2.355;
  G4double RHrand = RH*G4UniformRand(); //! Uniform angle distribution
  // G4double RHrand = (RH)*abs( G4RandGauss::shoot(mean_test, stdDev_test) ); //! Gaussian angle distribution
  G4double phirand = twopi*G4UniformRand();

  G4double a = RHrand;
  G4double x = a*cos(phirand);
  G4double y = a*sin(phirand);

	G4ThreeVector pos1(x, y, -200*cm); // source position
	
	fParticleGun->SetParticlePosition(pos1);
  fParticleGun->SetParticleDefinition(particle);
  double enegery_of_each_nucleon = 33; //! MeV
  fParticleGun->SetParticleEnergy(enegery_of_each_nucleon*A*MeV);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1));
  fParticleGun->GeneratePrimaryVertex(event);

  //! 4PI
  // G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
  // G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  // G4double ux = sinTheta*std::cos(phi),
  // uy = sinTheta*std::sin(phi),
  // uz = cosTheta;
  // fParticleGun->SetParticleEnergy(1.274537*MeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
  // fParticleGun->GeneratePrimaryVertex(event);
}
