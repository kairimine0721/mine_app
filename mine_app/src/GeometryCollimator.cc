#include <sstream>

#include "GeometryCollimator.hh"

#include "AHG4MaterialManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

using namespace mineapp;

void GeometryCollimator::Construct(G4LogicalVolume* LocalWorld_Logical) {

  const bool surfaceCheck = false;
  G4double margin = 0.1*mm; 

  AHG4MaterialManager* mmanager = AHG4MaterialManager::GetAHG4MaterialManager();
  AHG4Material* air = mmanager->instantiate("Vacuum");	
 
  // Null Collimator //////////////////////
  G4double Collimator_xSize = 50.0*mm;
  G4double Collimator_ySize = 50.0*mm;
  G4double Collimator_zSize = 20.0*mm;
  G4VSolid* Collimator_Solid = new G4Box("Collimator_Solid", Collimator_xSize*0.5, Collimator_ySize*0.5, Collimator_zSize*0.5);
  G4LogicalVolume* Collimator_Logical = new G4LogicalVolume(Collimator_Solid, air, "Collimator_Logical");

  G4VisAttributes* Collimator_Attributes = new G4VisAttributes(G4Colour::Red());
  Collimator_Attributes->SetForceSolid(surfaceCheck);
  Collimator_Logical->SetVisAttributes(Collimator_Attributes);

  G4ThreeVector pos;
  pos.setX(0.);
  pos.setY(0.);
  pos.setZ(50.0*mm);

  //new G4PVPlacement(0, pos, Collimator_Logical, "Collimator", LocalWorld_Logical, false, 0, surfaceCheck);
  
}
