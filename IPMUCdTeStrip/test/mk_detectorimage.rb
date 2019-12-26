#!/usr/bin/env ruby

#require 'cslib'
require 'comptonsoft/basic'
include ComptonSoft

require 'oISTapp'
include OISTapp


#hittreefiles = Dir.glob( "hittree.root" )
#comptreefile = ARGV[0]

#hittreefiles = Dir.glob("20161125_cam1_00021_001_hittree.root")
#hittreefiles = Dir.glob("ht*.root")
infile = ARGV[0]
ld = ARGV[1]
ud = ARGV[2]
hittreefiles = [infile]
imagefile = infile + ".image" +ld + "to" + ud + ".root"

ld = ARGV[1].to_f
ud = ARGV[2].to_f

detector_config = "/Users/exp/simulation/OISTCdTeStrip/database/detector_configuration.xml"

anl = ANL::ANLApp.new
anl.chain :CSHitCollection
anl.chain :ConstructDetector
anl.chain :ReadHitTree
anl.chain :OISTDetectorImage
anl.chain :SaveData

anl.set_parameters :ConstructDetector, {
  detector_configuration: detector_config,
}

anl.set_parameters :ReadHitTree, {
  file_list: hittreefiles,
}

anl.set_parameters :OISTDetectorImage, {
  energy_min: ld,
  energy_max: ud,
}

anl.set_parameters :SaveData, {
  output: imagefile,
}

anl.run(-1, 10000)

