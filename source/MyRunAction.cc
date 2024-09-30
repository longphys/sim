#include "MyRunAction.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  timer->Start();

	MyTreeHandler* aTreeHandler = MyTreeHandler::GetInstance();
	aTreeHandler->Open();
	G4cout
	<< "\n"
	<< "-------------------Begin of Run----------------------"
	<< "\n";
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
	G4cout
	<< "--------------------End of Run-----------------------"
	<< "\n";
	
	G4int nofEvents = run->GetNumberOfEvent();
	
	G4cout 
	<< "\n"
	<< "Total number of events: " << nofEvents 
	<< "\n";
	
	MyTreeHandler* aTreeHandler = MyTreeHandler::GetInstance();
  	aTreeHandler->Close();

  timer->Stop();
  std::cout << "Time elapsed: " << timer->GetRealElapsed() << "(s)\n";
}
