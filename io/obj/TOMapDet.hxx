/**
** MG, Feb 2020 
**/
#ifndef TOMAPDET_DEFINED
#define TOMAPDET_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TH3D.h>
#include <vector>

// class to store info for the Ge detector
class TOMapDet: public TNamed {
  public:
    TOMapDet(TString theName=TString("MapDet"));
    ~TOMapDet();
    void clear();
    void print();

    int doNorm(double QE) {
      int nzero=0;
       for(int i = 0; i < hMap->GetNbinsX();i++){
          for(int j = 0; j < hMap->GetNbinsY();j++){
            for(int k = 0; k < hMap->GetNbinsZ();k++){
              double binNorm =  hMapNorm->GetBinContent(i+1,j+1,k+1);
              double binVal  = hMapRaw->GetBinContent(i+1,j+1,k+1)*QE;
              if(binVal == 0) ++nzero;
              if(binNorm>0) hMap->SetBinContent(i+1,j+1,k+1,binVal/binNorm);
          }
        }
      }
      std::cout << " normalized " << this->GetName() << " zeros " << nzero << std::endl;
      return nzero;
    }
    // data elements
    double maxX;
    double minX;
    double  maxY;
    double  minY; 
    double  maxZ;
    double  minZ;
    double  minR;
    double  maxR;
    double  gridSpacing;
    int nbinsX;
    int nbinsY;
    int nbinsZ;
    int nbinsR;
    TH3D* hMap;
    TH3D* hMapRaw;
    TH3D* hMapNorm;
    //
  ClassDef(TOMapDet,1)
};
#endif

