#ifndef CdTeStripCameraMainGeometry_H
#define CdTeStripCameraMainGeometry_H 1
#include "G4ThreeVector.hh"

#include "VANLGeometry.hh"

class G4VUserDetectorConstruction;

namespace mineapp {

class CdTeStripCameraMainGeometry : public anlgeant4::VANLGeometry
{
  DEFINE_ANL_MODULE(CdTeStripCameraMainGeometry, 1.0);

public:
  CdTeStripCameraMainGeometry() {}
  virtual ~CdTeStripCameraMainGeometry() {}
  
  anl::ANLStatus mod_startup();

  G4VUserDetectorConstruction* create();

private:
  std::string m_CollimatorName;
  std::string m_DetectorName;
  G4ThreeVector w_sphere_center;
  double w_radius;

};

}

#endif /* CdTeStripCameraMainGeometry_H */
