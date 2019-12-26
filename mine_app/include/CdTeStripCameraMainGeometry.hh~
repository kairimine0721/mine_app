#ifndef CdTeStripCameraMainGeometry_H
#define CdTeStripCameraMainGeometry_H 1

#include "VANLGeometry.hh"

class G4VUserDetectorConstruction;

namespace cdtestripcamerageometry {

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

};

}

#endif /* CdTeStripCameraMainGeometry_H */
