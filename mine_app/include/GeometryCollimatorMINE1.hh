#ifndef GeometryCollimatorMINE1_HH
#define GeometryCollimatorMINE1_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "GeometryCollimator.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace mineapp {

  class GeometryCollimatorMINE1 : public GeometryCollimator{
    
  public:
    GeometryCollimatorMINE1() {};
    virtual ~GeometryCollimatorMINE1() {};
    
    void Construct(G4LogicalVolume* LocalWorld_Logical);
    
  private:
    
    void DefineMaterials() {};
    void SetupGeometry() {};
    
  };
  
}

#endif

