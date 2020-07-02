{
  printf("\n this is rootlogon for baconSim \n");
  TString arch=gSystem->GetBuildArch();
  gROOT->LoadMacro("util.C");
  cout << " arch is " << arch << endl; 
  iload = gSystem->Load("$BACONSIM/io/obj/libLegendRoot.so");
  printf(" loaded libLegendRoot.so = %i zero is success! \n",iload);
}

