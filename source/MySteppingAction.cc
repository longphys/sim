#include "MySteppingAction.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction) : G4UserSteppingAction(),
  fEventAction(eventAction),
  fEScoringVolume(),
  fDEScoringVolume()
{}

MySteppingAction::~MySteppingAction()
{}

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
  if (volume == fDEScoringVolume[0])
  {
    if (ProcessName == "compt" && TrackID == 1)
    {
      fEventAction->AddComptCount();
    }
  }

	//! EDep conditions
  for(int i = 0; i < 7; i++){
    if(volume == fDEScoringVolume[i]){
      fEventAction->AddDEdep(EdepStep, i);
    }
    else if(volume == fEScoringVolume[i]){
      fEventAction->AddEdep(EdepStep, i);
    }
  }
  
	// Information
  if (VolumeName == "physScint1" && EdepStep > 100.*keV){
    StepInfo = "--- Particle: " + ParticleName + "; Process Name: " + ProcessName + " ---" + "\n" +
    "Parent ID: " + ParentID + "; Track ID: " + TrackID + "; Step Number: " + StepNumber + "\n" 
    "Volume Name: " + VolumeName + "; Next Volume Name: " + NextVolumeName + "\n" +
    "Total Energy: " + TotalEnergy + "(MeV); TotalKineticEnergy: " + TotalKineticEnergy + "\n" +
    "(MeV); TotalEnergyAfter: " + TotalEnergyAfter + "(MeV); E: " + EdepStep + "MeV" + "\n";
    fEventAction->AddInfo(StepInfo);
  }
	
	// Checking the Ray tracing condition
	// if (NextVolumeName == "physPBox" or NextVolumeName == "physSBox")
	// {
	// 	track->SetTrackStatus(fStopAndKill);
	// }

  return;
}