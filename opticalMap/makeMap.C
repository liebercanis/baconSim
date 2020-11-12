enum {NDET=8};
TH3D* hMap[NDET];
TH2D* hMapXY[NDET];
TH2D* hMapYZ[NDET];
TH2D* hMapRZ[NDET];
TFile *fout;
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
    searchM[i] = Form("SipmMap%i", i);
  searchM[5].Form("PMTMap%i", 0);
  searchM[6].Form("PMTMap%i", 1);

  for (int i = 0; i < NDET - 2; ++i)
    save[i] = Form("SipmSumMap%i", i);
  save[5].Form("PMTSumMap%i", 0);
  save[6].Form("PMTSumMap%i", 1);

  /* XY */
  for (int i = 0; i < NDET - 2; ++i)
    searchXY[i] = Form("SipmMap%iXY", i);
  searchXY[5].Form("PMTMap%iXY", 0);
  searchXY[6].Form("PMTMap%iXY", 1);

  for (int i = 0; i < NDET - 2; ++i)
    saveXY[i] = Form("SipmSumMap%iXY", i);
  saveXY[5].Form("PMTSumMap%iXY", 0);
  saveXY[6].Form("PMTSumMap%iXY", 1);

  /* YZ */
  for (int i = 0; i < NDET - 2; ++i)
    searchYZ[i] = Form("SipmMap%iYZ", i);
  searchYZ[5].Form("PMTMap%iYZ", 0);
  searchYZ[6].Form("PMTMap%iYZ", 1);

  for (int i = 0; i < NDET - 2; ++i)
    saveYZ[i] = Form("SipmSumMap%iYZ", i);
  saveYZ[5].Form("PMTSumMap%iYZ", 0);
  saveYZ[6].Form("PMTSumMap%iYZ", 1);

  /* RZ */
  for (int i = 0; i < NDET - 2; ++i)
    searchRZ[i] = Form("SipmMap%iYZ", i);
  searchRZ[5].Form("PMTMap%iYZ", 0);
  searchRZ[6].Form("PMTMap%iYZ", 1);

  for (int i = 0; i < NDET - 2; ++i)
    saveRZ[i] = Form("SipmSumMap%iYZ", i);
  saveRZ[5].Form("PMTSumMap%iYZ", 0);
  saveRZ[6].Form("PMTSumMap%iYZ", 1);
}

void histSum( TH3D * h1, TH3D* h2) {
  for(int i=0; i< h1->GetNbinsX(); ++i) {
    for(int j=0; j< h1->GetNbinsY(); ++j) {
      for(int k=0; k< h1->GetNbinsZ(); ++k) {
        int ibin = h1->GetBin(i,j,k);
        h1->SetBinContent(ibin, h1->GetBinContent(ibin)+h2->GetBinContent(ibin));
      }
    }
  }
}

void histSum2(TH2D *h1, TH2D *h2)
{
  for (int i = 0; i < h1->GetNbinsX(); ++i)
  {
    for (int j = 0; j < h1->GetNbinsY(); ++j)
    {
      int ibin = h1->GetBin(i, j);
      h1->SetBinContent(ibin, h1->GetBinContent(ibin) + h2->GetBinContent(ibin));
    }
  }
}

