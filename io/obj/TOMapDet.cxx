#include "TOMapDet.hxx"
ClassImp(TOMapDet)

TOMapDet::TOMapDet(TString theName): TNamed(theName,theName)
{
  QE=1.0;
  maxX = 300.;
  minX = -300.;
  maxY=300.;
  minY = -300;
  maxZ= 850;
  minZ = -850;
  minR = 0;
  maxR = 300.;
  gridSpacing = 5;//*mm
  nbinsX = int((maxX-minX)/gridSpacing);
  nbinsY = int((maxY-minY)/gridSpacing);
  nbinsZ = int((maxZ-minZ)/gridSpacing);
  nbinsR = int((maxR-minR)/gridSpacing);

  hMap = new TH3D(theName,theName,nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  hRawMap = new TH3D(Form("%sRaw",theName.Data()),Form("%sRaw",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  hNormMap = new TH3D(Form("%sNorm",theName.Data()),Form("%sNorm",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  hMapRZ= new TH2D(Form("%sMapRZ",theName.Data()),Form("%sMapRZ",theName.Data()),nbinsR,minR,maxR,nbinsZ,minZ,maxZ);
  hRawRZ = new TH2D(Form("%sRawRZ",theName.Data()),Form("%sMapRZ",theName.Data()),nbinsR,minR,maxR,nbinsZ,minZ,maxZ);
  hNormRZ = new TH2D(Form("%sNormRZ",theName.Data()),Form("%sMapRZ",theName.Data()),nbinsR,minR,maxR,nbinsZ,minZ,maxZ);  
    
  hMapXY = new TH2D(Form("%sMapXY",theName.Data()),Form("%sMapXY",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY);
  hRawXY = new TH2D(Form("%sRawXY",theName.Data()),Form("%sRawXY",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY);
  hNormXY = new TH2D(Form("%sNormXY",theName.Data()),Form("%sNormXY",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY);

  hMapYZ = new TH2D(Form("%sMapYZ",theName.Data()),Form("%sMapYZ",theName.Data()),nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  hRawYZ = new TH2D(Form("%sRawYZ",theName.Data()),Form("%sRawYZ",theName.Data()),nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  hNormYZ = new TH2D(Form("%sNormYZ",theName.Data()),Form("%sNormYZ",theName.Data()),nbinsY,minY,maxY,nbinsZ,minZ,maxZ);

  hWeight = new TH1D("rWeight","rWeight",hMapRZ->GetNbinsX(),minR,maxR);
}


TOMapDet::~TOMapDet(){}

void TOMapDet::clear()
{
  hMap->Reset();
  hRawMap->Reset();
  hNormMap->Reset();
  hMapRZ->Reset();
  hRawRZ->Reset();
  hNormRZ->Reset();
  hMapYZ->Reset();
  hRawYZ->Reset();
  hNormYZ->Reset();
  hMapXY->Reset();
  hRawXY->Reset();
  hNormXY->Reset();
}

void TOMapDet::print()
{
  std::cout << hMap->GetName() << " has " << hMap->GetEntries() << std::endl; 
  std::cout << hRawMap->GetName() << " has " << hRawMap->GetEntries() << std::endl; 
  std::cout << hNormMap->GetName() << " has " << hNormMap->GetEntries() << std::endl; 
}
