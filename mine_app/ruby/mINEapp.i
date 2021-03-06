%module mINEapp
%{

#include "NucleusPrimaryGen_2d_phantom.hh"
#include "NucleusPrimaryGen_3d_phantom.hh"
#include "CdTeStripCameraMainGeometry.hh"
#include "class_list_anlGeant4.hh"

%}

%import "anlGeant4.i"

namespace mineapp {

  class NucleusPrimaryGen_2d_phantom : public anlgeant4::BasicPrimaryGen
  {
  public:
    NucleusPrimaryGen_2d_phantom();    
  };

  class NucleusPrimaryGen_3d_phantom : public anlgeant4::BasicPrimaryGen
  {
  public:
    NucleusPrimaryGen_3d_phantom();    
  };
  

  class CdTeStripCameraMainGeometry : public anlgeant4::VANLGeometry
  {
  public:
   CdTeStripCameraMainGeometry() {}
   virtual ~CdTeStripCameraMainGeometry() {}
   
  };
  
}

