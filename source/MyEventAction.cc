#include "MyEventAction.hh"

void MyEventAction::BeginOfEventAction(const G4Event* event)
	{
    fDEdep.clear();
    fDEdep.resize(7,0.);
    fEdep.clear();
    fEdep.resize(7,0.);
		
    // fDEdep = 0.;
    // fEdep = 0.;
    
		fcomptCount = 0;
		backEDep = 0.;

		comptEDep.clear();

    neutronEDep.clear();
    neutronEDep.resize(7,0.);
    protonEDep.clear();
    protonEDep.resize(7,0.);
    protonEDepRaw.clear();
    protonEDepRaw.resize(7,0.);
    gammaEDep.clear();
    gammaEDep.resize(7,0.);
    alphaEDep.clear();
    alphaEDep.resize(7,0.);
    C12EDep.clear();
    C12EDep.resize(7,0.);
    otherEDep.clear();
    otherEDep.resize(7,0.);

    // neutronEDep = 0.;
    // protonEDep = 0.;
    // gammaEDep = 0.;
    // alphaEDep = 0.;
    // C12EDep = 0.;
    // otherEDep = 0.;
			
		aBSCheck = false;
    protonCheck = false;
    gammaCheck = false;
    alphaCheck = false;
    c12Check = false;
    scatterWindowCheck = false;

		AllStepInfo = "Info: ";
	}
void MyEventAction::EndOfEventAction(const G4Event* event)
	{
		int EventsID = event->GetEventID();

    if( (EventsID % 10000) == 0){
      std::cout << "EVENT ID: "<< EventsID << "\n";
    }
    
    std::cout << "Number of events interacting with Steel window: "<< countScatterWindow << "\n";

    // G4cout << "\n-----EVENT ID: "<< EventsID << "-----\n";
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

    //! Check Particles
    if (fDEdep[0] < 0.8 && fDEdep[0] > 0.2){
      // G4cout << "##### EVENT ID: "<< EventsID << " #####" << G4endl;
      // G4cout << AllStepInfo << "\n";
    }

    if (protonCheck == true){
      countProtonTotal ++;
      if (alphaCheck == true & c12Check == false){
        countProtonAlpha++;
      }
      else{
        countProton++;
      }
    }
    
    if (scatterWindowCheck == true){
    	countScatterWindow++;
    }

    // if((EventsID % 10000) == 0){  
    //   std::cout << "only proton = " << countProton << "\n";
    //   std::cout << "proton alpha double scattering = " << countProtonAlpha << "\n";
    //   std::cout << "there is proton = " << countProtonTotal << "\n";
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
    	aTreeHandler->Push(EventsID, fDEdep, fEdep, fcomptCount, comptEDep, backEDep, neutronEDep, protonEDep, protonEDepRaw, gammaEDep, alphaEDep, C12EDep, otherEDep);
	}
