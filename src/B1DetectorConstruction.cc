//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* water   = nist->FindOrBuildMaterial("G4_WATER");
  G4Material* air     = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* silicon = nist->FindOrBuildMaterial("G4_Si");

  G4bool checkOverlaps = true;

  // Useful variable
  G4String name;

  // World
  name ="World";
  const G4double halfWorldSize = 10*m;
  G4VSolid* world_sol = new G4Box(name,halfWorldSize,halfWorldSize,halfWorldSize);
  G4LogicalVolume* world_log = new G4LogicalVolume(world_sol,air,name);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VPhysicalVolume* world_phys
  = new G4PVPlacement(G4Transform3D(),       // Placement (defines world/global coordinates)
                      world_log,             //its logical volume
                      name,                  //its name
                      0,                     //its mother volume (no mother - it's the world)
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  // Water attenuator
  name = "Water";
  const G4double halfWaterSize  = 50*cm;
  const G4double halfWaterDepth = 10*cm;
  const G4double waterZ         = 50*cm;
  G4VSolid* water_sol = new G4Box(name,halfWaterSize,halfWaterSize,halfWaterDepth);
  G4LogicalVolume* water_log = new G4LogicalVolume(water_sol,water,name);
  new G4PVPlacement(G4Translate3D(0.,0.,waterZ),  // Placement in world
                    water_log,             //its logical volume
                    name,                  //its name
                    world_log,             //its mother, the world
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

  // Detector
  name = "Detector";
  const G4double halfDetectorSize  = 5*mm;
  const G4double halfDetectorDepth = 1*mm;
  const G4double detectorZ         = 100*cm;
  G4VSolid* detector_sol = new G4Box(name,halfDetectorSize,halfDetectorSize,halfDetectorDepth);
  G4LogicalVolume* detector_log = new G4LogicalVolume(detector_sol,silicon,name);
  fScoringVolume = detector_log;
  new G4PVPlacement(G4Translate3D(0.,0.,detectorZ),  // Placement in world
                    detector_log,          //its logical volume
                    name,                  //its name
                    world_log,             //its mother, the world
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

  // Detector as scoring volume
  fScoringVolume = detector_log;

  return world_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
