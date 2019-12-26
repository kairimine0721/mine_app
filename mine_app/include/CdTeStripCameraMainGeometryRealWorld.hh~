#ifndef CdTeStripCameraMainGeometryRealWorld_HH
#define CdTeStripCameraMainGeometryRealWorld_HH

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserParallelWorld.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"

namespace cdtestripcamerageometry {

class CdTeStripCameraMainGeometryRealWorld : public G4VUserDetectorConstruction {

public:
  CdTeStripCameraMainGeometryRealWorld(std::string detname);
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
	
};

}
#endif
