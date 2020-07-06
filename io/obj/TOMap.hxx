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
#include "TOMapDet.hxx"
#include <map>

// class to store info for the Ge detector
class TOMap: public TNamed {
  public:
    TOMap();
    ~TOMap();
    void clear();
    void print();
    // data elements
    std::map<std::string,TOMapDet>  mapList;
    void addDet(TOMapDet d);
    TH3D *getRaw(TString name) {
      std::map<std::string,TOMapDet>::iterator iter = mapList.find(name.Data());
      if(iter != mapList.end()) return iter->second.hMapRaw;
      return NULL;
   }
    TH3D *getNorm(TString name) {
      std::map<std::string,TOMapDet>::iterator iter = mapList.find(name.Data());
      if(iter != mapList.end()) return iter->second.hMapNorm;
      return NULL;
   }
    TH3D *getMap(TString name) {
      std::map<std::string,TOMapDet>::iterator iter = mapList.find(name.Data());
      if(iter != mapList.end()) return iter->second.hMap;
      return NULL;
   }

    void normalize() {
      std::map<std::string,TOMapDet>::iterator iter = mapList.begin();
       while (iter != mapList.end()) {
         iter->second.doNorm(QE);
         ++iter;
       }
    }
    double QE;
    void setQE(double val ) { QE=val;}
    double getQE() { return QE;}
    //
  ClassDef(TOMap,1)
};
#endif
