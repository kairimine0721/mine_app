#ifndef GeometryCollimatorLEHR_HH
#define GeometryCollimatorLEHR_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "GeometryCollimator.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace mineapp {

  class GeometryCollimatorLEHR : public GeometryCollimator{
    
  public:
    GeometryCollimatorLEHR() {};
    virtual ~GeometryCollimatorLEHR() {};
    
    void Construct(G4LogicalVolume* LocalWorld_Logical);
    
  private:
    
    void DefineMaterials() {};
    void SetupGeometry() {};
    
  };
  
}

#endif

