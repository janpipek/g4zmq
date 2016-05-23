#include "PrimaryGeneratorAction.hh"

#include <G4GeneralParticleSource.hh>

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
}

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	fGps = new G4GeneralParticleSource();
}