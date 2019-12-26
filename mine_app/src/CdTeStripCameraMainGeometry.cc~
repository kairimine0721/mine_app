#include "CdTeStripCameraMainGeometry.hh"
#include "CdTeStripCameraMainGeometryRealWorld.hh"

using namespace anl;
using namespace anlgeant4;
using namespace cdtestripcamerageometry;

ANLStatus CdTeStripCameraMainGeometry::mod_startup() {

  register_parameter(&m_CollimatorName, "Collimator Name");
  set_parameter_description("Collimator Type (Type1, Type2, Type3 ......) ");
  return AS_OK;

}

G4VUserDetectorConstruction* CdTeStripCameraMainGeometry::create() {
  G4VUserDetectorConstruction* theGeometry = new CdTeStripCameraMainGeometryRealWorld(m_CollimatorName);
  return theGeometry;
}
