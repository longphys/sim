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
  //
  const G4Material* material = step->GetTrack()->GetMaterial();
  G4double birk1       = material->GetIonisation()->GetBirksConstant();
  G4double destep      = step->GetTotalEnergyDeposit();
  G4double stepl       = step->GetStepLength();  
  G4double charge      = step->GetTrack()->GetDefinition()->GetPDGCharge();
  //
  G4double response = destep;
  G4double scintillator_efficiency = 1.0;

  if (birk1*destep*stepl*charge != 0.)
  {
    response = scintillator_efficiency*destep/(1. + birk1*destep/stepl);
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
  G4double response = BirksAttenuation(step);
  const G4Material* material = step->GetTrack()->GetMaterial();
  std::string materialName = material->GetName();
  G4double birk1       = material->GetIonisation()->GetBirksConstant();
  G4double destep      = step->GetTotalEnergyDeposit();
  G4double stepl       = step->GetStepLength();  
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
      fEventAction->AddDEdep(response, i);
    }
    else if(volume == fEScoringVolume[i]){
      fEventAction->AddEdep(response, i);
    }
  }

	//! Information
    StepInfo = "--- Particle: " + ParticleName + "; Process Name: " + ProcessName + " ---" + "\n" +
    "Parent ID: " + ParentID + "; Track ID: " + TrackID + "; Step Number: " + StepNumber + "\n" 
    "Volume Name: " + VolumeName + "; Next Volume Name: " + NextVolumeName + "\n" +
    "Total Energy: " + TotalEnergy + "(MeV); TotalKineticEnergy: " + TotalKineticEnergy + "(MeV);" + "\n" +
    "TotalEnergyAfter: " + TotalEnergyAfter + "(MeV);" + "\n\n" + 

    "MaterialName: " + materialName + "; Birk's constant: " + birk1 + "\n" +
    "Step length: " + stepl + "\n" +
    "E: " + EdepStep + "MeV; E(Birk): " + response/MeV + "MeV" + "\n";
    fEventAction->AddInfo(StepInfo);

	
	// Checking the Ray tracing condition
	// if (NextVolumeName == "physPBox" or NextVolumeName == "physSBox")
	// {
	// 	track->SetTrackStatus(fStopAndKill);
	// }

  return;
}