#!/usr/bin/env python
import sys
import os
import subprocess
import numpy as np
import math
import pprint


def main(args):
    if len(args)<2: 
        print(' enter <height> <tag> ')
        exit(0)

    height = int(args[0]) 
    tag = args[1]     
    events = 10000
    macroname  = 'baconMapGenH%i-%s.mac' % (height,tag) 
    outputname = 'baconMapGenH%i-%s.root' % (height,tag)
    print(macroname,' ',outputname)
    exists = os.path.isfile(macroname)
    if exists:
        print('removing existing %s' %macroname)
        call='rm %s'% macroname
        os.system(call)
    # Load configuration file values
    # Load configuration file values
    f = open(macroname, 'w')
    print(f,' ',outputname)
    f.write('/MG/manager/mglog routine \n')
    f.write('/MG/manager/seedWithUUID\n')
    f.write('/MG/processes/realm DarkMatter\n')
    f.write('/MG/processes/lowenergy false\n')
    f.write('/MG/processes/opticalOnly true\n')
    f.write('/MG/geometry/detector BACON\n')
    f.write('/MG/BACON/SetLiquid Xenon-Doped-Argon-Liq\n')
    f.write('/run/initialize\n')
    f.write('/MG/eventaction/rootschema MCOpticalRun\n')
    f.write('/MG/eventaction/reportingfrequency 10\n')
    f.write('/MG/eventaction/rootfilename %s \n' % outputname)
    f.write('/MG/io/MCOpticalRun/SetSensitiveIDLabelScheme manual\n')
    f.write('/MG/io/MCOpticalRun/AddSensitiveVolnameID physicalPMT_0 100\n')
    f.write('/MG/io/MCOpticalRun/setRunID 001\n')
    f.write('/MG/io/MCOpticalRun/useTimeWindow true\n')
    f.write('/MG/io/MCOpticalRun/setTimeWindow 86400 second\n')
    f.write('/MG/io/MCOpticalRun/setNSteps 10000000000000\n')
    f.write('/MG/generator/select LGNDLiquidArgon\n')
    f.write('/MG/generator/LGNDLiquidArgon/SetRadiusMax 250. mm\n')
    f.write('/MG/generator/LGNDLiquidArgon/SetRadiusMin 0. mm\n')
    f.write('/MG/generator/LGNDLiquidArgon/SetHeight %i mm \n' % height)
    f.write('/MG/generator/LGNDLiquidArgon/SetCenterVector 0.0 0.0 0.0 mm\n')
    f.write('/MG/generator/LGNDLiquidArgon/SetNParticles 1\n')
    f.write('/MG/generator/LGNDLiquidArgon/SetBinWidth 5 mm\n')
    f.write('/run/beamOn %i \n' % events)
    f.close()

#print(" yar ",__name__)
if __name__ == "__main__":
    main(sys.argv[1:])
