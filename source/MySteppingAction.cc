#include "MySteppingAction.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction) : G4UserSteppingAction(),
  fEventAction(eventAction),
  fEScoringVolume(),
  fDEScoringVolume()
{}

MySteppingAction::~MySteppingAction()
{}

G4double MySteppingAction::BirksAttenuation(const G4Step* step)
{
  //Example of Birk attenuation law in organic scintillators.
  //adapted from Geant3 PHYS337. See MIN 80 (1970) 239-244
  
  const G4Material* material = step->GetTrack()->GetMaterial();
  std::string materialName = material->GetName();
  G4double destep      = step->GetTotalEnergyDeposit()*MeV;
  G4double stepl       = step->GetStepLength()*mm;  
  G4double charge      = step->GetTrack()->GetDefinition()->GetPDGCharge();
  //
  G4double response = destep;
  // G4double scintillator_efficiency = 0.94; //! BC408
  // G4double scintillator_efficiency = 1.24; //! BC404
  // G4double scintillator_efficiency = 1.5; //! BC400
  // G4double scintillator_efficiency = 1.140; //! Polystyrene
  // G4double scintillator_efficiency = 0.94; //! TEST1 //! best fit for high energy proton recoil //! 10% diff, birk2 = 0., 
  G4double scintillator_efficiency = 0.925; //! TEST1 //! best fit for high energy proton recoil //! 10% diff, birk2 = 0., 
  // G4double scintillator_efficiency = 1.0; //! TEST1
  // G4double scintillator_efficiency = 0.95; //! TEST1 birk2
  // G4double scintillator_efficiency = 0.87; //! TEST2
  // G4double scintillator_efficiency = 0.9; //! TEST3
  // G4double scintillator_efficiency = 0.65; //! TEST4

  //!

  //! Setting Birk's constant
  G4double Birks_BC400 = 0.207;
  G4double Birks_BC404 = 0.155;
  G4double Birks_BC408 = 0.088;
  G4double Birks_Polystyrene = 0.126;

  G4double Birks_test1 = 0.08; //! best fit for high energy proton recoil //! 10% diff, birk2 = 0., 
  G4double Birks_test2 = 0.055;
  G4double Birks_test3 = 0.07;
  G4double Birks_test4 = 0.01;
  
  G4double birk1 = Birks_test1*mm/MeV;
  G4double birk1_alpha = Birks_test1*mm/MeV;
  // G4double birk1_alpha = 0.8/10.;
  // G4double birk1_alpha = 0.08*2.;
  // G4double birk1_alpha = 0.08*20.;
  // G4double birk1_alpha = 0.08*80.; //!
  // G4double birk1_alpha = 0.08*200.;
  // G4double birk2       = 0.008*40.; //!
  // G4double birk2       = 0.;
  // G4double birk2       = Birks_test1*0.08; //! 9,1%
  G4double birk2       = Birks_test1*0.2; //! 5%, for scintillator_efficiency*18.0 0.1%
  // G4double birk2       = Birks_test1*0.3; //! 5% for scintillator_efficiency*20.0
  // G4double birk2       = 0.008*10.;
  // G4double scintillator_efficiency_alpha = scintillator_efficiency; //! best fit for high energy proton recoil //! 10% diff, birk2 = 0., scintillator yield alpha = scintillator yield proton
  // G4double scintillator_efficiency_alpha = scintillator_efficiency*14.0; //! 9,1%, for birk_test1*0.2 5%
  G4double scintillator_efficiency_alpha = scintillator_efficiency*18.0; //! for birk_test1*0.2 0.1%
  // G4double scintillator_efficiency_alpha = scintillator_efficiency*20.0; //! 5% for Birks_test1*0.3
  // G4double scintillator_efficiency_alpha = scintillator_efficiency*4.0; //!
  // G4double scintillator_efficiency_alpha = 10.*2.; //!
  // G4double scintillator_efficiency_alpha = 10.*20.; 

  //! Wright
  G4double wright = 0.406; //! BC408

  //! Cecil
  double a = 0.693;
  double b = 3.0;
  double c = 0.2;
  double d = 0.965;

  if (material->GetIonisation()->GetBirksConstant() != 0.){
    if (destep > 0 && stepl > 0 && charge!=0 )
    {
      if (abs(charge) >= 2){
        // response = (scintillator_efficiency*destep)/(1. + birk1_alpha*destep/stepl);
        response = (scintillator_efficiency_alpha*destep)/(1. + birk1_alpha*destep/stepl + birk2*(destep/stepl)*(destep/stepl));
      }
      else{
        response = (scintillator_efficiency*destep)/(1. + birk1*destep/stepl);
        // response = (scintillator_efficiency*destep)/(1. + birk1*destep/stepl + birk2*(destep/stepl)*(destep/stepl));
      }
      // response = (scintillator_efficiency*destep)/(1. + birk1*destep/stepl);
      // response = (scintillator_efficiency*destep)/(1. + birk1*destep/stepl + birk2*(destep/stepl)*(destep/stepl));
      // response = (scintillator_efficiency*destep)/(1. + birk2*(destep/stepl)*(destep/stepl));
      // response = scintillator_efficiency*destep/(wright*destep/stepl)*log(1+wright*destep/stepl);
      // response = a*destep-b*(1-exp(-c*pow(destep,d)));
    }
  }
  return response;
}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
	const MyDetectorConstruction* detectorConstruction
  	= static_cast<const MyDetectorConstruction*>
  	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	// Getting the scoring volumes
  for(int i = 0; i < 7; i++){
    if (!fDEScoringVolume[i]) 
    {
      fDEScoringVolume[i] = detectorConstruction->GetScoringVolumeDE(i);
    }
    if (!fEScoringVolume[i]) 
    { 
      fEScoringVolume[i] = detectorConstruction->GetScoringVolumeE(i);   
    }
  }

	G4LogicalVolume* volume = step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume();

  // energy deposited in this step
  G4double EdepStep = step->GetTotalEnergyDeposit();

  G4Track* track = step->GetTrack();

  G4String StepInfo;

  G4String ParticleName = track->GetParticleDefinition()->GetParticleName();
  G4String ProcessTypeName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessTypeName(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessType());
  G4String ProcessName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  std::string VolumeName = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();

	//! Energy before and after the process
	G4double TotalEnergy;
	if (step->GetPreStepPoint()->GetTotalEnergy())
	{
		TotalEnergy = step->GetPreStepPoint()->GetTotalEnergy()*MeV;
	}

  G4double TotalKineticEnergy = track->GetKineticEnergy();

	G4double TotalEnergyAfter = step->GetPostStepPoint()->GetTotalEnergy()*MeV;

	std::string NextVolumeName = "";
	if (track->GetNextVolume())
	{
		NextVolumeName = track->GetNextVolume()->GetName();
	}
  //G4String ProcessName = step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName();
  G4int ParentID = track->GetParentID();
  G4int TrackID = track->GetTrackID();
  G4int StepNumber = track->GetCurrentStepNumber();

	// bool for BackScatter
	// if (VolumeName == "physPMT" || VolumeName == "physPMTL" || VolumeName == "physPMTR")
	// {
	// 	if (ParticleName == "gamma" && ProcessName == "compt" && TotalEnergy == 0.662)
	// 	{
  //  			fEventAction->SwitchBS();
	// 	}
	// }

  //! Conditions for counting compt
  if (volume == fDEScoringVolume[0]){
    if (ProcessName == "compt" && TrackID == 1){
      fEventAction->AddComptCount();
    }
  }

	 if (VolumeName == "physSurface"){
    if (TotalEnergyAfter != TotalEnergy){
      fEventAction->CheckScatterWindow();
    }
  }

  //! Conditions for particles
  // if (volume == fDEScoringVolume[0]){
  //   fEventAction->AddParEdep(EdepStep, ParticleName, ParentID);
  // }

  // for(int i = 0; i < 7; i++){
  //   if (volume == fDEScoringVolume[i]){
  //     fEventAction->AddParEdep(EdepStep, ParticleName, i);
  //   }
  // }
	// //! EDep conditions
  // for(int i = 0; i < 7; i++){
  //   if(volume == fDEScoringVolume[i]){
  //     fEventAction->AddDEdep(EdepStep, i);
  //   }
  //   else if(volume == fEScoringVolume[i]){
  //     fEventAction->AddEdep(EdepStep, i);
  //   }
  // }

  //! Birk's attenuation
  const G4Material* material = step->GetTrack()->GetMaterial();
  G4double response = BirksAttenuation(step);
  std::string materialName = material->GetName();
  G4double birk1       = material->GetIonisation()->GetBirksConstant();
  G4double destep      = step->GetTotalEnergyDeposit()*MeV;
  G4double stepl       = step->GetStepLength()*mm;  
  G4double charge      = step->GetTrack()->GetDefinition()->GetPDGCharge();
  // G4cout << " Destep: " << EdepStep/keV << " keV"
  //       << " response after Birks: " << response/keV << " keV" << G4endl;
  
  //! EDep Par
  for(int i = 0; i < 7; i++){
    if (volume == fDEScoringVolume[i]){
      fEventAction->AddParEdep(response, ParticleName, i);
    }
  }
	//! EDep conditions
  for(int i = 0; i < 7; i++){
    if(volume == fDEScoringVolume[i]){
      if (ParticleName == "proton"){
        fEventAction->AddRawProton(EdepStep, i);
      }
    fEventAction->AddDEdep(EdepStep, i);
    }
    else if(volume == fEScoringVolume[i]){
      fEventAction->AddEdep(EdepStep, i);
    }
  }

  if(volume == fDEScoringVolume[0]){
    //! Track PID
    if(EdepStep!=0){
      if (ParticleName == "proton"){
        fEventAction->CheckProton();
      }
      if (ParticleName == "gamma"){
        fEventAction->CheckGamma();
      }
      if (ParticleName == "alpha"){
        fEventAction->CheckAlpha();
      }
      if (ParticleName == "C12"){
        fEventAction->CheckC12();
      }
    }
  }

	//! Information
     StepInfo = "--- Particle: " + ParticleName + "; Process Name: " + ProcessName + " ---" + "\n" +
     "Parent ID: " + ParentID + "; Track ID: " + TrackID + "; Step Number: " + StepNumber + "\n" 
     "Volume Name: " + VolumeName + "; Next Volume Name: " + NextVolumeName + "\n" +
     "Total Energy: " + TotalEnergy + "(MeV); TotalKineticEnergy: " + TotalKineticEnergy + "(MeV);" + "\n" +
     "TotalEnergyAfter: " + TotalEnergyAfter + "(MeV);" + "\n\n" + 

     "MaterialName: " + materialName + "; Birk's constant: " + birk1 + "\n" +
     "Step length: " + stepl + "; Particle charge: " + charge + "\n"+
     "E: " + EdepStep + "MeV; E(Birk): " + response*MeV + "MeV" + "\n";
     fEventAction->AddInfo(StepInfo);

	
	//! Checking the Ray tracing condition
	// if (NextVolumeName == "physScint" or NextVolumeName == "physScint1")
	// {
	// 	track->SetTrackStatus(fStopAndKill);
	// }

  return;
}
