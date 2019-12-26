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

#include "NucleusPrimaryGen_3d_phantom.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"
#include "G4Ions.hh"
#include "G4IonTable.hh"
#include "G4RIsotopeTable.hh"

using namespace anl;
using namespace anlgeant4;

namespace mineapp
{

NucleusPrimaryGen_3d_phantom::NucleusPrimaryGen_3d_phantom()
  : m_Position0(0.0, 0.0, 0.0),
    m_RIZ(55), m_RIA(137), m_RIEnergy(0.0)
{
  add_alias("NucleusPrimaryGen_3d_phantom");
}

NucleusPrimaryGen_3d_phantom::~NucleusPrimaryGen_3d_phantom() = default;

ANLStatus NucleusPrimaryGen_3d_phantom::mod_startup()
{
  anlgeant4::BasicPrimaryGen::mod_startup();

  unregister_parameter("particle");
  setParticleName("");
  register_parameter(&m_Position0, "position", cm, "cm");
  set_parameter_description("Position of the source.");
  register_parameter(&m_RIZ, "atomic_number");
  set_parameter_description("Atomic number of the radioactive isotope.");
  register_parameter(&m_RIA, "mass_number");
  set_parameter_description("Mass number of the radioactive isotope.");
  register_parameter(&m_RIEnergy, "energy", keV, "keV");
  set_parameter_description("Excitation energy of the radioactive isotope. A value of 0 means the ground state of the nucleus.");

  //  register_parameter(&m_FileName, "input_file_name");
  //  std::cout << "m_FileName: " << m_FileName << std::endl;  
  //  register_parameter(&m_HistName, "histgram_name");

  register_parameter(&m_FileName, "Input file name");
  std::cout << "m_FileName: " << m_FileName << std::endl;  
  register_parameter(&m_HistName, "Histgram name");


  
  return AS_OK;
}

ANLStatus NucleusPrimaryGen_3d_phantom::mod_bgnrun()
{
  anlgeant4::BasicPrimaryGen::mod_bgnrun();

  std::cout << "m_FileName....: " << m_FileName << std::endl;  
  m_fin = new TFile(m_FileName.c_str());
  m_inputDistribution = (TH3 *)m_fin->Get(m_HistName.c_str());

  m_Xmin =  m_inputDistribution->GetXaxis()->GetXmin();
  m_Xmax =  m_inputDistribution->GetXaxis()->GetXmax();
  m_Ymin =  m_inputDistribution->GetYaxis()->GetXmin();
  m_Ymax =  m_inputDistribution->GetYaxis()->GetXmax();
  m_Zmin =  m_inputDistribution->GetZaxis()->GetXmin();
  m_Zmax =  m_inputDistribution->GetZaxis()->GetXmax();
  
  
  G4IonTable* ionTable = static_cast<G4IonTable*>(G4ParticleTable::GetParticleTable()->GetIonTable());
  G4ParticleDefinition* particle = 
    ionTable->GetIon(m_RIZ, m_RIA, m_RIEnergy);
  setDefinition(particle);
  
  //  G4double energy(0.0);
  //  G4ThreeVector direction(0.0, 0.0, 0.0);
  //  setPrimary(m_Position0, energy, direction);
  
  G4cout << "------------------------------ \n"
	 << "       RI Information \n"
	 << "      Name    " << particle->GetParticleName()       << '\n' 
	 << "      Type    " << particle->GetParticleType()       << '\n' 
	 << "       A      " << particle->GetAtomicMass()         << '\n' 
	 << "       Z      " << particle->GetAtomicNumber()       << '\n' 
	 << "   life time  " << particle->GetPDGLifeTime()/second << " sec\n"
	 << "------------------------------ \n"
	 << G4endl;
  
  return AS_OK;
}

  ANLStatus NucleusPrimaryGen_3d_phantom::mod_ana()
  {
    const G4ThreeVector position = samplePosition();

    //const G4ThreeVector direction = sampleDirection();
    //    const G4double energy = sampleEnergy();
    G4double energy(0.0);
    G4ThreeVector direction(0.0, 0.0, 0.0);
    setPrimary(position, energy, direction);
    
    //    if (PolarizationMode()==0) {
    //      setUnpolarized();
    //    }
    
    return BasicPrimaryGen::mod_ana();
  }
  
G4ThreeVector NucleusPrimaryGen_3d_phantom::samplePosition()
{

  G4ThreeVector m_Position;
  G4double posx, posy, posz;
  int xbin,ybin,zbin;

  while(1){
    posx = m_Xmin + G4UniformRand()*(m_Xmax-m_Xmin);
    posy = m_Ymin + G4UniformRand()*(m_Ymax-m_Ymin);
    posz = m_Zmin + G4UniformRand()*(m_Zmax-m_Zmin);
    xbin = m_inputDistribution->GetXaxis()->FindBin(posx);
    ybin = m_inputDistribution->GetYaxis()->FindBin(posy);
    zbin = m_inputDistribution->GetZaxis()->FindBin(posz);
    int value = m_inputDistribution->GetBinContent(xbin,ybin,zbin);
    
    if(value>0.){
      break;
    }else{
      continue;
    }
    
  }
  
  m_Position.setX(m_Position0.getX()+posx*cm);
  m_Position.setY(m_Position0.getY()+posy*cm);
  m_Position.setZ(m_Position0.getZ()+posz*cm);
  return m_Position0;
}
  
} /* namespace anlgeant4 */
