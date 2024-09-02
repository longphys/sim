#include "MySteppingAction.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction) : G4UserSteppingAction(),
  fEventAction(eventAction),
  fEScoringVolume(0),
  fEScoringVolume1(0),
  fEScoringVolume2(0),
  fEScoringVolume3(0),
  fEScoringVolume4(0),
  fEScoringVolume5(0),
  fEScoringVolume6(0),

  fDEScoringVolume(0),
  fDEScoringVolume1(0),
  fDEScoringVolume2(0),
  fDEScoringVolume3(0),
  fDEScoringVolume4(0),
  fDEScoringVolume5(0),
  fDEScoringVolume6(0)
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
		
	if (!fDEScoringVolume3) 
	{
  	fDEScoringVolume3 = detectorConstruction->GetScoringVolumeDE3();
  }
		
	if (!fDEScoringVolume4) 
	{
  	fDEScoringVolume4 = detectorConstruction->GetScoringVolumeDE4();
  }
		
	if (!fDEScoringVolume5) 
	{
  	fDEScoringVolume5 = detectorConstruction->GetScoringVolumeDE5();
  }
		
	if (!fDEScoringVolume6) 
	{
  	fDEScoringVolume6 = detectorConstruction->GetScoringVolumeDE6();
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

	if (!fEScoringVolume3) 
	{ 
  	fEScoringVolume3 = detectorConstruction->GetScoringVolumeE3();   
  }
	
	if (!fEScoringVolume4) 
	{ 
  	fEScoringVolume4 = detectorConstruction->GetScoringVolumeE4();   
  }

	if (!fEScoringVolume5) 
	{ 
  	fEScoringVolume5 = detectorConstruction->GetScoringVolumeE5();   
  }
	
	if (!fEScoringVolume6) 
	{ 
  	fEScoringVolume6 = detectorConstruction->GetScoringVolumeE6();   
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
    fEventAction->AddDEdep1(EdepStep);
  }
	else if (volume == fDEScoringVolume2)
  {
    fEventAction->AddDEdep2(EdepStep);
  }
	else if (volume == fDEScoringVolume3)
  {
    fEventAction->AddDEdep3(EdepStep);
  }
	else if (volume == fDEScoringVolume4)
  {
    fEventAction->AddDEdep4(EdepStep);
  }
	else if (volume == fDEScoringVolume5)
  {
    fEventAction->AddDEdep5(EdepStep);
  }
	else if (volume == fDEScoringVolume6)
  {
    fEventAction->AddDEdep6(EdepStep);
  }
	else if (volume == fEScoringVolume)
  {
    fEventAction->AddEdep(EdepStep);
  }
	else if (volume == fEScoringVolume1)
  {
    fEventAction->AddEdep1(EdepStep);
  }
  else if (volume == fEScoringVolume2)
  {
    fEventAction->AddEdep2(EdepStep);
  }
  else if (volume == fEScoringVolume3)
  {
    fEventAction->AddEdep3(EdepStep);
  }
  else if (volume == fEScoringVolume4)
  {
    fEventAction->AddEdep4(EdepStep);
  }
  else if (volume == fEScoringVolume5)
  {
    fEventAction->AddEdep5(EdepStep);
  }
  else if (volume == fEScoringVolume6)
  {
    fEventAction->AddEdep6(EdepStep);
  }

	// Verbosity
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