//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//                                                                           //
//                                                                           //
//                         MaGe Simulation                                   //
//                                                                           //
//      This code implementation is the intellectual property of the         //
//      MAJORANA and Gerda Collaborations. It is based on Geant4, an         //
//      intellectual property of the RD44 GEANT4 collaboration.              //
//                                                                           //
//                        *********************                              //
//                                                                           //
//    Neither the authors of this software system, nor their employing       //
//    institutes, nor the agencies providing financial support for this      //
//    work  make  any representation or  warranty, express or implied,       //
//    regarding this software system or assume any liability for its use.    //
//    By copying, distributing or modifying the Program (or any work based   //
//    on on the Program) you indicate your acceptance of this statement,     //
//    and all its terms.                                                     //
//                                                                           //
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//---------------------------------------------------------------------------//
/**                                                            
* $Id:
*      
* CLASS DECLARATION:  MGGeneratorPb210.hh
*
*---------------------------------------------------------------------------//
*
* DESCRIPTION: 
*
*/
// Begin description of class here
/**
*
* Generates gammas as from Pb210 shielding; constructs root TF1 functions
* and TH1F histograms to sample energy, zenith angle, and origin, then
* produces a gamma at a random point on the lead shield, with the chosen
* zenith angle and energy.
* Currently, the simulator can produce second order photons, but will always
* produce first order photons.
* 
*
*/
// End class description
//
/**  
* SPECIAL NOTES:
* Using this class requires GSS.  The macro macros/Pb210Generator_BEGE.mac
* shows an example of how to use GSS with this class.
*
*/
//
// --------------------------------------------------------------------------//
/** 
* AUTHOR: Neil McFadden
* CONTACT: nmcfadde@unm.edu
* FIRST SUBMISSION:
* 
* REVISION:
* 
*/
// --------------------------------------------------------------------------//

#ifndef _MGGENERATORLGNDLIQUIDARGON_HH
#define _MGGENERATORLGNDLIQUIDARGON_HH

//---------------------------------------------------------------------------//
#include <CLHEP/Units/SystemOfUnits.h>
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Run.hh"

#include "TF1.h"
#include "TH1F.h"

#include "generators/MGVGenerator.hh"

//---------------------------------------------------------------------------//

class G4Event;
class G4Messenger;
class G4ParticleGun;
class G4Run;

using namespace CLHEP;

class MGGeneratorLGNDLiquidArgon : public MGVGenerator
{

public:
  MGGeneratorLGNDLiquidArgon();

  MGGeneratorLGNDLiquidArgon(const MGGeneratorLGNDLiquidArgon &);

  ~MGGeneratorLGNDLiquidArgon();
  //public interface
  void GeneratePrimaryVertex(G4Event *event);
  G4ThreeVector GetPrimary()
  {
    return fPrimary;
  }
  void SetParticlePosition(G4ThreeVector pos) { fPrimary = pos; }

  void GeneratePrimaryScan(G4Event *event);
  void GenerateZScan(G4Event *event);
  void DirectionDecider();
  void EnergyDecider();
  void PositionDecider();
  void PositionDecider(G4double x, G4double y, G4double z, G4double binWidth);
  void ParticleDecider();
  void PositionXYDecider();
  G4bool IsInArgon(G4ThreeVector rp);

  //Messenger Commands
  void SetRadius(G4double r) { fRadiusMax = r; }
  void SetRadiusMin(G4double r) { fRadiusMin = r; }
  void SetHeight(G4double h)
  {
    fZ = h;
    MGLog(routine) << " setting fZ  " << fZ << endlog;
  }
  void SetCenterVector(G4ThreeVector vec)
  {
    fCenterVector = vec;
    MGLog(routine) << " setting fCenterVector ( " << vec.x() << " , " << vec.y() << " , " << vec.z() << " )" << endlog;
  }
  void SetParticleType(G4String str) { fParticleType = str; }
  void SetPhotonMean(G4double v)
  {
    fPhotonMean = v;
    MGLog(routine) << " setting fPhotonMean " << fPhotonMean / nm << " nm " << endlog;
  }
  void SetPhotonSigma(G4double v)
  {
    fPhotonSigma = v;
    MGLog(routine) << " setting fPhotonSigma " << fPhotonSigma / nm << " nm" << endlog;
  }

  void SetBinWidth(G4double width)
  {
    MGLog(routine) << " setting bin width  " << width << endlog;
    fBinWidth = width;
  }

  void EndOfRunAction(const G4Run *grun)
  {
    MGLog(routine) << "  ****** EndOfRun  " << grun->GetRunID() << "  ****** "
                   << " \n \t total events  " << grun->GetNumberOfEvent()
                   << " in Argon " << nInArgon
                   << "  \n ****** " << endlog;
  }

  void SetNParticles(G4double N) { fNParticles = N; }
  void SetScanBinX(G4int bin) { fScanBinX = bin; }
  void SetScanBinY(G4int bin) { fScanBinY = bin; }
  void SetScanBinZ(G4int bin) { fScanBinZ = bin; }
  void SetGeneratePrimaryScan(G4bool val) { fSetPrimaryScan = val; }
  void SetGenerateZScan(G4bool val) { fSetZScan = val; }

private:
  static const G4double LambdaE;
  G4ParticleGun *fParticleGun;
  //particle properties
  G4double fCurrentEnergy;  // energy of current particle
  G4ThreeVector fDirection; // direction of momentum
  G4ThreeVector fPrimary;   // current primary vertex
  G4double fRadiusMax;
  G4double fRadiusMin;
  G4double fZ;
  G4double fZ0; // set to bottom of cryostat
  G4double fBinWidth;
  G4double fNParticles;
  G4ThreeVector fCenterVector;
  G4String fParticleType;
  G4double fPhotonMean;
  G4double fPhotonSigma;
  G4int fScanBinX;
  G4int fScanBinY;
  G4int fScanBinZ;
  G4double fScanX;
  G4double fScanY;
  G4double fScanZ;
  G4int nInArgon;
  G4int nOutArgon;
  G4bool fSetPrimaryScan;
  G4bool fSetZScan;
};
#endif
