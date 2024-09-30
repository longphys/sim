#ifndef MyRunAction_hh
#define MyRunAction_hh

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "MyTreeHandler.hh"
#include "G4Timer.hh"

class G4Run;

class MyRunAction: public G4UserRunAction
{
public:
    MyRunAction();
    virtual ~MyRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*); 
private:
  G4Timer* timer = new G4Timer();
};

#endif
