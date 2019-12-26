#ifndef GeometryCollimatorTORAY1_HH
#define GeometryCollimatorTORAY1_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "GeometryCollimator.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace mineapp {

  class GeometryCollimatorTORAY1 : public GeometryCollimator{
    
  public:
    GeometryCollimatorTORAY1() {};
    virtual ~GeometryCollimatorTORAY1() {};
    
    void Construct(G4LogicalVolume* LocalWorld_Logical);
    
  private:
    
    void DefineMaterials() {};
    void SetupGeometry() {};
    
  };
  
}

#endif

