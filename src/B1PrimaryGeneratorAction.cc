
#include "B1PrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
{
  fParticleGun  = new G4GeneralParticleSource();
}

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
