#include <sstream>

#include "GeometryCollimatorMINE2.hh"

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
#include "G4Polyhedra.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"


using namespace mineapp;

void GeometryCollimatorMINE2::Construct(G4LogicalVolume* LocalWorld_Logical) {

  const bool surfaceCheck = false;
  G4double margin = 0.1*mm; 

  AHG4MaterialManager* mmanager = AHG4MaterialManager::GetAHG4MaterialManager();
  AHG4Material* air = mmanager->instantiate("Vacuum");	

  std::string matname;
  AHG4MaterialProperty* p;
  matname = "AHG4SGD.Tungsten";
  p = mmanager->RetrieveProperty("Tungsten");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* tungsten = mmanager->instantiate(matname);


  // Collimator //////////////////////


  double a0 = 0.136818181818*mm; //hole radius
  double d0 = 0.0224063646098*mm; //septa thickness
  int imax=3;
  int jmax=3;
  
  double offset_x = -(2.0*a0+d0)*((double)imax-1.0)/2.0;
  double offset_y = -(a0+d0/2.0)/0.57735027*((double)jmax-1.0)/2.0;

  
  //G4double Collimator_px = 16.95*mm;
  G4double Collimator_px = -offset_x;
  //G4double Collimator_py = 16.95*mm;
  G4double Collimator_py = -offset_y;
  //  G4double Collimator_pz = 10.44*mm;
  G4double Collimator_pz = 2.53361552021*mm; //hole length /2
  G4VSolid* Collimator_Solid = new G4Box("Collimator_Solid", Collimator_px, Collimator_py, Collimator_pz);

  
  const G4double zPlane[2] = {-(Collimator_pz+0.1*mm),Collimator_pz+0.1*mm};
  const G4double zInner[2] = {0.0*mm,0.0*mm};  
  const G4double zOuter[2] = {a0,a0};
  G4VSolid* hole_Solid = new G4Polyhedra("hole_Solid", 0.0*deg,360.0*deg, 6, 2, zPlane,zInner,zOuter);
  //  G4LogicalVolume* Collimator_Logical = new G4LogicalVolume(Collimator_Solid, tungsten, "Collimator_Logical");

  
  G4RotationMatrix rot_p1 = G4RotationMatrix();
  rot_p1.rotateZ(30.0*deg);



  
  G4SubtractionSolid *a[imax][jmax];

  for(int j=0;j<jmax;j++){    
    for(int i=0;i<imax;i++){      
      double sx = offset_x;
      double sy = offset_y;
      if(j%2){
	sx = sx + (a0+d0/2.0);
      }
      
      G4ThreeVector p(sx+(2.0*a0+d0)*(double)i,sy+(a0+d0/2.0)/0.57735027*(double)j,0);
      G4String name = "a" + std::to_string(i)+ std::to_string(j);
      std::cout << name << std::endl;
      if(i==0&&j==0){
	a[i][j] = new G4SubtractionSolid("a00",Collimator_Solid,hole_Solid,G4Transform3D(rot_p1, p));
      }else{

	if(i==0){
	  a[i][j] = new G4SubtractionSolid(name,a[imax-1][j-1],hole_Solid,G4Transform3D(rot_p1, p));
	}else{
	  a[i][j] = new G4SubtractionSolid(name,a[i-1][j],hole_Solid,G4Transform3D(rot_p1, p));
	}

      }
      
    }
  }
    
  //  G4SubtractionSolid *aaa = new G4SubtractionSolid("a2918",Collimator_Solid,hole_Solid,G4Transform3D(rot_p1, p1));
  G4LogicalVolume* Collimator_Logical = new G4LogicalVolume(a[imax-1][jmax-1], tungsten, "Collimator_Logical");
  
  
  G4VisAttributes* Collimator_Attributes = new G4VisAttributes(G4Colour::Red());
  Collimator_Attributes->SetForceSolid(true);  
  Collimator_Logical->SetVisAttributes(Collimator_Attributes);
  

  double pitch_x = -offset_x*2.0;
  double pitch_y = -offset_y*2.0;
  
  double s_x = 0.0*mm-28.0*pitch_x;
  double s_y = 0.0*mm-32.0*pitch_y;
  
  G4ThreeVector pos;
  
  for(int i=0;i<57;i++){ //8 15
    for(int j=0;j<65;j++){ //9 17
      std::string name = "Collimator"+std::to_string(i)+std::to_string(j);
      pos.setX(s_x+i*pitch_x);
      pos.setY(s_y+j*pitch_y);
      pos.setZ(Collimator_pz+1.0*mm);
      
      new G4PVPlacement(0, pos, Collimator_Logical, name, LocalWorld_Logical, false, 0, surfaceCheck);
    }
  }
  
}
