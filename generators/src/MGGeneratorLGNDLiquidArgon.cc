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
//    Neither the authors of this software syste> employing       //
//    institutes, nor the agencies providing financial support for this      //
//    work  make  any representation or  warranty, express or implied,       //
//    regarding this software system or assume any liability for its use.    //
//    By copying, distributing or modifying the Program (or any work based   //
//    on on the Program) you indicate your acceptance of this statement,     //
//    and all its terms.                                                     //
//                                                                           //
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//---------------------------------------------------------------------------//
//                                                          
// $Id:
//      
// CLASS IMPLEMENTATION:  MGGeneratorLGNDLiquidArgon.cc
//
//---------------------------------------------------------------------------//
/**
* SPECIAL NOTES:
*/
//
//---------------------------------------------------------------------------//
/**
* AUTHOR: Neil McFadden
* CONTACT: nmcfadde@unm.edu
 * FIRST SUBMISSION: 
* 
* REVISION:
*
*
*/
//---------------------------------------------------------------------------//

#include "Randomize.hh"

#include "G4ios.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Alpha.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleGun.hh"
#include "G4Run.hh"

#include "G4PhysicalVolumeStore.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"

#include "TMath.h"

#include "generators/MGGeneratorLGNDLiquidArgon.hh"
#include "generators/MGGeneratorLGNDLiquidArgonMessenger.hh"
#include "io/MGLogger.hh"
#include "legendgeometry/LGND_200_Cryostat.hh"
#include "bacongeometry/BACON_Baseline.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"

#include "TH2D.h"
#include "TFile.h"
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//

using namespace CLHEP;

const G4double MGGeneratorLGNDLiquidArgon::LambdaE = twopi * 1.973269602e-16 * m * GeV;

MGGeneratorLGNDLiquidArgon::MGGeneratorLGNDLiquidArgon()
{
  fGeneratorName = "LiquidArgon";
  fG4Messenger = new MGGeneratorLGNDLiquidArgonMessenger(this);
  fParticleGun = new G4ParticleGun(1);
  fRadiusMax = 0;
  fRadiusMin = 0;
  fZ = 0;
  fZ0 = 0; // set to bottom of cryostat
  fBinWidth = 0;
  fNParticles = 1;
  fParticleType = G4String("opticalphoton");
  fPhotonMean = 128.0 * nm;
  fPhotonSigma = 2.929 * nm;
  MGLog(routine) << " fPhotonMean   " << fPhotonMean / nm
                 << " fPhotonSigma  " << fPhotonSigma / nm << endlog;
}

MGGeneratorLGNDLiquidArgon::MGGeneratorLGNDLiquidArgon(const MGGeneratorLGNDLiquidArgon &other) : MGVGenerator(other)
{
  ;
}

MGGeneratorLGNDLiquidArgon::~MGGeneratorLGNDLiquidArgon()
{
  delete fG4Messenger;
  delete fParticleGun;
}

void MGGeneratorLGNDLiquidArgon::DirectionDecider()
{
  G4double phi = 2 * pi * G4UniformRand();
  G4double costheta = 2 * G4UniformRand() - 1;
  G4double theta = acos(costheta); //pi*G4UniformRand();

  G4double px = cos(phi) * sin(theta);
  G4double py = sin(phi) * sin(theta);
  G4double pz = cos(theta);

  fDirection.setX(px);
  fDirection.setY(py);
  fDirection.setZ(pz);
}

void MGGeneratorLGNDLiquidArgon::EnergyDecider()
{
  fCurrentEnergy = 0;
  G4double waveL = 0;

  if (fParticleType == "opticalphoton")
  {
    //Gaussian
    waveL = G4RandGauss::shoot(fPhotonMean, fPhotonSigma);
    //Some materials don't have optical properties bellow 115*nm
    if (waveL < 115 * nm)
    {
      MGLog(routine) << " photon wavelength was  " << waveL / nm << " set to 115 nm " << endlog;
      waveL = 115 * nm;
    }
    fCurrentEnergy = LambdaE / waveL;
  }
  else
    MGLog(error) << "Warned fCurrentEnergy is not set " << endlog;

  MGLog(debugging) << " photon wavelength " << waveL / nm << " nm  energy " << fCurrentEnergy / eV << " eV " << endlog;
}

