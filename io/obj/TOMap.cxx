#include "TOMap.hxx"
ClassImp(TOMap)

TOMap::TOMap(): TNamed("TOMap","TOMap")
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
  TString theName("Map");
  hNormMap = new TH3D(Form("%sNorm",theName.Data()),Form("%sNorm",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  hNormRZ = new TH2D(Form("%sNormRZ",theName.Data()),Form("%sMapRZ",theName.Data()),nbinsR,minR,maxR,nbinsZ,minZ,maxZ);  
  hNormXY = new TH2D(Form("%sNormXY",theName.Data()),Form("%sNormXY",theName.Data()),nbinsX,minX,maxX,nbinsY,minY,maxY);
  hNormYZ = new TH2D(Form("%sNormYZ",theName.Data()),Form("%sNormYZ",theName.Data()),nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  clear();
}

TOMap::~TOMap(){}

void TOMap::addDet(TOMapDet d) {
  // if the key already exists, add energy to the existing hit
  std::map<std::string,TOMapDet>::iterator iter = mapList.find(d.GetName());
  if(iter != mapList.end()) {
    std::cout << " name " << d.GetName()  << " already exists in map " << std::endl;
    return;
  }
  mapList.insert(std::pair<std::string,TOMapDet>(d.GetName(),d));
}


void TOMap::print()
{
  printf("TOMap #maps  = %u \n",(unsigned)mapList.size());
  std::map<std::string,TOMapDet>::iterator iter = mapList.begin();
  while (iter != mapList.end()) {
    printf(" %s %.3f %.0f \n",iter->second.GetName(),iter->second.QE,iter->second.hRawMap->GetEntries());
    ++iter;
  }
}

