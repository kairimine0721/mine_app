#! /usr/bin/env ruby

require 'comptonsoft/basic'

require 'mINEapp'
include MINEapp

def run_simulation(num, random)
  energy = 79.3 # keV
  posx = 0.0 #cm
  posy = 0.0 #cm
  posz = 12.188 #cm
  radius = 0.00001 #cm 5.0
  
 dirx = 0
 diry = 0
 dirz = -1.0
 thetamax = 0.26179933#0.26179933
#  thetamax = 0.5

  output = "ps_MINE1_collimator_ene#{energy}_posx#{posx}cm_posy#{posy}cm_poz#{posz}cm_seed#{random}.root"

  sim = ComptonSoft::Simulation.new
  sim.output = output
  sim.random_seed = random
  sim.verbose = 0


  sim.detector_config = "/Users/exp/simulation/IPMUCdTeStrip/database/detector_configuration.xml"
  sim.simulation_param = "/Users/exp/simulation/IPMUCdTeStrip/simdatabase/simulation_parameters.xml"
  sim.analysis_param = "/Users/exp/simulation/IPMUCdTeStrip/database/analysis_parameters.xml"
  
  sim.set_physics(hadron_hp: false, cut_value: 0.001)
  sim.set_physics(radioactive_decay: true)

  sim.set_geometry :CdTeStripCameraMainGeometry, {
                     "Collimator Name" => "MINE1",
                     "Detector Name" => "CdTe",
                     "Water Sphere Center" => vec(posx,posy,posz),
                     "Water Sphere Radius" => radius,
  }  
  
  sim.set_primary_generator :PointSourcePrimaryGen, {
    particle: "gamma",
    photon_index: 0.0,
    energy_min: energy,
    energy_max: energy,
    position: vec(posx, posy, posz),
    direction: vec(dirx, diry, dirz),
    theta_min: 0.0,
    theta_max: thetamax,
  }

#  sim.set_primary_generator :OISTPrimaryGen2DPhantom, {
#    particle: "gamma",
#    photon_index: 0.0,
#    energy_min: energy,
#    energy_max: energy,
#    "Source position" => vec(posx, posy, posz),
#    "Center direction" => vec(dirx, diry, dirz),
#    "theta min" => 0.0,
#    "theta max" => thetamax,
#    "Input file name" => "Phantom2D.root",
#    "Histgram name" => "phantom",
#
#  }
  
  
  #sim.set_primary_generator :NucleusPrimaryGenInVolume, {
  #  atomic_number: 56,
  #  mass_number: 133,
  #  energy: 0.0,
  #  volume_hierarchy: ["Collimator00"]
  #}
  
  
 # sim.set_primary_generator :NucleusPrimaryGen_2d_phantom, {
 #   atomic_number: 85,
 #   mass_number: 211,
 #   energy: 0.0,
 #   position: vec(posx, posy, posz),
 #   "Input file name" => "Phantom2D.root",
 #   "Histgram name" => "phantom",
 # }
  
  
  #  sim.set_primary_generator :OISTPrimaryGen3DPhantom, {
#    particle: "geantino",
#    photon_index: 0.0,
#    energy_min: energy,
#    energy_max: energy,
#    "Source position" => vec(posx, posy, posz),
#    "Center direction" => vec(dirx, diry, dirz),
#    "theta min" => 0.0,
#    "theta max" => thetamax,
#    "Input file name" => "Phantom3D.root",
#    "Histgram name" => "phantom",  
#
#  }
  
  #sim.visualize(mode: 'OGLSQt')
  sim.run(num)
end

### main ###
num = 1000000
run_id = ARGV[0].to_i
random = run_id
run_simulation(num, random)
