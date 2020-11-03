#include "TOMap.hxx"
ClassImp(TOMap)

    TOMap::TOMap() : TNamed("TOMap", "TOMap")
{
  //cryo rmax 241.3 cryo zmax 292.1
  double dimr = 241.3;
  double dimz = 292.1;
  minX = -dimr;
  maxX = dimr;
  minY = -dimr;
  maxY = dimr;
  minR = 0;
  maxR = dimr;
  minZ = -dimz;
  maxZ = dimz;

  gridSpacing = 5; //*mm
  nbinsX = int(2 * dimr / gridSpacing);
  nbinsY = int(2 * dimr / gridSpacing);
  nbinsR = int(dimr / gridSpacing);
  nbinsZ = int(2 * dimz / gridSpacing);

  TString theName("Map");
  hDetFrequency = new TH1D("DetFreq", " det freqency ", 8, 0, 8);
  hNormMap = new TH3D(Form("%sNorm", theName.Data()), Form("%sNorm", theName.Data()), nbinsX, minX, maxX, nbinsY, minY, maxY, nbinsZ, minZ, maxZ);
  hNormRZ = new TH2D(Form("%sNormRZ", theName.Data()), Form("%sMapRZ", theName.Data()), nbinsR, minR, maxR, nbinsZ, minZ, maxZ);
  hNormXY = new TH2D(Form("%sNormXY", theName.Data()), Form("%sNormXY", theName.Data()), nbinsX, minX, maxX, nbinsY, minY, maxY);
  hNormYZ = new TH2D(Form("%sNormYZ", theName.Data()), Form("%sNormYZ", theName.Data()), nbinsY, minY, maxY, nbinsZ, minZ, maxZ);
  clear();
}

TOMap::~TOMap() {}

void TOMap::addDet(TOMapDet d)
{
  // if the key already exists, add energy to the existing hit
  std::map<std::string, TOMapDet>::iterator iter = mapList.find(d.GetName());
  if (iter != mapList.end())
  {
    std::cout << " name " << d.GetName() << " already exists in map " << std::endl;
    return;
  }
  mapList.insert(std::pair<std::string, TOMapDet>(d.GetName(), d));
}

void TOMap::print()
{
  printf(" Total det hits %.0f \n", hDetFrequency->GetEntries());
  printf("TOMap # maps  = %u norm events = %0.f \n", (unsigned)mapList.size(), hNormMap->GetEntries());
  std::map<std::string, TOMapDet>::iterator iter = mapList.begin();
  while (iter != mapList.end())
  {
    printf(" %s QE %.3f raw %.0f  \n",
           iter->second.GetName(), iter->second.QE, iter->second.hRawMap->GetEntries());
    ++iter;
  }
}
