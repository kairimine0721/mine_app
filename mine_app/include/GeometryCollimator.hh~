#ifndef GeometryCollimator_HH
#define GeometryCollimator_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
class G4LogicalVolume;
class G4VPhysicalVolume;

namespace cdtestripcamerageometry {

class GeometryCollimator {

public:
  GeometryCollimator() {};
  virtual ~GeometryCollimator() {};
  
  virtual G4LogicalVolume* Construct(G4ThreeVector *pos);

private:

  void DefineMaterials() {};
  void SetupGeometry() {};
  
};

}

#endif

