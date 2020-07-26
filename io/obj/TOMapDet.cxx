#include "TOMapDet.hxx"
ClassImp(TOMapDet)

    TOMapDet::TOMapDet(TString theName) : TNamed(theName, theName)
{
  QE = 1.0;
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

  hMap = new TH3D(theName, theName, nbinsX, minX, maxX, nbinsY, minY, maxY, nbinsZ, minZ, maxZ);
  hRawMap = new TH3D(Form("%sRaw", theName.Data()), Form("%sRaw", theName.Data()), nbinsX, minX, maxX, nbinsY, minY, maxY, nbinsZ, minZ, maxZ);

  hMapRZ = new TH2D(Form("%sRZ", theName.Data()), Form("%sMapRZ", theName.Data()), nbinsR, minR, maxR, nbinsZ, minZ, maxZ);
  hRawRZ = new TH2D(Form("%sRawRZ", theName.Data()), Form("%sMapRZ", theName.Data()), nbinsR, minR, maxR, nbinsZ, minZ, maxZ);

  hMapXY = new TH2D(Form("%sXY", theName.Data()), Form("%sMapXY", theName.Data()), nbinsX, minX, maxX, nbinsY, minY, maxY);
  hRawXY = new TH2D(Form("%sRawXY", theName.Data()), Form("%sRawXY", theName.Data()), nbinsX, minX, maxX, nbinsY, minY, maxY);

  hMapYZ = new TH2D(Form("%sYZ", theName.Data()), Form("%sMapYZ", theName.Data()), nbinsY, minY, maxY, nbinsZ, minZ, maxZ);
  hRawYZ = new TH2D(Form("%sRawYZ", theName.Data()), Form("%sRawYZ", theName.Data()), nbinsY, minY, maxY, nbinsZ, minZ, maxZ);

  hWeight = new TH1D(Form("%sWeight", theName.Data()), Form("%sWeight", theName.Data()), hMapRZ->GetNbinsX(), minR, maxR);
  hEDep = new TH1D(Form("%sEDep", theName.Data()), Form("%sEDep", theName.Data()), 1000, 0, 20);
}

TOMapDet::~TOMapDet() {}

void TOMapDet::clear()
{
  hEDep->Reset();
  hWeight->Reset();
  hMap->Reset();
  hRawMap->Reset();
  hMapRZ->Reset();
  hRawRZ->Reset();
  hMapYZ->Reset();
  hRawYZ->Reset();
  hMapXY->Reset();
  hRawXY->Reset();
}

void TOMapDet::print()
{
  std::cout << hMap->GetName() << " has " << hMap->GetEntries() << std::endl;
}
int TOMapDet::doNorm(TH3D *hNormMap, TH2D *hNormRZ, TH2D *hNormYZ, TH2D *hNormXY)
{
  double binVal = 0;
  double binNorm = 0;
  int nzero = 0;
  for (int i = 0; i < hMap->GetNbinsX(); i++)
  {
    for (int j = 0; j < hMap->GetNbinsY(); j++)
    {
      for (int k = 0; k < hMap->GetNbinsZ(); k++)
      {
        binNorm = hNormMap->GetBinContent(i + 1, j + 1, k + 1);
        binVal = hRawMap->GetBinContent(i + 1, j + 1, k + 1) * QE;
        if (binVal == 0)
          ++nzero;
        if (binNorm > 0)
          hMap->SetBinContent(i + 1, j + 1, k + 1, binVal / binNorm);
      }
    }
  }
  for (int i = 0; i < hMapXY->GetNbinsX(); i++)
  {
    for (int j = 0; j < hMapXY->GetNbinsY(); j++)
    {
      binNorm = hNormXY->GetBinContent(i + 1, j + 1);
      binVal = hRawXY->GetBinContent(i + 1, j + 1) * QE;
      if (binNorm > 0)
        hMapXY->SetBinContent(i + 1, j + 1, binVal / binNorm);
    }
  }
  for (int i = 0; i < hMapYZ->GetNbinsX(); i++)
  {
    for (int j = 0; j < hMapYZ->GetNbinsY(); j++)
    {
      binNorm = hNormYZ->GetBinContent(i + 1, j + 1);
      binVal = hRawYZ->GetBinContent(i + 1, j + 1) * QE;
      if (binNorm > 0)
        hMapYZ->SetBinContent(i + 1, j + 1, binVal / binNorm);
    }
  }
  for (int i = 0; i < hMapRZ->GetNbinsX(); i++)
  {
    for (int j = 0; j < hMapRZ->GetNbinsY(); j++)
    {
      binNorm = hNormRZ->GetBinContent(i + 1, j + 1);
      binVal = hRawRZ->GetBinContent(i + 1, j + 1) * QE;
      double r = gridSpacing * (i + 1) + minR;
      double weight = ((r + gridSpacing) * (r + gridSpacing) - r * r) / (maxR * maxR - minR * minR);
      binVal /= weight;
      hWeight->SetBinContent(i + 1, weight);
      if (binNorm > 0)
        hMapRZ->SetBinContent(i + 1, j + 1, binVal / binNorm);
    }
  }
  std::cout << " normalized "
            << this->GetName() << " raw map entries "
            << hRawMap->GetEntries()
            << " zeros " << nzero << std::endl;
  return nzero;
}