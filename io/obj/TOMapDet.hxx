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
class TOMapDet: public TNamed {
  public:
    TOMapDet(TString theName=TString("MapDet"));
    ~TOMapDet();
    void clear();
    void print();

    int doNorm() {
      double binVal=0;
      double binNorm=0;
      int nzero=0;
      for(int i = 0; i < hMap->GetNbinsX();i++){
        for(int j = 0; j < hMap->GetNbinsY();j++){
          for(int k = 0; k < hMap->GetNbinsZ();k++){
            binNorm =  hNormMap->GetBinContent(i+1,j+1,k+1);
            binVal  = hRawMap->GetBinContent(i+1,j+1,k+1)*QE;
            if(binVal == 0) ++nzero;
            if(binNorm>0) hMap->SetBinContent(i+1,j+1,k+1,binVal/binNorm);
          }
        }
      }
      for(int i = 0; i < hMapXY->GetNbinsX();i++){
        for(int j = 0; j < hMapXY->GetNbinsY();j++){
          binNorm = hNormXY->GetBinContent(i+1,j+1);
          binVal = hRawXY->GetBinContent(i+1,j+1)*QE;
          if(binNorm>0) hMapXY->SetBinContent(i+1,j+1,binVal/binNorm);
        }
      }
      for(int i = 0; i < hMapYZ->GetNbinsX();i++){
        for(int j = 0; j < hMapYZ->GetNbinsY();j++){
          binNorm = hNormYZ->GetBinContent(i+1,j+1);
          binVal = hRawYZ->GetBinContent(i+1,j+1)*QE;
          if(binNorm>0) hMapYZ->SetBinContent(i+1,j+1,binVal/binNorm);
        }
      }
      for(int i = 0; i < hMapRZ->GetNbinsX();i++){
        for(int j = 0; j < hMapRZ->GetNbinsY();j++){
          binNorm = hNormRZ->GetBinContent(i+1,j+1);
          binVal = hRawRZ->GetBinContent(i+1,j+1)*QE;
          double r = gridSpacing*(i+1)+minR;
          double weight = ((r+gridSpacing)*(r+gridSpacing)-r*r)/(maxR*maxR-minR*minR);
          binVal /= weight;
          hWeight->SetBinContent(i+1,weight);
          if(binNorm>0) hMapRZ->SetBinContent(i+1,j+1,binVal/binNorm);
        }
      }

      std::cout << " normalized " << this->GetName() << " zeros " << nzero << std::endl;
      return nzero;
    }
    //
    void fillNorm(double x, double y, double z){
      hNormMap->Fill(x,y,z);
      double r = sqrt(x*x+y*y+z*z);
      hNormRZ->Fill(r,z);
      hNormYZ->Fill(y,z);
      hNormXY->Fill(x,y);
    }
    //
    void fill(double x, double y, double z){
      hRawMap->Fill(x,y,z);
      double r = sqrt(x*x+y*y+z*z);
      hRawRZ->Fill(r,z);
      hRawYZ->Fill(y,z);
      hRawXY->Fill(x,y);
    }

    void setQE(double val ) { QE=val;}
    double getQE() { return QE;}
    // data elements
    double QE;
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
    TH3D* hRawMap;
    TH3D* hNormMap;
    TH2D* hMapRZ;
    TH2D* hRawRZ;
    TH2D* hNormRZ;
    TH2D* hMapYZ;
    TH2D* hRawYZ;
    TH2D* hNormYZ;
    TH2D* hMapXY;
    TH2D* hRawXY;
    TH2D* hNormXY;
    TH1D* hWeight;
    //
  ClassDef(TOMapDet,1)
};
#endif

