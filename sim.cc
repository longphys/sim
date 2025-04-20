#include "G4MTRunManager.hh"
#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "G4VisManager.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "MyDetectorConstruction.hh"
#include "MyPhysicsList.hh"
#include "MyActionInitialization.hh"
#include "MyTreeHandler.hh"

#include "QBBC.hh"
#include "QGSP_INCLXX.hh"
#include "G4StepLimiterPhysics.hh"

MyTreeHandler* MyTreeHandler::fTreeHandlerPtr = NULL;

int main (int argc, char** argv)
{
	#ifdef G4MULTITHREADED
  		G4MTRunManager* runManager = new G4MTRunManager;
	#else
  		G4RunManager* runManager = new G4RunManager;
	#endif
	
	//runManager->SetUserInitialization(new MyPhysicsList());

	// Physics list is QBBC
	// G4VModularPhysicsList* physicsList = new QBBC;
	G4VModularPhysicsList* physicsList = new QGSP_INCLXX;
	physicsList->SetVerboseLevel(0);
	runManager->SetUserInitialization(physicsList);
  // G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
  // stepLimitPhys->SetApplyToAll(true);
  // physicsList->RegisterPhysics(stepLimitPhys);

	runManager->SetUserInitialization(new MyDetectorConstruction());

	G4UIExecutive *ui = 0;
	if(argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	
	// User action initialization
	runManager->SetUserInitialization(new MyActionInitialization());
	//runManager->Initialize();

	// ui = new G4UIExecutive(argc, argv); // For now ui is always turned on
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(ui)
	{
		UImanager->ApplyCommand("/control/execute vis.mac");

		ui->SessionStart();
		//delete ui;
	}
	else
	{
		// UImanager->ApplyCommand("/control/execute vis.mac");
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}

	delete visManager;
  delete runManager;
}