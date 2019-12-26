#ifndef GeometryCollimatorTORAY1_HH
#define GeometryCollimatorTORAY1_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "GeometryCollimator.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace cdtestripcamerageometry {

  class GeometryCollimatorTORAY1 : public GeometryCollimator{
    
  public:
    GeometryCollimatorTORAY1() {};
    virtual ~GeometryCollimatorTORAY1() {};
    
    G4LogicalVolume* Construct(G4ThreeVector *pos);
    
  private:
    
    void DefineMaterials() {};
    void SetupGeometry() {};
    
  };
  
}

#endif

