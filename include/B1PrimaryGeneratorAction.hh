#ifndef B1PrimaryGeneratorAction_hh
#define B1PrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class G4GeneralParticleSource;
class G4Event;

class B1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    B1PrimaryGeneratorAction();    
    virtual ~B1PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4GeneralParticleSource* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4GeneralParticleSource*  fParticleGun; // pointer a to G4 gun class
};

#endif
