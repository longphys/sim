#include "MySteppingAction.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction) : G4UserSteppingAction(),
  fEventAction(eventAction),
  fEScoringVolume(0),
  fEScoringVolume1(0),
  fEScoringVolume2(0),
  fDEScoringVolume(0),
  fDEScoringVolume1(0),
  fDEScoringVolume2(0)
{}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
	const MyDetectorConstruction* detectorConstruction
  	= static_cast<const MyDetectorConstruction*>
  	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	// Getting the scoring volumes
	if (!fDEScoringVolume) 
	{
  	fDEScoringVolume = detectorConstruction->GetScoringVolumeDE();
  }

	if (!fDEScoringVolume1) 
	{
  	fDEScoringVolume1 = detectorConstruction->GetScoringVolumeDE1();
  }
	
	if (!fDEScoringVolume2) 
	{
  	fDEScoringVolume2 = detectorConstruction->GetScoringVolumeDE2();
  }
	
  if (!fEScoringVolume) 
	{ 
  	fEScoringVolume = detectorConstruction->GetScoringVolumeE();   
  }

	if (!fEScoringVolume1) 
	{ 
  	fEScoringVolume1 = detectorConstruction->GetScoringVolumeE1();   
  }
	
	if (!fEScoringVolume2) 
	{ 
  	fEScoringVolume2 = detectorConstruction->GetScoringVolumeE2();   
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

	// Energy before and after the process
	G4double TotalEnergy;
	if (step->GetPreStepPoint()->GetTotalEnergy())
	{
		TotalEnergy = step->GetPreStepPoint()->GetTotalEnergy();
	}

	G4double TotalEnergyAfter = step->GetPostStepPoint()->GetTotalEnergy();

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
	
	if (VolumeName == "physPMT" || VolumeName == "physPMTL" || VolumeName == "physPMTR")
	{
		if (ParticleName == "gamma" && ProcessName == "compt" && TotalEnergy == 0.662)
		{
   			fEventAction->SwitchBS();
		}
	}

	// EDep conditions
  if (volume == fDEScoringVolume)
  {
		// Conditions for counting compt
    if (ProcessName == "compt" && TrackID == 1)
    {
      fEventAction->AddComptCount();
    }
		fEventAction->AddDEdep(EdepStep);
  }
	else if (volume == fDEScoringVolume1)
  {
    fEventAction->AddDEdepL(EdepStep);
  }
	else if (volume == fDEScoringVolume2)
  {
    fEventAction->AddDEdepR(EdepStep);
  }
	else if (volume == fEScoringVolume)
  {
    fEventAction->AddEdep(EdepStep);
  }
	else if (volume == fEScoringVolume1)
  {
    fEventAction->AddEdepL(EdepStep);
  }
  else if (volume == fEScoringVolume2)
  {
    fEventAction->AddEdepR(EdepStep);
  }
	// Verbosity
	StepInfo = "--- Particle: " + ParticleName + "; Process Name: " + ProcessName + " ---" + "\n" +
	"Parent ID: " + ParentID + "; Track ID: " + TrackID + "; Step Number: " + StepNumber + "\n" 
	"Volume Name: " + VolumeName + "; Next Volume Name: " + NextVolumeName + "\n" +
	"Total Energy: " + TotalEnergy + "; TotalEnergyAfter: " + TotalEnergyAfter + "; E: " + EdepStep + "MeV" + "\n";
	fEventAction->AddInfo(StepInfo);
	
	// Checking the Ray tracing condition
	// if (NextVolumeName == "physPBox" or NextVolumeName == "physSBox")
	// {
	// 	track->SetTrackStatus(fStopAndKill);
	// }

  return;
}