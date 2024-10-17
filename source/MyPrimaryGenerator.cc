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
	RH = 3.5/2*cm;
	// RH = RH+5.0*cm;
	G4double HH = detectorConstruction->GetHH();
  G4double HC = detectorConstruction->GetHC();
	G4double zPar = 37.*cm;
	G4double zDis = zPar + (HH+HC)/2;
	// G4double zDis = zPar - (HH+HC)/2;

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("neutron");

	G4ThreeVector pos1(0., 0., -zDis); // source position
	
	fParticleGun->SetParticlePosition(pos1);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(14.1*MeV);

	G4double random = G4UniformRand();
	
  // for (G4int i = 0; i < 1; i++)
  // {
    G4double RHrand = RH*G4UniformRand();
    G4double phirand = twopi*G4UniformRand();

    G4double a = RHrand;
    G4double x = a*cos(phirand);
    G4double y = a*sin(phirand);
    G4double z = zPar;

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
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