void getInit(TString fname)
{
  TFile *fin = new TFile(fname,"READONLY");
  if(!fin) {
    cout << fname << " not found " << endl;
    return;
  }
  cout << " file " << fin->GetName()  << " opened " << endl;
  TDirectory *dir=NULL;
  fin->GetObject("OpticalMap",dir);
  if(!dir) {
    cout << " OpticalMap dir  not found " << endl;
    return;
  }
  //dir->ls();


  TList* list = dir->GetListOfKeys() ;
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
      if( hname== searchM[i] )  
      {
        hist = (TH3D*) obj;
        fout->cd();
        hMap[i]= (TH3D*) hist->Clone(save[i]);
      }
      if (hname == searchXY[i])
      {
        hist2 = (TH2D *)obj;
        fout->cd();
        hMapXY[i] = (TH2D *)hist2->Clone(saveXY[i]);
      }
      if (hname == searchYZ[i])
      {
        hist2 = (TH2D *)obj;
        fout->cd();
        hMapYZ[i] = (TH2D *)hist2->Clone(saveYZ[i]);
      }
      if (hname == searchRZ[i])
      {
        hist2 = (TH2D *)obj;
        fout->cd();
        hMapRZ[i] = (TH2D *)hist2->Clone(saveRZ[i]);
      }
    }
  }

  for(int i=0; i< NDET; ++i) if(hMap[i]) {
    if(hMap[i]) {
      cout << " init " << fname << " " << hMap[i]->GetName() << " entries " << hMap[i]->GetEntries() << endl;
      cout << " init " << fname << " " << hMapXY[i]->GetName() << " entries " << hMapXY[i]->GetEntries() << endl;
      cout << " init " << fname << " " << hMapYZ[i]->GetName() << " entries " << hMapYZ[i]->GetEntries() << endl;
      cout << " init " << fname << " " << hMapRZ[i]->GetName() << " entries " << hMapRZ[i]->GetEntries() << endl;
    }
  }

}


void getOne(TString fname)
{
  TFile *fin = new TFile(fname,"READONLY");
  if(!fin) {
    cout << fname << " not found " << endl;
    return;
  }
  cout << " file " << fin->GetName()  << " opened " << endl;
  TDirectory *dir=NULL;
  fin->GetObject("OpticalMap",dir);
  if(!dir) {
    cout << " OpticalMap dir  not found " << endl;
    return;
  }
  //dir->ls();

  TList* list = dir->GetListOfKeys() ;
  if (!list) { printf("<E> No keys found in file\n") ; exit(1) ; }
  TIter next(list);
  TKey* key;
  TObject* obj;
  TH3D* hist;
  TH2D *hist2;
  while ((key = (TKey *)next()))
  {
    obj = key->ReadObj();
    TString hname(obj->GetName());
    for (int i = 0; i < NDET; ++i)
    {
      if (hname == searchM[i])
      {
        hist = (TH3D *)obj;
        histSum(hMap[i],hist);
      }
      if (hname == searchXY[i])
      {
        hist2 = (TH2D *)obj;
        histSum2(hMapXY[i],hist2);
      }
      if (hname == searchYZ[i])
      {
        hist2 = (TH2D *)obj;
        histSum2(hMapYZ[i],hist2);
      }
      if (hname == searchRZ[i])
      {
        hist2 = (TH2D *)obj;
        histSum2(hMapRZ[i],hist2);
      }
    }
  }

  for (int i = 0; i < NDET; ++i)
  {
    if(hMap[i]) {
      cout << " sum " << fname << " " << hMap[i]->GetName() << " entries " << hMap[i]->GetEntries() << endl;
      cout << " sum " << fname << " " << hMapXY[i]->GetName() << " entries " << hMapXY[i]->GetEntries() << endl;
      cout << " sum " << fname << " " << hMapYZ[i]->GetName() << " entries " << hMapYZ[i]->GetEntries() << endl;
      cout << " sum " << fname << " " << hMapRZ[i]->GetName() << " entries " << hMapRZ[i]->GetEntries() << endl;
    }
  }
}

void makeMap() {
  fout = new TFile("baconOpticalMap.root","RECREATE");

  makeNames();

  // look for files
  cout << "dir is " << gSystem->pwd()  << endl;
  TSystemDirectory lDir("opticalMap",gSystem->pwd()); 
  TList *files = (TList*) lDir.GetListOfFiles();

  TString fname;
  TIter next(files);
  TSystemFile *afile;
  bool init=true;
  while( (afile = (TSystemFile*) next()) )
  {  
    fname = afile->GetName();  
    if(fname.Contains("root")&&fname.Contains("baconMap")) {
      cout << " .... " << fname << endl;
      if(init) {
        getInit(fname);
        init=false;
      } else 
        getOne(fname);
    }
  }
  
  /*
  for(int i=0; i< NDET; ++i) {

    TString cname; cname.Form("Can%i-%s",i,hMap[i]->GetName() );
    TCanvas *can = new TCanvas(cname,cname);
    hMap[i]->Draw("lego");
    can->Print(".png");
  }
  */

  fout->ls();
  fout->Write();
}

