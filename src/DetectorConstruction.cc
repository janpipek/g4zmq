#include "DetectorConstruction.hh"

#include <G4Sphere.hh>
#include <G4Box.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>

G4VPhysicalVolume* DetectorConstruction::Construct() 
{
    G4NistManager* nist = G4NistManager::Instance();

    G4Material* boxMaterial = nist->FindOrBuildMaterial("G4_WATER");    
    G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld = new G4Box("World", 1 * m, 1 * m, 1 * m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMaterial, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, {}, logicWorld, "World", 0, false, 0);

    G4Box* solidCube = new G4Box("Box", 10 * cm, 10 * cm, 10 *cm);
    G4LogicalVolume* logicCube = new G4LogicalVolume(solidCube, boxMaterial, "Box");
    new G4PVPlacement(nullptr, {0, 0, 20 * cm}, logicCube, "Box", logicWorld, false, 0);

    return physWorld;
}

// Implement the following only if you have fields / sensitive detector
/*
void DetectorConstruction::ConstructSDandField()
{

}
*/