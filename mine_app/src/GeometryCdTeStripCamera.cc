#include <sstream>

#include "GeometryCdTeStripCamera.hh"
#include "AHG4MaterialManager.hh"

#include "GeometryCollimator.hh"
#include "GeometryCollimatorTORAY1.hh"
#include "GeometryCollimatorMINE1.hh"
#include "GeometryCollimatorMINE2.hh"
#include "GeometryCollimatorLEHR.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Sphere.hh"

using namespace mineapp;

G4LogicalVolume* GeometryCdTeStripCamera::Construct(std::string colname, std::string detname, G4ThreeVector w_sphere_center, double w_radius) {

  const bool surfaceCheck = false;
  //const bool surfaceCheck = true;
  G4double margin = 0.1*mm;  

  AHG4MaterialManager* mmanager = AHG4MaterialManager::GetAHG4MaterialManager();
  AHG4Material* air = mmanager->instantiate("Vacuum");
  std::string matname;
  AHG4MaterialProperty* p;

  matname = "AHG4SGD.CdTe";
  p = mmanager->RetrieveProperty("CdTe");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* cdte = mmanager->instantiate(matname);

  matname = "AHG4SGD.NaI";
  p = mmanager->RetrieveProperty("NaI");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* nai = mmanager->instantiate(matname);

  matname = "AHG4SGD.Aluminium";
  p = mmanager->RetrieveProperty("Aluminium");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* aluminium = mmanager->instantiate(matname);

  matname = "AHG4SGD.Cu";
  p = mmanager->RetrieveProperty("Cu");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* copper = mmanager->instantiate(matname);

  matname = "AHG4SGD.H2O";
  p = mmanager->RetrieveProperty("H2O");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* h2o = mmanager->instantiate(matname);

  
  // Local World //////////////////////
  G4double LocalWorld_xSize = 500.0*mm;
  G4double LocalWorld_ySize = 500.0*mm;
  G4double LocalWorld_zSize = 500.0*mm;
  G4VSolid* LocalWorld_Solid = new G4Box("LocalWorld_Solid", LocalWorld_xSize*0.5, LocalWorld_ySize*0.5, LocalWorld_zSize*0.5);
  G4LogicalVolume* LocalWorld_Logical = new G4LogicalVolume(LocalWorld_Solid, air, "LocalWorld_Logical");


 //======= CdTe-Double-sided Strip Ditector  ======
  G4double CdTe_DSD_xSize = 34.0*mm;
  G4double CdTe_DSD_ySize = 34.0*mm;
  G4double CdTe_DSD_zSize = 0.75*mm;
  G4VSolid* CdTe_DSD = new G4Box("CdTe_DSD", CdTe_DSD_xSize*0.5, CdTe_DSD_ySize*0.5, CdTe_DSD_zSize*0.5);
  
  G4LogicalVolume* CdTe_DSD_Logical;
  if(detname == "CdTe"){
    CdTe_DSD_Logical = new G4LogicalVolume(CdTe_DSD, cdte, "CdTe_DSD_Logical");
  }else if(detname == "NaI"){
    CdTe_DSD_Logical = new G4LogicalVolume(CdTe_DSD, nai, "CdTe_DSD_Logical");
  }else{
    CdTe_DSD_Logical = new G4LogicalVolume(CdTe_DSD, cdte, "CdTe_DSD_Logical");
  }
    
  G4double CdTe_DSD_xPos = 0.0*mm;
  G4double CdTe_DSD_yPos = 0.0*mm;
  G4double CdTe_DSD_zPos = 0.0*mm - 0.5*CdTe_DSD_zSize;
  new G4PVPlacement(0, G4ThreeVector(CdTe_DSD_xPos, CdTe_DSD_yPos, CdTe_DSD_zPos), CdTe_DSD_Logical, "CdTe_DSD", LocalWorld_Logical, false, 0, surfaceCheck);

  G4VisAttributes* cdtestrip_Attributes = new G4VisAttributes(G4Colour::Blue());
  cdtestrip_Attributes->SetForceSolid(surfaceCheck);
  CdTe_DSD_Logical->SetVisAttributes(cdtestrip_Attributes);
  
  //======= Collimator  ======

  GeometryCollimator* Collimator_Geometry;
  if(colname == "TORAY1"){
    Collimator_Geometry = new GeometryCollimatorTORAY1();
  }else if(colname == "MINE1"){
    Collimator_Geometry = new GeometryCollimatorMINE1();
  }else if(colname == "MINE2"){
    Collimator_Geometry = new GeometryCollimatorMINE2();
  }else if(colname == "LEHR"){
    Collimator_Geometry = new GeometryCollimatorLEHR();
  }else{
    Collimator_Geometry = new GeometryCollimator();
  }


  Collimator_Geometry->Construct(LocalWorld_Logical);

  //======= Water ========
  G4double inner_radius = 0.0*cm;
  G4double outer_radius = w_radius*cm;
  G4double segment_angle_phi_min = 0.0*deg;
  G4double segment_angle_phi_max = 360.0*deg;
  G4double segment_angle_theta_min = 0.0*deg;
  G4double segment_angle_theta_max = 360.0*deg;
  
  G4VSolid* Water = new G4Sphere("Water", inner_radius, outer_radius, segment_angle_phi_min, segment_angle_phi_max, segment_angle_theta_min, segment_angle_theta_max);
  G4LogicalVolume* Water_Logical = new G4LogicalVolume(Water, h2o, "Water_Logical");
  G4ThreeVector Water_Center =  w_sphere_center*cm;
  new G4PVPlacement(0, Water_Center, Water_Logical, "Water", LocalWorld_Logical, false, 0, surfaceCheck);  
  

  G4VisAttributes* water_Attributes = new G4VisAttributes(G4Colour::Cyan());
  water_Attributes->SetForceSolid(surfaceCheck);
  Water_Logical->SetVisAttributes(water_Attributes);
  
  return LocalWorld_Logical;
}
