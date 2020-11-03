/**
** MG, Feb 2020 
**/
#ifndef TOMAP_DEFINED
#define TOMAP_DEFINED
#include <iostream>
#include <string>
#include <TROOT.h>
#include <TNamed.h>
#include <TVector3.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <map>
#include "TOMapDet.hxx"

// class to store info for the Ge detector
class TOMap : public TNamed
{
public:
  TOMap();
  ~TOMap();
  // data elements
  std::map<std::string, TOMapDet> mapList;
  TH3D *hNormMap;
  TH2D *hNormRZ;
  TH2D *hNormYZ;
  TH2D *hNormXY;
  TH1D *hDetFrequency;
  double maxX;
  double minX;
  double maxY;
  double minY;
  double maxZ;
  double minZ;
  double minR;
  double maxR;
  double gridSpacing;
  int nbinsX;
  int nbinsY;
  int nbinsZ;
  int nbinsR;
  // methods
  void print();
  void clear()
  {
    hDetFrequency->Reset();
    hNormMap->Reset();
    hNormRZ->Reset();
    hNormYZ->Reset();
    hNormXY->Reset();
    mapList.clear();
  }
  void addDet(TOMapDet d);
  TOMapDet *getMap(TString name)
  {
    std::map<std::string, TOMapDet>::iterator iter = mapList.find(name.Data());
    if (iter != mapList.end())
      return &(iter->second);
    return NULL;
  }
  void fillFrequency(int id)
  {
    int idet = 0;
    if (id > 200)
      idet = id % 200;
    else if (id == 100)
      idet = 6;
    else if (id == 101)
      idet = 7;
    hDetFrequency->Fill(idet + 1);
  }
  void normalize()
  {
    std::map<std::string, TOMapDet>::iterator iter = mapList.begin();
    while (iter != mapList.end())
    {
      iter->second.doNorm(hNormMap, hNormRZ, hNormYZ, hNormXY);
      ++iter;
    }
  }
  //
  void fillNorm(double x, double y, double z)
  {
    hNormMap->Fill(x, y, z);
    double r = sqrt(x * x + y * y + z * z);
    hNormRZ->Fill(r, z);
    hNormYZ->Fill(y, z);
    hNormXY->Fill(x, y);
  }
  ClassDef(TOMap, 2)
};
#endif
