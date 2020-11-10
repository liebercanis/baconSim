enum {NDET=7};
TH3D* hMap[NDET];
TH2D* hMapXY[NDET];
TH2D* hMapYZ[NDET];
TH2D* hMapRZ[NDET];
TFile *fin;
TString searchM[NDET];
TString save[NDET];
TString searchXY[NDET];
TString saveXY[NDET];
TString searchYZ[NDET];
TString saveYZ[NDET];
TString searchRZ[NDET];
TString saveRZ[NDET];

// make names   
void makeNames(){
  
  for (int i = 0; i < NDET - 2; ++i)
    save[i] = Form("SipmSumMap%i", i);
  save[5].Form("PMTSumMap%i", 0);
  save[6].Form("PMTSumMap%i", 1);

  for (int i = 0; i < NDET - 2; ++i)
    saveXY[i] = Form("SipmSumMap%iXY", i);
  saveXY[5].Form("PMTSumMap%iXY", 0);
  saveXY[6].Form("PMTSumMap%iXY", 1);

    for (int i = 0; i < NDET - 2; ++i)
    saveYZ[i] = Form("SipmSumMap%iYZ", i);
  saveYZ[5].Form("PMTSumMap%iYZ", 0);
  saveYZ[6].Form("PMTSumMap%iYZ", 1);

  
  for (int i = 0; i < NDET - 2; ++i)
    saveRZ[i] = Form("SipmSumMap%iYZ", i);
  saveRZ[5].Form("PMTSumMap%iYZ", 0);
  saveRZ[6].Form("PMTSumMap%iYZ", 1);
}

void getHistograms()
{
  

  TList* list = fin->GetListOfKeys() ;
  if (!list) { printf("<E> No keys found in file\n") ; exit(1) ; }
  TIter next(list);
  TKey* key;
  TObject* obj;
  TH3D* hist;
  TH2D* hist2;
  while ( (key = (TKey*)next()) ) 
  {
    obj = key->ReadObj();
    TString hname(obj->GetName());
    for(int i=0; i< NDET; ++i) 
    {
      if( hname== save[i] )  
      {
        hist = (TH3D*) obj;
        hMap[i]= (TH3D*) hist->Clone(save[i]);
      }
      if (hname == saveXY[i])
      {
        hist2 = (TH2D *)obj;
        hMapXY[i] = (TH2D *)hist2->Clone(saveXY[i]);
      }
      if (hname == saveYZ[i])
      {
        hist2 = (TH2D *)obj;
        hMapYZ[i] = (TH2D *)hist2->Clone(saveYZ[i]);
      }
      if (hname == saveRZ[i])
      {
        hist2 = (TH2D *)obj;
        hMapRZ[i] = (TH2D *)hist2->Clone(saveRZ[i]);
      }
    }
  }

  for(int i=0; i< NDET; ++i) if(hMap[i]) {
    cout << " got "  << hMap[i]->GetName() << " entries " << hMap[i]->GetEntries() << endl;
    cout << " got "  << hMapXY[i]->GetName() << " entries " << hMapXY[i]->GetEntries() << endl;
    cout << " got "  << hMapYZ[i]->GetName() << " entries " << hMapYZ[i]->GetEntries() << endl;
    cout << " got "  << hMapRZ[i]->GetName() << " entries " << hMapRZ[i]->GetEntries() << endl;
  }

}

void viewMap() {

  fin = new TFile("baconOpticalMap.root","READONLY");

  makeNames();

  getHistograms();

  gStyle->SetOptLogz();
  gStyle->SetOptStat(0);


  for(int i=0; i< NDET; ++i) {
    TString cname; cname.Form("Can%i-%s",i,hMap[i]->GetName() );
    TCanvas *can = new TCanvas(cname,cname);
    hMapRZ[i]->Draw("COLZ");
    can->Print(".png");
  }
}

