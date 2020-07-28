void mapView(TString name = "baconTest")
{
  TString fname = name + TString(".root");
  TFile *fin = new TFile(fname,"READONLY");
  TDirectory *dir;
  fin->GetObject("OpticalMap",dir);
  //dir->ls();
  TTree *ltree;
  TLArEvent *lev = new TLArEvent();
  fin->GetObject("LTree",ltree);
  ltree->SetBranchAddress("LArEvent",&lev);
  ltree->GetListOfBranches()->ls();

  TFile *fout = new TFile("mapView.root","RECREATE");

  TH1D* hPrimR= new TH1D("PrimR","",200,0,250);
  TH2D* hPrimXY= new TH2D("PrimXY","",400,-20,20,200,-250,250);
  hPrimXY->SetMarkerStyle(7);
  TH1D* hPrimZ= new TH1D("PrimZ","",200,-300,300);

  cout << " LTree has " << ltree->GetEntries() << endl;

  for(Long64_t iev=0; iev< ltree->GetEntries() ; ++ iev) {
    ltree->GetEntry(iev);
    hPrimR->Fill( lev->primaryVertex.Perp() );
    hPrimZ->Fill( lev->primaryVertex.Z() );
    hPrimXY->Fill( lev->primaryVertex.X(),lev->primaryVertex.Y() );
  }
  gStyle->SetOptStat(11);
  TCanvas *pcan = new TCanvas("PrimVertex","PrimVertex");
  pcan->SetLogz();
  pcan->Divide(2,2);
  pcan->cd(1); hPrimXY->Draw("contz");
  pcan->cd(2); hPrimR->Draw();
  pcan->cd(3); hPrimZ->Draw();


  //
  TH2D* PMTMapRZ[2];
  TH2D* SipmMapRZ[6];
  TH1D* SipmMapEDep[6];
  dir->GetObject("PMTMap0RZ",PMTMapRZ[0]);
  dir->ls();
  for(int i=0; i<2; ++i ) {
    dir->GetObject(Form("PMTMap%iRZ",i),PMTMapRZ[i]);
    PMTMapRZ[i]->GetYaxis()->SetTitle(" Z (mm) ");
    PMTMapRZ[i]->GetXaxis()->SetTitle(" R (mm) ");
    PMTMapRZ[i]->SetMarkerStyle(7);
    PMTMapRZ[i]->SetMarkerSize(.2);

    cout <<  PMTMapRZ[i]->GetName() << "  has   " << PMTMapRZ[i]->GetEntries() << endl;
  }
  TString sipmName;
  for(int i=0; i<6; ++i ) {
    dir->GetObject(Form("SipmMap%iRZ",i),SipmMapRZ[i]);
    sipmName.Form("SipmMap%iEDep",i);
    dir->GetObject(sipmName,SipmMapEDep[i]);
    SipmMapRZ[i]->GetYaxis()->SetTitle(" Z (mm) ");
    SipmMapRZ[i]->GetXaxis()->SetTitle(" R (mm) ");
    SipmMapRZ[i]->SetMarkerStyle(7);
    SipmMapRZ[i]->SetMarkerSize(.2);
    cout <<  SipmMapRZ[i]->GetName() << "  has   " << SipmMapRZ[i]->GetEntries() << endl;
    if(SipmMapEDep[i]) cout  <<  SipmMapEDep[i]->GetName() << "  has   " << SipmMapEDep[i]->GetEntries() << endl;
  }


  TCanvas *can = new TCanvas("PMTMap","PMTMap");
  gStyle->SetOptLogz();
  can->Divide(1,2);
  for(int i=0; i<2; ++i ) { 
    can->cd(i+1);
    PMTMapRZ[i]->Draw("contz");
  }

  TCanvas *scan = new TCanvas("SipmMap", "SipmMap");
  gStyle->SetOptLogz();
  scan->Divide(2, 3);
  for (int i = 0; i < 6; ++i)
  {
    scan->cd(i + 1);
    SipmMapRZ[i]->Draw("contz");
  }
  
  TCanvas *edcan = new TCanvas("SipmEDep", "SipmEDep");
  gStyle->SetOptLogy();
  edcan->Divide(2, 3);
  for (int i = 0; i < 6; ++i)
  {
    edcan->cd(i + 1);
    SipmMapEDep[i]->GetXaxis()->SetTitle(" photon energy (eV)  ");
    SipmMapEDep[i]->Draw("");
  }

  fout->ls();
  fout->Write();

}
