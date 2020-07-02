void baconArray(int nevents=100)
{
  ofstream outputFile;
  string fileName = "baconMap";
  double zMax =  295;
  double zMin = -300;
  double binSize = 5;
  int nslice = (zMax-zMin)/binSize+1;
  cout << " map "  << nslice << " slices with binSize "<< binSize << " fileName  " << fileName << " nevents  " << nevents << endl << endl;
  for(int i = 0; i < nslice ; i++){
    double z = zMax - binSize*i;
    //cout<<"Setting Z to "<<z<<"mm...Range is from 300mm to -300mm , fileName is "<<fileName+ std::to_string(i) +string(".mac")<<endl;
    string n = std::to_string(i);
    outputFile.open(fileName + std::to_string(i) +string(".mac"));
    outputFile<<"/MG/manager/mglog routine"<<endl;
    outputFile<<"/MG/manager/seedWithUUID"<<endl;
    outputFile<<"/MG/processes/realm DarkMatter"<<endl;
    outputFile<<"/MG/processes/lowenergy false"<<endl;
    outputFile<<"/MG/processes/opticalOnly true"<<endl;
    outputFile<<"/MG/geometry/detector BACON"<<endl;
    outputFile<<"/MG/BACON/SetLiquid Xenon-Doped-Argon-Liq"<<endl;
    outputFile<<"/run/initialize"<<endl;
    outputFile<<"/MG/eventaction/rootschema MCOpticalRun"<<endl;
    outputFile<<"/MG/eventaction/reportingfrequency 10"<<endl;
    outputFile<<"/MG/eventaction/rootfilename "<<fileName + to_string(i)<<".root"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/SetSensitiveIDLabelScheme manual"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/AddSensitiveVolnameID physicalPMT_0 100"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/setRunID 001"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/useTimeWindow true"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/setTimeWindow 86400 second"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/setNSteps 10000000000000"<<endl;
    outputFile<<"/MG/generator/select LGNDLiquidArgon"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetRadiusMax 250. mm"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetRadiusMin 0. mm"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetHeight "<<to_string(z)<<" mm"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetCenterVector 0.0 0.0 0.0 mm"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetNParticles 1"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetBinWidth 5 mm"<<endl;
    outputFile<<"/run/beamOn "<<nevents<<endl;
    outputFile.close();
  }
}
