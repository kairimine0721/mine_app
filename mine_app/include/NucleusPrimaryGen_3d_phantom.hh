/*************************************************************************
 *                                                                       *
 * Copyright (c) 2011 Hirokazu Odaka                                     *
 *                                                                       *
 * This program is free software: you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                       *
 *************************************************************************/

#ifndef ANLGEANT4_NucleusPrimaryGen_3d_phantom_H
#define ANLGEANT4_NucleusPrimaryGen_3d_phantom_H 1

#include "BasicPrimaryGen.hh"
#include "G4ThreeVector.hh"


#include "TFile.h"
#include "TH3.h"

class G4ParticleDefinition;

namespace mineapp {


/**
 * ANLGeant4 PrimaryGen module.
 * A nucleus is generated.
 *
 * @author Hirokazu Odaka
 * @date 2011-04-12
 */
class NucleusPrimaryGen_3d_phantom : public anlgeant4::BasicPrimaryGen
{
  DEFINE_ANL_MODULE(NucleusPrimaryGen_3d_phantom, 4.0);
public:
  NucleusPrimaryGen_3d_phantom();
  ~NucleusPrimaryGen_3d_phantom();

  virtual anl::ANLStatus mod_startup();
  virtual anl::ANLStatus mod_bgnrun();
  virtual anl::ANLStatus mod_ana();
  
private:
  G4ThreeVector m_Position0;
  G4int m_RIZ;
  G4int m_RIA;
  G4double m_RIEnergy;

  std::string m_FileName;
  TFile *m_fin;
  std::string m_HistName;
  TH3 *m_inputDistribution;

  G4double m_Xmin;
  G4double m_Xmax;
  G4double m_Ymin;
  G4double m_Ymax;
  G4double m_Zmin;
  G4double m_Zmax;

  G4ThreeVector samplePosition();
  
};

} /* namespace anlgeant4 */

#endif /* ANLGEANT4_NucleusPrimaryGen_3d_phantom_H */
