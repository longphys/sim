#include "MyEventAction.hh"

void MyEventAction::BeginOfEventAction(const G4Event* event)
	{
    for(int i = 0; i < 7; i++){
      fDEdep[i] = 0.;
      fEdep[i] = 0.;
    }
		
    // fDEdep = 0.;
    // fEdep = 0.;
    
		fcomptCount = 0;
		backEDep = 0.;

		comptEDep.clear();

    // neutronEDep.clear();
    // protonEDep.clear();
    // gammaEDep.clear();
    // alphaEDep.clear();
    // C12EDep.clear();
    // otherEDep.clear();

    neutronEDep = 0.;
    protonEDep = 0.;
    gammaEDep = 0.;
    alphaEDep = 0.;
    C12EDep = 0.;
    otherEDep = 0.;
			
		aBSCheck = false;
    protonCheck = false;

		AllStepInfo = "Info: ";
	}
void MyEventAction::EndOfEventAction(const G4Event* event)
	{
		G4int EventsID = event->GetEventID();

		G4cout << "++++++++++++++++EVENT ID: "<< EventsID << "+++++++++++++++++++++\n";
		
		//! Conditions for verbosity
		// if (fDEdep > 0.)
		// {
		// 	G4cout << "Compton Scattering Interactions: " << fcomptCount << "\n";
    G4cout << AllStepInfo << "\n";
		// 	G4cout << "Event Number: " << EventsID +1 << "\n";
		// 	G4cout << "; Delta E: " << fDEdep << "MeV; E: " << fEdep << "MeV" << "\n"
		// 	G4cout << "\n" << "----- End of event " << EventsID +1 << " -----" << "\n";
		// }
		
		//! Condition for recording Back-Scattered Comptons
		// if (fDEdep > 0. && aBSCheck == true)
		// {
		// 	backEDep = fDEdep;
		// }

		//! Condition for recording Compton Scattering Count and Dep
		if (fcomptCount > 0)
		{
			comptEDep.resize(fcomptCount);
			for (G4int i = 0; i <= fcomptCount - 1; i++)
			{
				comptEDep[i] = 0.;
			}
			comptEDep[fcomptCount - 1] = fDEdep[0]; //! Middle detector
		}
		else
		{
			comptEDep.push_back(-1.);
		}
		
		MyTreeHandler* aTreeHandler = MyTreeHandler::GetInstance();
    	aTreeHandler->Push(EventsID, fDEdep, fEdep, fcomptCount, comptEDep, backEDep, neutronEDep, protonEDep, gammaEDep, alphaEDep, C12EDep, otherEDep);
	}
