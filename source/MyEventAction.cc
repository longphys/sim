#include "MyEventAction.hh"

void MyEventAction::BeginOfEventAction(const G4Event* event)
	{
    for(int i = 0; i < 7; i++){
      fDEdep[i] = 0.;
      fEdep[i] = 0.;
    }
		
		fcomptCount = 0;
		backEDep = 0.;

		comptEDep.clear();
    neutronEDep.clear();
    protonEDep.clear();
    gammaEDep.clear();
    otherEDep.clear();
			
		aBSCheck = false;
		AllStepInfo = "Info: ";
	}
void MyEventAction::EndOfEventAction(const G4Event* event)
	{
		G4int EventsID = event->GetEventID();

		G4cout << "Event ID: "<< EventsID << "\n";
		
		//! Conditions for verbosity
		// if (fDEdep > 0.)
		// {
		// 	G4cout << "Compton Scattering Interactions: " << fcomptCount << "\n";
    // G4cout << AllStepInfo << "\n";
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

    // const G4Run* run
    // = static_cast<const G4Run*>
    // (G4RunManager::GetRunManager()->GetCurrentRun());
    // double nofEvents = run->GetNumberOfEventToBeProcessed();

    // int barWidth = 50;
    // std::cout << "[";
    // int pos = barWidth * events/nofEvents;
    // for (int i = 0; i < barWidth; ++i) {
    //     if (i < pos) std::cout << "=";
    //     else if (i == pos) std::cout << ">";
    //     else std::cout << " ";
    // }
    // std::cout << "] " << int(events/nofEvents * 100.0) << "%\r";
    // std::cout.flush();

    // events += 1; // for demonstration only

		// G4cout << "Random:" << (2*((rand() % 10) % 2) - 1) << "\n";
		// G4cout << "Event Number: " << EventsID << "; fDEdep: " << fDEdep <<
		// "; fDEdepL: " << fDEdepL << "; fDEdepR: " << fDEdepR << 
		// "; fEdep: " << fEdep << "; fEdepL: " << fEdepL << "; fEdepR: " <<
		// fEdepR << "; fcomptCount: " << fcomptCount << "; comptEDep: " << 
		// comptEDep[0] << "; backEDep: " << backEDep << "\n";
		
		MyTreeHandler* aTreeHandler = MyTreeHandler::GetInstance();
    	aTreeHandler->Push(EventsID, fDEdep, fEdep, fcomptCount, comptEDep, backEDep, neutronEDep, protonEDep, gammaEDep, otherEDep);
	}
