#include "MyEventAction.hh"

void MyEventAction::BeginOfEventAction(const G4Event* event)
	{
		fDEdep = 0.;
		fDEdepL = 0.;
		fDEdepR = 0.;
		
		fEdep = 0.;
		fEdepL = 0.;
		fEdepR = 0.;

		fcomptCount = 0;
		backEDep = 0.;

		comptEDep.clear();
			
		aBSCheck = false;
		AllStepInfo = "Info: ";
	}
void MyEventAction::EndOfEventAction(const G4Event* event)
	{
		G4int EventsID = event->GetEventID();
		
		// Conditions for verbosity
		// if (fDEdep > 0.)
		// {
		// 	G4cout << "Compton Scattering Interactions: " << fcomptCount << "\n";
		// 	G4cout << AllStepInfo << "\n";
		// 	G4cout << "Event Number: " << EventsID +1 << "\n";
		// 	G4cout << "; Delta E: " << fDEdep << "MeV; E: " << fEdep << "MeV" << "\n"
		// 	G4cout << "\n" << "----- End of event " << EventsID +1 << " -----" << "\n";
		// }

		
		
		// Condition for recording Back-Scattered Comptons
		if (fDEdep > 0. && aBSCheck == true)
		{
			backEDep = fDEdep;
		}

		// Condition for recording Compton Scattering Count and Dep
		if (fcomptCount > 0)
		{
			comptEDep.resize(fcomptCount);
			for (G4int i = 0; i <= fcomptCount - 1; i++)
			{
				comptEDep[i] = 0.;
			}
			comptEDep[fcomptCount - 1] = fDEdep;
		}
		else
		{
			comptEDep.push_back(-1.);
		}
		G4cout << "Event ID: "<< EventsID << "\n";
		// G4cout << "Random:" << (2*((rand() % 10) % 2) - 1) << "\n";
		// G4cout << "Event Number: " << EventsID << "; fDEdep: " << fDEdep <<
		// "; fDEdepL: " << fDEdepL << "; fDEdepR: " << fDEdepR << 
		// "; fEdep: " << fEdep << "; fEdepL: " << fEdepL << "; fEdepR: " <<
		// fEdepR << "; fcomptCount: " << fcomptCount << "; comptEDep: " << 
		// comptEDep[0] << "; backEDep: " << backEDep << "\n";
		
		MyTreeHandler* aTreeHandler = MyTreeHandler::GetInstance();
    	aTreeHandler->Push(EventsID, fDEdep, fDEdepL, fDEdepR, fEdep, 
		fEdepL, fEdepR, fcomptCount, comptEDep, backEDep);
	}
