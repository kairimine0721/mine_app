#ifndef GeometryCollimator_HH
#define GeometryCollimator_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
class G4LogicalVolume;
class G4VPhysicalVolume;

namespace mineapp {

class GeometryCollimator {

public:
  GeometryCollimator() {};
  virtual ~GeometryCollimator() {};
  
  virtual void Construct(G4LogicalVolume* LocalWorld_Logical);

private:

  void DefineMaterials() {};
  void SetupGeometry() {};
  
};

}

#endif

