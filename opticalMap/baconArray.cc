#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
  int nevents = 10000;
  if (argc > 1)
    nevents = atoi(argv[1]);
  ofstream outputFile;
  int nparticles = 1000000;
  double mean = 128;
  double sigma = 2.929;
  string fileName = "baconMap";
  int njobs = 10;
  cout << " map " << njobs << " jobs with  " << nevents << " fileName  " << fileName << "x.mac " << endl;
  char sub[180];
  for (int i = 0; i < njobs; i++)
  {
    //cout<<"Setting Z to "<<z<<"mm...Range is from 300mm to -300mm , fileName is "<<fileName+ std::to_string(i) +string(".mac")<<endl;
    outputFile.open(fileName + to_string(i) + string(".mac"));
    outputFile << "/MG/manager/mglog routine" << endl;
    outputFile << "/MG/manager/seedWithUUID" << endl;
    outputFile << "/MG/processes/realm DarkMatter" << endl;
    outputFile << "/MG/processes/lowenergy false" << endl;
    outputFile << "/MG/processes/opticalOnly true" << endl;
    outputFile << "/MG/geometry/detector BACON" << endl;
    outputFile << "/MG/BACON/SetLiquid Xenon-Doped-Argon-Liq" << endl;
    outputFile << "/run/initialize" << endl;
    outputFile << "/MG/eventaction/rootschema MCOpticalRun" << endl;
    outputFile << "/MG/eventaction/reportingfrequency 100" << endl;
    sprintf(sub, "/MG/eventaction/rootfilename %s%i.root", fileName.c_str(), i);
    outputFile << sub << endl;
    outputFile << "/MG/io/MCOpticalRun/SetSensitiveIDLabelScheme manual" << endl;
    outputFile << "/MG/io/MCOpticalRun/AddSensitiveVolnameID physicalPMT_0 100" << endl;
    outputFile << "/MG/io/MCOpticalRun/setRunID 001" << endl;
    outputFile << "/MG/io/MCOpticalRun/useTimeWindow true" << endl;
    outputFile << "/MG/io/MCOpticalRun/setTimeWindow 86400 second" << endl;
    outputFile << "/MG/io/MCOpticalRun/setNSteps 10000000000000" << endl;
    outputFile << "/MG/generator/select LGNDLiquidArgon" << endl;
    outputFile << "/MG/generator/LGNDLiquidArgon/SetRadiusMax 0. mm" << endl;
    outputFile << "/MG/generator/LGNDLiquidArgon/SetRadiusMin 0. mm" << endl;
    outputFile << "/MG/generator/LGNDLiquidArgon/SetHeight 0 mm" << endl;
    outputFile << "/MG/generator/LGNDLiquidArgon/SetCenterVector 0.0 0.0 -291.1 mm" << endl;
    sprintf(sub, "/MG/generator/LGNDLiquidArgon/SetPhotonMean %.1f nm ", mean);
    outputFile << sub << endl;
    sprintf(sub, "/MG/generator/LGNDLiquidArgon/SetPhotonSigma %.3f nm ", sigma);
    outputFile << sub << endl;
    sprintf(sub, "/MG/generator/LGNDLiquidArgon/SetNParticles %i ", nparticles);
    outputFile << sub << endl;
    outputFile << "/MG/generator/LGNDLiquidArgon/SetBinWidth 0 mm" << endl;
    outputFile << "/run/beamOn " << nevents << endl;
    outputFile.close();
  }
  string sfileName("sbatchBacon");
  for (int i = 0; i < njobs; i++)
  {
    //cout<<"Setting Z to "<<z<<"mm...Range is from 300mm to -300mm , fileName is "<<sfileName+ std::to_string(i) +string(".sh")<<endl;
    string macroName = fileName + to_string(i) + string(".mac");
    string logName = sfileName + to_string(i) + string(".log");
    outputFile.open(sfileName + to_string(i) + string(".sh"));
    outputFile << "#!/bin/bash -l" << endl;
    outputFile << "#SBATCH --mail-type=begin,end,fail" << endl;
    outputFile << "#SBATCH --mail-user=mgold@unm.edu" << endl;
    outputFile << "#SBATCH --image docker:legendexp/legend-base:latest" << endl;
    outputFile << "#SBATCH --qos=shared" << endl;
    outputFile << "#SBATCH -C haswell" << endl;
    outputFile << "#SBATCH --nodes=1" << endl;
    outputFile << "#SBATCH --ntasks=1" << endl;
    outputFile << "#SBATCH --cpus-per-task=2" << endl;
    outputFile << "#SBATCH --time=3:00:00 # 3 hour" << endl;
    outputFile << "#SBATCH --mem=32G" << endl;
    outputFile << "#SBATCH --image=docker:legendexp/legend-base:latest" << endl;
    outputFile << "#SBATCH --export=LD_LIBRARY_PATH=/global/project/projectdirs/m2676/users/mgold/shifter/MGDO/lib:/opt/root/lib:/usr/lib64:/opt/clhep/lib:/opt/geant4/lib64:/opt/geant4/lib64:/opt/clhep/lib:/opt/hdf5/lib" << endl;
    outputFile << "#SBATCH --export=projectdir=/global/project/projectdirs/m2676/users/mgold/shifter/baconSim" << endl;
    outputFile << "export projectdir=/global/project/projectdirs/m2676/users/mgold/shifter/baconSim" << endl;
    outputFile << "export macro=" << macroName << endl;
    outputFile << "export logfile=" << logName << endl;
    outputFile << "srun --output=$projectdir/$logfile -n 1  -C haswell shifter --env-file=$projectdir/MaGeEnvirons $projectdir/bin/Linux-g++/MaGe $projectdir/opticalMap/$macro" << endl;
    outputFile.close();
  }

  return 0;
}
