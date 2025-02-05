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
	G4ParticleDefinition *particle = particleTable->FindParticle("neutron");
	// G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

	G4ThreeVector pos1(0., 0., -zDis); // source position
	// G4ThreeVector pos1(0., 3.0*cm, -zDis); // source position
	// G4ThreeVector pos1(0., RH-1.5*cm, -zDis); // source position
	// G4ThreeVector pos1(0., 0.5*RH, -zDis); // source position
	// G4ThreeVector pos1(0., 2.5*RH, -zDis);
	
	fParticleGun->SetParticlePosition(pos1);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(14.1*MeV);
  // fParticleGun->SetParticleEnergy(1.*GeV); //! gamma 100keV for testing beam size
	
  // for (G4int i = 0; i < 1; i++)
  // {
    // G4double RHrand = RH*G4UniformRand();
    // G4double RHrand = RH*G4UniformRand()/10;
    // G4double RHrand = RH*G4UniformRand()/5;

    double mean_test = 0.;
    // double stdDev_test = 1.0;
    // double stdDev_test = pixel_side/2.355;
    // std::cout << "RandGaus = " << G4RandGauss::shoot(mean_test, stdDev_test) << "\n";

    double beam_sizefactor = 5.;
    double beam_sizefactorY = 5.;
    G4double RHrand = RH*G4UniformRand(); //! Uniform angle distribution
    // G4double RHrand = (RH)*abs( G4RandGauss::shoot(mean_test, stdDev_test) ); //! Gaussian angle distribution
    G4double phirand = twopi*G4UniformRand();

    G4double a = RHrand;
    G4double x = a*cos(phirand);
    G4double y = a*sin(phirand);
    // G4double y = a*sin(phirand)/beam_sizefactorY; //! Reduce beam size on y-axis
    G4double z = zPar;

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y + 3.5*cm, z));
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y - 7.5*cm, z));
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y - 8.5*cm, z));
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x , y - 8.1*cm, z)); //! best fit
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y - 8.0*cm, z));
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y - 7.9*cm, z));
    //? y + 3.5 cm
    //? y + 4 cm

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
