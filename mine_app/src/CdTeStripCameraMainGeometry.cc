#include "CdTeStripCameraMainGeometry.hh"
#include "CdTeStripCameraMainGeometryRealWorld.hh"

using namespace anl;
using namespace anlgeant4;
using namespace mineapp;

ANLStatus CdTeStripCameraMainGeometry::mod_startup() {

  register_parameter(&m_CollimatorName, "Collimator Name");
  set_parameter_description("Collimator Type (Type1, Type2, Type3 ......) ");
    
  register_parameter(&m_DetectorName, "Detector Name");
  set_parameter_description("Detector Type (Type1, Type2, Type3 ......) ");
    
  register_parameter(&w_sphere_center, "Water Sphere Center");

  register_parameter(&w_radius, "Water Sphere Radius");
  
  return AS_OK;

}

G4VUserDetectorConstruction* CdTeStripCameraMainGeometry::create() {
  G4VUserDetectorConstruction* theGeometry = new CdTeStripCameraMainGeometryRealWorld(m_CollimatorName, m_DetectorName, w_sphere_center, w_radius);
  return theGeometry;
}