void MGGeneratorLGNDLiquidArgon::PositionDecider()
{
  // boundary protection is in GeneratePrimaryVertex which calls this function
  G4ThreeVector rpos(1, 1, 1);
  G4bool isIn = false;

  //Generate random points in a bound box around inner_cryostat
  int errorCounter = 0;

  do
  {
    //G4double r = (fRadiusMax-fRadiusMin)*rand*rand+fRadiusMin;
    /** fixed by mgold  PDF = (2/R^2)*r **/
    G4double rand = G4UniformRand();
    G4double c2 = pow(fRadiusMax, 2.) - pow(fRadiusMin, 2.);
    G4double r = sqrt(c2 * rand + pow(fRadiusMin, 2.));
    G4double theta = 2 * pi * G4UniformRand();
    G4double z = fZ + fBinWidth * G4UniformRand();
    rpos.setRhoPhiZ(r, theta, z);
    rpos = rpos + fCenterVector;

    //check that point in in "Argon-Liq"
    isIn = IsInArgon(rpos);
    errorCounter++;
    if (errorCounter % 1000 == 0)
    {
      G4Navigator *theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
      G4cout << " out of LAr counter " << errorCounter
             << " fBinWidth " << fBinWidth
             << " fRadius max " << fRadiusMax
             << " fRadiusMin " << fRadiusMin
             << " at pos r= " << rpos.perp() << " phi= "
             << " , z= " << rpos.z()
             << " volume = " << theNavigator->LocateGlobalPointAndSetup(rpos)->GetName()
             << G4endl;
    }
    if (errorCounter > 10000)
    {
      G4cout << "errorCounter has exceeded 1e4 counts!" << G4endl;
      MGLog(fatal) << "errorCounter has exceeded 1e4 counts!" << endlog;
    }
  } while (!isIn);

  fPrimary = rpos;
}
void MGGeneratorLGNDLiquidArgon::PositionDecider(G4double xPos, G4double yPos, G4double zPos, G4double binWidth)
{

  G4ThreeVector rpos(1, 1, 1);
  G4bool isIn = false;
  int errorCounter = 0;
  //Generate random points in a bound box around inner_cryostat
  do
  {
    //pdf_r = (2/R^2)*r
    //G4double r = fRadius*std::sqrt(G4UniformRand());
    G4double x = xPos, y = yPos, z = zPos;
    G4double rand = G4UniformRand();
    x += binWidth * rand;
    rand = G4UniformRand();
    y += binWidth * rand;
    rand = G4UniformRand();
    z += binWidth * rand;
    rpos.setX(x);
    rpos.setY(y);
    rpos.setZ(z);
    //Is it in the Argon?
    //Note that in the Stepping Action, a step or two are taken before intial position is stored
    isIn = IsInArgon(rpos);
    errorCounter++;
    if (errorCounter > 1e2)
    {
      fPrimary = rpos;
      break;
    }
  } while (!isIn);
  fPrimary = rpos;
}
G4bool MGGeneratorLGNDLiquidArgon::IsInArgon(G4ThreeVector rpos)
{
  bool isit = false;
  //This is how Geant4 suggests you should randomly generate a point in a volume
  G4ThreeVector myPoint = rpos;
  G4Navigator *theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
  G4VPhysicalVolume *myVolume = theNavigator->LocateGlobalPointAndSetup(myPoint);
  if (myVolume->GetName() == "Detector")
    isit = true;
  if (myVolume->GetName() == "argonGasPhysical")
    isit = true;

  return isit;
}

void MGGeneratorLGNDLiquidArgon::ParticleDecider()
{
  if (fParticleType == "opticalphoton")
  {
    fParticleGun->SetParticleDefinition(G4OpticalPhoton::OpticalPhotonDefinition());
  }
  else if (fParticleType == "gamma")
  {
    fParticleGun->SetParticleDefinition(G4Gamma::GammaDefinition());
  }
  else if (fParticleType == "beta")
  {
    fParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());
  }
  else if (fParticleType == "alpha")
  {
    fParticleGun->SetParticleDefinition(G4Alpha::AlphaDefinition());
  }
  else
  {
    MGLog(error) << "Unknow paticle type " << fParticleType << ", if real particle type, add it to the code!" << endlog;
  }
}

