#ifndef GeometryCdTeStripCamera_HH
#define GeometryCdTeStripCamera_HH
#include "G4ThreeVector.hh"

#include "globals.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace mineapp {

class GeometryCdTeStripCamera {

public:
  GeometryCdTeStripCamera() {};
  virtual ~GeometryCdTeStripCamera() {};
  
  G4LogicalVolume* Construct(std::string colname, std::string detname, G4ThreeVector w_sphere_center, double w_radius);

private:
  void DefineMaterials() {};
  void SetupGeometry() {};

};

}

#endif


