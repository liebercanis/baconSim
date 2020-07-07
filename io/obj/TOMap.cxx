#include "TOMap.hxx"
ClassImp(TOMap)

TOMap::TOMap(): TNamed("TOMap","TOMap")
{
  clear();
}

TOMap::~TOMap(){}

void TOMap::clear()
{
  mapList.clear();
}

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
    printf(" %s %.3f \n",iter->second.GetName(),iter->second.QE);
    ++iter;
  }
}