void MGGeneratorLGNDLiquidArgon::GeneratePrimaryVertex(G4Event *event)
{
  //User inputs specific height fZ, max height fZ+binwidth, fNParticles
  // max and min radius
  BACON_Baseline *cryostat = new BACON_Baseline("LGND200generatorCryostat");
  G4double cryoR = cryostat->GetCryostatID() / 2.;
  G4double cryoHalfZ = cryostat->GetCryostatHeight() / 2.;
  G4double sipmDimX = cryostat->GetSipmDimX();
  G4double sipmDimY = cryostat->GetSipmDimY();
  delete cryostat;

  if (fBinWidth == 0)
  {
    fBinWidth = 2 * cryoHalfZ;
    MGLog(routine) << " WARNING resetting fBinWdith to   " << fBinWidth << endl;
  }

  G4double zMin = fZ + fCenterVector.z();
  G4double zMax = fZ + fCenterVector.z() + fBinWidth;

  if (fRadiusMax == 0)
  {
    fRadiusMax = cryoR;
    MGLog(routine) << " WARNING resetting fRadiumMax to   " << fRadiusMax << endl;
  }
  if (zMax > cryoHalfZ || fBinWidth == 0)
  {
    fBinWidth = cryoHalfZ - fZ - fCenterVector.z();
    MGLog(routine) << " WARNING >zMax resetting fBinWdith to   " << fBinWidth << endl;
  }
  if (zMin < -cryoHalfZ)
  {
    fZ = -1.0 * (cryoHalfZ + fCenterVector.z());
    MGLog(routine) << " WARNING resetting fZ cryoHalfZ " << cryoHalfZ << " fCenterVector.z() " << fCenterVector.z() << " WARNING <zMin resetting fZ   " << fZ << endl;
  }

  if (event->GetEventID() == 0)
  {
    MGLog(routine) << " all in mm:  "
                   << " \n sipmDimX " << sipmDimX
                   << " \n sipmDimY " << sipmDimY
                   << " \n cryo rmax  " << cryoR
                   << " \n cryo zmax  " << cryoHalfZ
                   << " \n cryo zmin  " << -1. * cryoHalfZ
                   << " \n fRadiusMax " << fRadiusMax
                   << " \n fRadiusMin " << fRadiusMin
                   << " \n fZ " << fZ
                   << " \n fBinWidth " << fBinWidth
                   << " \n Z min " << fZ + fCenterVector.z()
                   << " \n Z max  " << fZ + fCenterVector.z() + fBinWidth
                   << " \n fCenterVector r= " << fCenterVector.perp() << " phi= " << fCenterVector.phi() << " z= " << fCenterVector.z()
                   << " \n fNParticles " << fNParticles
                   << " \n photons with :  \n fPhotonMean   " << fPhotonMean / nm
                   << "  fPhotonSigma  " << fPhotonSigma / nm << " nm " << endlog;
  }

  fParticleGun->SetParticlePolarization(G4ThreeVector(2 * G4UniformRand() - 1, 2 * G4UniformRand() - 1, 2 * G4UniformRand() - 1));

  //what is the particle
  ParticleDecider();
  //determine particle momentum direction
  DirectionDecider();

  //determine particle position
  //PositionDecider();
  PositionDecider();
  MGLog(debugging) << "Generator vertex " << fPrimary << endlog;
  //determine particle energy
  EnergyDecider();

  //particle direction, position, and energy sent to ParticleGun
  fParticleGun->SetParticlePosition(fPrimary);
  //G4cout<<"("<<fPrimary.x()<<","<<fPrimary.y()<<","<<fPrimary.z()<<")"<<G4endl;
  fParticleGun->SetParticleMomentumDirection(fDirection);
  fParticleGun->SetParticleEnergy(fCurrentEnergy);
  fParticleGun->SetNumberOfParticles(1);

  //vertex generated by ParticleGun
  for (int ip = 0; ip < fNParticles; ++ip)
    fParticleGun->GeneratePrimaryVertex(event);
}
