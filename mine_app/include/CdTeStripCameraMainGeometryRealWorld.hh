#ifndef CdTeStripCameraMainGeometryRealWorld_HH
#define CdTeStripCameraMainGeometryRealWorld_HH

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserParallelWorld.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"

namespace mineapp {

class CdTeStripCameraMainGeometryRealWorld : public G4VUserDetectorConstruction {

public:
  CdTeStripCameraMainGeometryRealWorld(std::string colname, std::string detname, G4ThreeVector pos, double radius);
  virtual ~CdTeStripCameraMainGeometryRealWorld() {};
  
  virtual G4VPhysicalVolume* Construct();
  void Initialize();
  
private:
  void DefineMaterials() {};
  void SetupGeometry();

  G4int constructed;
  G4LogicalVolume* World_Logical;
  G4VPhysicalVolume* World_Physical;
  std::string m_CollimatorName;
  std::string m_DetectorName;
  G4ThreeVector w_sphere_center;
  double w_radius;
	
};

}
#endif
