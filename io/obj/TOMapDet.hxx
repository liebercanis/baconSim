/**
** MG, Feb 2020 
**/
#ifndef TOMAPDET_DEFINED
#define TOMAPDET_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <vector>

// class to store info for the Ge detector
class TOMapDet : public TNamed
{
public:
  TOMapDet(TString theName = TString("MapDet"));
  ~TOMapDet();
  void clear();
  void print();

  int doNorm(TH3D *hNormMap, TH2D *hNormRZ, TH2D *hNormYZ, TH2D *hNormXY);

  
  //
  void fill(double eDep, double x, double y, double z)
  {
    hEDep->Fill(eDep * 1.0E6); // convert to eV
    hRawMap->Fill(x, y, z);
    double r = sqrt(x * x + y * y );
    hRawRZ->Fill(r, z);
    hRawYZ->Fill(y, z);
    hRawXY->Fill(x, y);
  }

  void setQE(double val) { QE = val; }
  double getQE() { return QE; }
  // data elements
  double QE;
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
  TH1D *hEDep;
  TH3D *hMap;
  TH3D *hRawMap;
  TH2D *hMapRZ;
  TH2D *hRawRZ;
  TH2D *hMapYZ;
  TH2D *hRawYZ;
  TH2D *hMapXY;
  TH2D *hRawXY;
  TH1D *hWeight;
  //
  ClassDef(TOMapDet, 2)
};
#endif
