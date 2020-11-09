enum {NDET=7};
TH3D* hMap[NDET];
TFile *fout;


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

void getInit(int imap)
{
  TString fname;
  fname.Form("baconMap%i.root",imap);
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

  TString search[NDET];
  for(int i=0; i< NDET-2; ++i ) search[i]=Form("SipmMap%i",i);
  search[5].Form("PMTMap%i",0);
  search[6].Form("PMTMap%i",1);

  TString save[NDET];
  for(int i=0; i< NDET-2; ++i ) save[i]=Form("SipmSumMap%i",i);
  save[5].Form("PMTSumMap%i",0);
  save[6].Form("PMTSumMap%i",1);



  TList* list = dir->GetListOfKeys() ;
  if (!list) { printf("<E> No keys found in file\n") ; exit(1) ; }
  TIter next(list);
  TKey* key;
  TObject* obj;
  TH3D* hist;
  while ( (key = (TKey*)next()) ) {
    obj = key->ReadObj() ;
    if (!obj->InheritsFrom("TH3D")) continue;
    TString hname(obj->GetName());
    for(int i=0; i< NDET; ++i) {
      if( hname== search[i] )  {
        hist = (TH3D*) obj;
        fout->cd();
        hMap[i]= (TH3D*) hist->Clone(save[i]);
      }
    }
  }

   for(int i=0; i< NDET; ++i) if(hMap[i]) {
     cout << " init " << imap << " " << hMap[i]->GetName() << " entries " << hMap[i]->GetEntries() << endl;
   }

}


void getOne(int imap)
{
  TString fname;
  fname.Form("baconMap%i.root",imap);
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

  TString search[NDET];
  for(int i=0; i< NDET-2; ++i ) search[i]=Form("SipmMap%i",i);
  search[5].Form("PMTMap%i",0);
  search[6].Form("PMTMap%i",1);

  TList* list = dir->GetListOfKeys() ;
  if (!list) { printf("<E> No keys found in file\n") ; exit(1) ; }
  TIter next(list);
  TKey* key;
  TObject* obj;
  TH3D* hist;
  while ( (key = (TKey*)next()) ) {
    obj = key->ReadObj() ;
    if (!obj->InheritsFrom("TH3D")) continue;
    TString hname(obj->GetName());
    for(int i=0; i< NDET; ++i) {
      if( hname== search[i] ) { hist = (TH3D*) obj;
        histSum(hMap[i],hist);
      }
    }
  }

   for(int i=0; i< NDET; ++i) if(hMap[i]) cout << imap << " got " << hMap[i]->GetName() << " entries " << hMap[i]->GetEntries() << endl;

}

void makeMap() {
  fout = new TFile("baconOpticalMap.root","RECREATE");


  getInit(4);
  getOne(5);
  getOne(6);
  getOne(7);

  fout->ls();
 for(int i=0; i< NDET; ++i) {

  TString cname; cname.Form("Can%i-%s",i,hMap[i]->GetName() );
  TCanvas *can = new TCanvas(cname,cname);
   hMap[i]->Draw("lego");
   can->Print(".png");
 }


  fout->Write();
}

