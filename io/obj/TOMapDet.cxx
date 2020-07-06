#include "TOMapDet.hxx"
ClassImp(TOMapDet)

TOMapDet::TOMapDet(TString theName): TNamed(theName,theName)
{
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
  hMapRaw = new TH3D(Form("%sRaw",theName.Data()),Form("%sRaw",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  hMapNorm = new TH3D(Form("%sNorm",theName.Data()),Form("%sNorm",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
}


TOMapDet::~TOMapDet(){}

void TOMapDet::clear()
{
  hMap->Reset();
  hMapRaw->Reset();
  hMapNorm->Reset();
}

void TOMapDet::print()
{
  std::cout << hMap->GetName() << " has " << hMap->GetEntries() << std::endl; 
  std::cout << hMapRaw->GetName() << " has " << hMapRaw->GetEntries() << std::endl; 
  std::cout << hMapNorm->GetName() << " has " << hMapNorm->GetEntries() << std::endl; 
}

