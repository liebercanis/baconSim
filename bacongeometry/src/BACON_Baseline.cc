#include "G4Material.hh"
#include "G4Polycone.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4NistManager.hh"

//#include <cmath>//floor() function
#include <math.h>

#include "geometry/MGGeometryGlobals.hh"
#include "io/MGLogger.hh"
#include "bacongeometry/BACON_Baseline.hh"
#include "bacongeometry/BACON_BaselineMessenger.hh"

using namespace CLHEP;

const G4double BACON_Baseline::LambdaE = twopi * 1.973269602e-16 * m * GeV;
const G4double BACON_Baseline::inch = 2.54 * cm;

BACON_Baseline::BACON_Baseline(G4String version) : MGGeometryDetector(version),
                                                   fMessenger(0)
{
  fLiquid = "Argon-Liq";
  fMessenger = new BACON_BaselineMessenger(this);
  fCryoOD = 20 * inch;
  fCryoThickness = 0.5 * inch;
  fCryoID = fCryoOD - 2 * fCryoThickness;
  //Inner height is measured to be 22.5,
  //if lid thickness of top and bottom are added in
  //correct value is 24.5 inches
  //fCryoHeight = 22.5*inch;
  fCryoHeight = 23 * inch; //24.5*inch;
  fDelta = 0.000001 * m;
  fSipmDimX = 300.0 * mm;
  fSipmDimY = 3.0 * mm;
}

BACON_Baseline::~BACON_Baseline()
{
}

void BACON_Baseline::ConstructDetector()
{
  /*
  static const G4double inch = 2.54*cm;
  G4double cryoOD = 20*inch;
  G4double cryoThickness = 0.5*inch;
  G4double cryoID = cryoOD-2*cryoThickness;
  G4double cryoHeight = 23*inch;
  G4double delta = 0.000001*m;
  */

  //G4Material *argon = G4Material::GetMaterial("Argon-Liq");
  //G4Material *xenonDopedArgon = G4Material::GetMaterial("Xenon-Doped-Argon-Liq");
  G4Box *exptBox = new G4Box("exptBox", 100. * m, 100. * m, 100. * m);
  G4VisAttributes *ArVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0, 0.01)); // magenta, 50% opaque
  ArVisAtt->SetForceWireframe(true);

  //theDetectorLogical = new G4LogicalVolume(expt"Box, argon, "theDetectorLogical");
  theDetectorLogical = new G4LogicalVolume(exptBox, G4Material::GetMaterial(fLiquid), "theDetectorLogical");
  G4cout << "Liquid inside cryostat is " << fLiquid << G4endl;
  //theDetectorLogical = new G4LogicalVolume(exptBox, xenonDopedArgon, "theDetectorLogical");
  theDetectorLogical->SetVisAttributes(ArVisAtt);

  G4Material *steel = G4Material::GetMaterial("Steel");
  G4NistManager *nistMan = G4NistManager::Instance();
  G4Material *delrin = nistMan->FindOrBuildMaterial("G4_POLYOXYMETHYLENE");

  /*
  G4Tubs* cryoTubeOuter = new G4Tubs("cryoTubOuter",0,fCryoOD/2.,fCryoHeight/2.,0,2*pi);
  //Lid is 1.0 inch thick, walls are 0.5 inches thick
  G4Tubs* cryoTubeInner = new G4Tubs("cryoTubInner",0,fCryoID/2,fCryoHeight/2.-2*fCryoThickness,0,2*pi);
  G4SubtractionSolid *cryostatSolid = new G4SubtractionSolid("CryostatSolid",cryoTubeOuter,cryoTubeInner);
  */
  G4double wellOD = 5 * inch;
  G4double wellHeight = 8. * inch + 2. * fCryoThickness;
  G4double wellThickness = 0.25 * inch;
  const G4int cryoN = 6;
  //Lid is 1" thick, walls are 1/2" thick,fCryoThickness = 1/2"
  G4double cryoZ[cryoN] = {-fCryoHeight / 2, -fCryoHeight / 2 + fCryoThickness, -fCryoHeight / 2 + fCryoThickness,
                           fCryoHeight / 2, fCryoHeight / 2, fCryoHeight / 2 + 2. * fCryoThickness};
  G4double cryoRmin[cryoN] = {0, 0, fCryoID / 2, fCryoID / 2, wellOD / 2., wellOD / 2.};
  G4double cryoRmax[cryoN] = {fCryoOD / 2, fCryoOD / 2, fCryoOD / 2, fCryoOD / 2, fCryoOD / 2, fCryoOD / 2};
  G4Polycone *cryostatSolid = new G4Polycone("", 0, 2 * pi, cryoN, cryoZ, cryoRmin, cryoRmax);

  G4VisAttributes *cryoVisAtt = new G4VisAttributes(G4Colour(0.8, 0.8, 0.8, 0.1)); //cryoVisAtt->SetVisibility(true);
  //cryoVisAtt->SetForceWireframe(true);
  //cryoVisAtt->SetVisibility(false);
  //cryoVisAtt->SetForceAuxEdgeVisible(true);
  G4LogicalVolume *cryostatLogical = new G4LogicalVolume(cryostatSolid, steel, "CryostatLogical");
  cryostatLogical->SetVisAttributes(cryoVisAtt);

  const G4int wellN = 4;
  G4double wellZ[wellN] = {-wellHeight / 2., -wellHeight / 2. + wellThickness, -wellHeight / 2. + wellThickness, wellHeight / 2.};
  G4double wellRmin[wellN] = {0, 0, wellOD / 2. - wellThickness, wellOD / 2. - wellThickness};
  G4double wellRmax[wellN] = {wellOD / 2., wellOD / 2., wellOD / 2., wellOD / 2.};

  G4Polycone *wellSolid = new G4Polycone("", 0, 2 * pi, wellN, wellZ, wellRmin, wellRmax);
  G4LogicalVolume *wellLogical = new G4LogicalVolume(wellSolid, steel, "WellLogical");
  G4VisAttributes *wellVisAtt = new G4VisAttributes(G4Colour(0.8, 0.8, 0.8, 0.01));
  wellVisAtt->SetForceWireframe(true);
  wellLogical->SetVisAttributes(wellVisAtt);

  G4VPhysicalVolume *cryostatPhysical = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), cryostatLogical, "Cryostat", theDetectorLogical, false, 0);
  G4VPhysicalVolume *wellPhysical = new G4PVPlacement(0, G4ThreeVector(0, 0, fCryoHeight / 2 - wellHeight / 2. + 2 * fCryoThickness), wellLogical, "CryoWell", theDetectorLogical, false, 0);

  //Dumb thing about having the Guard Vacuum Can off center, is that all the other volumes that are cut out volumes also have to be off center...
  //canShift is the variable to define this offset
  G4double canOD = 22.750 * inch;
  G4double canHeight = 32.41 * inch;
  G4double canThickness = 0.25 * inch;
  G4double canShift = 2.5 * inch;
  G4Tubs *outerCanSolid = new G4Tubs("outerCanSolid", 0, canOD / 2., canHeight / 2., 0, 2 * pi);
  G4Tubs *innerCanSolid = new G4Tubs("innerCanSolid", 0, canOD / 2. - canThickness, canHeight / 2. - 2 * fCryoThickness, 0, 2 * pi);
  G4SubtractionSolid *canSolid = new G4SubtractionSolid("canSolid", outerCanSolid, innerCanSolid);

  G4LogicalVolume *canLogical = new G4LogicalVolume(canSolid, steel, "canLogical");
  canLogical->SetVisAttributes(wellVisAtt);
  canLogical->SetVisAttributes(wellVisAtt);

  G4VPhysicalVolume *canPhysical = new G4PVPlacement(0, G4ThreeVector(0, 0, canShift), canLogical, "CryoCan", theDetectorLogical, false, 0);

  G4Material *rock = G4Material::GetMaterial("Rock");
  //  G4Box* outerBox = new G4Box("outerBox", 100.*m - fDelta, 100.*m -fDelta, 100.*m-fDelta);
  G4Box *outerBox = new G4Box("outerBox", 100. * m, 100. * m, 100. * m);
  G4Box *innerBox = new G4Box("innerBox", 20.0 * m, 20.0 * m, 20.0 * m);
  G4SubtractionSolid *lab = new G4SubtractionSolid("lab", outerBox, innerBox);
  G4VisAttributes *rockVisAtt = new G4VisAttributes(G4Colour(0.64, 0.64, 0.64, 0.1)); //gray, 10% opaque
  G4LogicalVolume *labLog = new G4LogicalVolume(lab, rock, "CavernRockLogical");
  rockVisAtt->SetForceWireframe(true);
  labLog->SetVisAttributes(rockVisAtt);
  /*G4PVPlacement* labPhys =*/new G4PVPlacement(0, G4ThreeVector(0, 0, canShift), labLog, "lab", theDetectorLogical, false, 0);

  G4Material *air = G4Material::GetMaterial("Air");
  //G4Box* airboundary = new G4Box("airboundary", 20.0*m - fDelta, 20.0*m - fDelta, 20.0*m - fDelta);
  //G4Tubs* cryostatvoid = new G4Tubs("cryostatvoid", 0, fCryoOD/2.+fDelta, fCryoHeight/2. +fDelta, 0, 2*pi);
  G4Box *airboundary = new G4Box("airboundary", 20.0 * m, 20.0 * m, 20.0 * m);
  G4Tubs *cryostatvoid = new G4Tubs("cryostatvoid", 0, canOD / 2., canHeight / 2., 0, 2 * pi);
  G4SubtractionSolid *airspace = new G4SubtractionSolid("airspace", airboundary, cryostatvoid);
  G4VisAttributes *airVisAtt = new G4VisAttributes(G4Colour(0.64, 0.64, 0.64, 0.01)); //gray, 1% opaque
  G4LogicalVolume *airLog = new G4LogicalVolume(airspace, air, "LabAirLogical");
  airVisAtt->SetForceWireframe(true);
  airLog->SetVisAttributes(airVisAtt);
  G4PVPlacement *airSpacePhys = new G4PVPlacement(0, G4ThreeVector(0, 0, canShift), airLog, "airSpace", theDetectorLogical, false, 0);

  //Scintillator Panels
  //large panels
  //G4Box* scintPanel = new G4Box("scintPanel",8.5/2*inch,18.0/2*inch,0.9/2*cm); //x,y,z
  G4Box *scintPanel = new G4Box("scintPanel", 8.5 / 2 * inch, 17.0 / 2 * inch, 0.35 / 2 * cm); //x,y,z
  G4VisAttributes *scintVis = new G4VisAttributes(G4Colour(1, 0, 0));
  G4LogicalVolume *scintLogical = new G4LogicalVolume(scintPanel, G4Material::GetMaterial("PolystyreneFiber"), "LogicalPanel");
  scintLogical->SetVisAttributes(scintVis);
  //Do not need to add canShift because the motherVolume is the airSpace
  //airSpace is already shifted when placed.
  G4PVPlacement *physicalScintPanel1 = new G4PVPlacement(0, G4ThreeVector(0, 0, canHeight / 2. + 4 * inch), scintLogical, "ScintPanel1", airLog, false, 0);
  G4RotationMatrix *scintRotation = new G4RotationMatrix();
  scintRotation->rotateZ(pi / 2);
  G4PVPlacement *physicalScintPanel2 = new G4PVPlacement(scintRotation, G4ThreeVector(0, 0, -canHeight / 2. - 4 * inch), scintLogical, "ScintPanel2", airLog, false, 0);

  //placing the outer can for the guard vacuum
  //not really needed for LAr light, but important for muon simulations
  G4Material *vacuum = G4Material::GetMaterial("Vacuum");
  const G4int vacN = 6;
  G4double gapLow = canHeight / 2. - fCryoHeight / 2. - canShift - 2 * fCryoThickness;
  G4double gapHi = canHeight / 2. - fCryoHeight / 2. + canShift - 2 * fCryoThickness;

  G4double vacZ[vacN] = {-fCryoHeight / 2. - gapLow, -fCryoHeight / 2., -fCryoHeight / 2., fCryoHeight / 2. + 2 * fCryoThickness, fCryoHeight / 2. + 2 * fCryoThickness, fCryoHeight / 2. + gapHi};
  G4double vacRmin[vacN] = {0, 0, fCryoOD / 2., fCryoOD / 2., 0, 0};
  G4double vacRmax[vacN] = {canOD / 2. - canThickness, canOD / 2. - canThickness, canOD / 2. - canThickness, canOD / 2. - canThickness, canOD / 2. - canThickness, canOD / 2. - canThickness};

  G4Polycone *vaccumSolid = new G4Polycone("", 0, 2 * pi, vacN, vacZ, vacRmin, vacRmax);
  G4LogicalVolume *vacuumLogical = new G4LogicalVolume(vaccumSolid, vacuum, "vacuumLogical");
  G4VisAttributes *vacuumVisAtt = new G4VisAttributes(G4Colour(1, 0, 0));
  vacuumVisAtt->SetForceWireframe(true);
  vacuumLogical->SetVisAttributes(vacuumVisAtt);
  G4VPhysicalVolume *vacuumPhysical = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), vacuumLogical, "Vacuum", theDetectorLogical, false, 0);

  G4Tubs *vacWellSolid = new G4Tubs("vacWellSolid", 0, wellOD / 2. - wellThickness, wellHeight / 2. - wellThickness / 2., 0, 2 * pi);
  G4LogicalVolume *vacWellLogical = new G4LogicalVolume(vacWellSolid, vacuum, "vacuumWellLogical");
  vacWellLogical->SetVisAttributes(vacuumVisAtt);
  G4VPhysicalVolume *vacWellPhysical = new G4PVPlacement(0, G4ThreeVector(0, 0, fCryoHeight / 2 - wellHeight / 2. + wellThickness / 2. + 2 * fCryoThickness), vacWellLogical, "vacuumWell", theDetectorLogical, false, 0);
  //Liquid height 23*119/1.3954/105 = 18.68 inch
  //23-18.68
  G4double gasHeight = 4.31 * inch;
  G4Material *argonGas = G4Material::GetMaterial("Argon");
  G4Tubs *argonGasSolid = new G4Tubs("argonGasSolid", wellOD / 2., fCryoID / 2, gasHeight / 2., 0, 2 * pi);
  G4LogicalVolume *argonGasLogical = new G4LogicalVolume(argonGasSolid, argonGas, "argonGasLogical");
  G4VisAttributes *argonGasVisAtt = new G4VisAttributes(G4Colour(1, 0., 1., 0.1)); //gray, 1% opaque
  argonGasLogical->SetVisAttributes(argonGasVisAtt);
  G4VPhysicalVolume *argonGasPhysical = new G4PVPlacement(0, G4ThreeVector(0, 0, fCryoHeight / 2 - gasHeight / 2), argonGasLogical, "argonGasPhysical", theDetectorLogical, false, 0);

  G4Element *elC = new G4Element("Carbon", "C", 6., 12.011 * g / mole);
  G4Element *elH = new G4Element("Hydrogen", "H", 1., 1.00794 * g / mole);
  // Z =14, A
  G4Element *elSi = new G4Element("Silicon", "Si", 14., 28.0855 * g / mole);
  G4Element *elO = new G4Element("Oxygen", "O", 8., 15.9994 * g / mole);

  //Glass
  G4Material *Glass = new G4Material("Glass", 1.032 * g / cm3, 2);
  Glass->AddElement(elC, 91.533 * perCent);
  Glass->AddElement(elH, 8.467 * perCent);

  const G4int nGlass = 2;
  G4double waveGlass[nGlass] = {LambdaE / (650 * nm), LambdaE / (115) * nm};
  G4double indexGlass[nGlass] = {1.458, 1.458};
  G4double absGlass[nGlass] = {1 * m, 1 * m};
  auto glassOpticalTable = new G4MaterialPropertiesTable();
  glassOpticalTable->AddProperty("RINDEX", waveGlass, indexGlass, nGlass);
  glassOpticalTable->AddProperty("ABSLENGTH", waveGlass, absGlass, nGlass);

  Glass->SetMaterialPropertiesTable(glassOpticalTable);

  //silicon
  G4Material *SiMaterial = new G4Material("Silicon", 14., 28.090 * g / mole, 2.33 * g / cm3);

  // quartz (SiO2, crystalline)
  G4Material *quartzMaterial = new G4Material("quartzMaterial", 2.64 * g / cm3, 2);
  quartzMaterial->AddElement(elSi, 33 * perCent);
  quartzMaterial->AddElement(elO, 67 * perCent);

  const G4int nQuartz = 24;
  // parameterization wavelengths in ev
  G4double waveQuartz[nQuartz] = {
      7.2093 * nm,
      7.2941 * nm,
      7.3810 * nm,
      7.4699 * nm,
      7.5610 * nm,
      7.6543 * nm,
      7.7500 * nm,
      7.8481 * nm,
      7.9487 * nm,
      8.0519 * nm,
      8.1579 * nm,
      8.2667 * nm,
      8.3784 * nm,
      8.4932 * nm,
      8.6111 * nm,
      8.7324 * nm,
      8.8571 * nm,
      8.9855 * nm,
      9.1176 * nm,
      9.2537 * nm,
      9.3939 * nm,
      9.5385 * nm,
      9.6875 * nm,
      9.8413 * nm};
  G4double ABSQUARTZ[nQuartz] = {
      0.1179,
      0.1298,
      0.1542,
      0.2050,
      0.2873,
      0.3913,
      0.5100,
      0.6487,
      0.7982,
      0.9194,
      0.9810,
      0.9965,
      0.9989,
      0.9992,
      0.9990,
      0.9988,
      0.9986,
      0.9984,
      0.9981,
      0.9979,
      0.9978,
      0.9978,
      0.9981,
      0.9978};

  G4double RINDEXQUARTZ[nQuartz];
  for (int iq = 0; iq < nQuartz; ++iq)
    RINDEXQUARTZ[iq] = 1.46;
  auto quartzOpticalTable = new G4MaterialPropertiesTable();
  quartzOpticalTable->AddProperty("RINDEX", waveQuartz, RINDEXQUARTZ, nQuartz);
  quartzOpticalTable->AddProperty("ABSLENGTH", waveQuartz, ABSQUARTZ, nQuartz)->SetSpline(true);

  quartzMaterial->SetMaterialPropertiesTable(quartzOpticalTable);

  //Glass tube for a simple PMT
  //surface between tpb and PMT will have QE LogicalBorder

  ///*
  G4double pmtRadius = (3.215 / 2.) * inch;
  G4double pmtHeight = 6. * inch;
  G4double pmtThickness = 1 * um;
  G4double pmtHousingThickness = 1. * mm;
  G4double pmtSpacing = 0.5 * inch;
  //Lid is double the thickness of the sides of the cryostat
  G4double pmtPlacing = pmtHeight / 2. + 2 * fCryoThickness;
  //*/
  /*
  G4double pmtHousingThickness = 1.*mm;
  G4double pmtHeight = 1*cm;  
  G4double pmtRadius = fCryoID/2. - pmtHousingThickness;
  */

  //half lengths pX,pY,pZ
  G4Tubs *pmtSolid = new G4Tubs("pmtSolid", 0, pmtRadius, pmtThickness / 2., 0, 2 * pi);
  G4LogicalVolume *pmtLogical = new G4LogicalVolume(pmtSolid, Glass, "pmtLogical");
  G4VisAttributes *pmtVisAtt = new G4VisAttributes(G4Colour(1, 0.0, 0.0));
  pmtVisAtt->SetForceSolid(true);
  pmtLogical->SetVisAttributes(pmtVisAtt);
  // these are half length dimensions

  G4double sidimX = fSipmDimX;
  G4double sidimZ = fSipmDimY;
  G4double sidimY = 0.5 * mm;
  G4Box *sipmSolid = new G4Box("sipmSolid", sidimX, sidimY, sidimZ);
  G4LogicalVolume *sipmLogical = new G4LogicalVolume(sipmSolid, SiMaterial, "sipmLogical");
  G4VisAttributes *sipmVisAtt = new G4VisAttributes(G4Colour(1, 0.0, 0.0));
  sipmVisAtt->SetForceWireframe(true);
  sipmLogical->SetVisAttributes(sipmVisAtt);

  G4double siOffset = 17.6 * mm;
  G4double quartzZlength = siOffset / 2. + 2. * sidimZ;
  G4Box *sipmQuartzSolid = new G4Box("sipmQuartzSolid", sidimX, sidimY, quartzZlength);
  G4LogicalVolume *sipmQuartzLogical = new G4LogicalVolume(sipmQuartzSolid, quartzMaterial, "sipmQuartzLogical");
  G4VisAttributes *sipmQuartzVisAtt = new G4VisAttributes(G4Colour(0, 1, 0.0));
  sipmQuartzVisAtt->SetForceWireframe(true);
  sipmQuartzLogical->SetVisAttributes(sipmQuartzVisAtt);

  //sipm  backing
  G4double sipmBackZlength = siOffset * 5. / 2. + 2. * sidimZ;
  G4Box *sipmBackBox = new G4Box("sipmBackBox", sidimX, sidimY, sipmBackZlength);
  G4LogicalVolume *sipmBackLogical = new G4LogicalVolume(sipmBackBox, delrin, "sipmBackLogical");
  G4VisAttributes *sipmBackVisAtt = new G4VisAttributes(G4Color(.4, .6, .8));
  sipmBackLogical->SetVisAttributes(sipmBackVisAtt);

  G4VPhysicalVolume *pmtPhysical0 = new G4PVPlacement(0, G4ThreeVector(0, (1. / 2.) * fCryoID / 2, -(fCryoHeight / 2.) + 0.5 * pmtHeight + pmtPlacing - pmtThickness / 2. + pmtSpacing), pmtLogical, "physicalPMT_0", theDetectorLogical, false, 0);
  G4VPhysicalVolume *pmtPhysical1 = new G4PVPlacement(0, G4ThreeVector(0, -(1. / 2.) * fCryoID / 2, -(fCryoHeight / 2.) + 0.5 * pmtHeight + pmtPlacing - pmtThickness / 2. + pmtSpacing), pmtLogical, "physicalPMT_1", theDetectorLogical, false, 0);

  /* add sipm physical */
  G4double siZcenter = fCryoHeight / 4;
  G4ThreeVector siCenter0(0, 0, siZcenter + 2.5 * siOffset);
  G4ThreeVector siCenter1(0, 0, siZcenter + 1.5 * siOffset);
  G4ThreeVector siCenter2(0, 0, siZcenter + 0.5 * siOffset);
  G4ThreeVector siCenter3(0, 0, siZcenter - 0.5 * siOffset);
  G4ThreeVector siCenter4(0, 0, siZcenter - 1.5 * siOffset);
  G4ThreeVector siCenter5(0, 0, siZcenter - 2.5 * siOffset);
  G4VPhysicalVolume *sipmPhysical0 = new G4PVPlacement(0, siCenter0, sipmLogical, "physicalSIPM_0", theDetectorLogical, false, 0);
  G4VPhysicalVolume *sipmPhysical1 = new G4PVPlacement(0, siCenter1, sipmLogical, "physicalSIPM_1", theDetectorLogical, false, 0);
  G4VPhysicalVolume *sipmPhysical2 = new G4PVPlacement(0, siCenter2, sipmLogical, "physicalSIPM_2", theDetectorLogical, false, 0);
  G4VPhysicalVolume *sipmPhysical3 = new G4PVPlacement(0, siCenter3, sipmLogical, "physicalSIPM_3", theDetectorLogical, false, 0);
  G4VPhysicalVolume *sipmPhysical4 = new G4PVPlacement(0, siCenter4, sipmLogical, "physicalSIPM_4", theDetectorLogical, false, 0);
  G4VPhysicalVolume *sipmPhysical5 = new G4PVPlacement(0, siCenter5, sipmLogical, "physicalSIPM_5", theDetectorLogical, false, 0);
  sipmPhysical0->CheckOverlaps(1000, 0, true);
  sipmPhysical1->CheckOverlaps(1000, 0, true);
  sipmPhysical2->CheckOverlaps(1000, 0, true);
  sipmPhysical3->CheckOverlaps(1000, 0, true);
  sipmPhysical4->CheckOverlaps(1000, 0, true);
  sipmPhysical5->CheckOverlaps(1000, 0, true);
  // quartz over center 2 sipms
  G4ThreeVector quartzPos(0, 2 * sidimY, siZcenter);
  G4VPhysicalVolume *sipmQuartzPhysical = new G4PVPlacement(0, quartzPos, sipmQuartzLogical, "sipmQuartzPhysicsical", theDetectorLogical, false, 0);
  sipmQuartzPhysical->CheckOverlaps(1000, 0, true);

  // backing
  G4ThreeVector sipmBackPos(0, -2. * sidimY, siZcenter);
  G4VPhysicalVolume *sipmBackPhysical = new G4PVPlacement(0, sipmBackPos, sipmBackLogical, "sipmBackPhysicsical", theDetectorLogical, false, 0);
  sipmBackPhysical->CheckOverlaps(1000, 0, true);

  //pmt housing to block photons from being "detected" from the side
  const G4int N = 4;
  G4double Z[N] = {-pmtHeight / 2., pmtHeight / 2. - pmtThickness, pmtHeight / 2. - pmtThickness, pmtHeight / 2.};
  G4double Rmin[N] = {0, 0, pmtRadius, pmtRadius};
  G4double Rmax[N] = {pmtRadius + pmtHousingThickness, pmtRadius + pmtHousingThickness, pmtRadius + pmtHousingThickness, pmtRadius + pmtHousingThickness};
  //G4Tubs* pmtHousingSolid = new G4Tubs("pmtHousingSolid",pmtRadius,pmtRadius+pmtHousingThickness,pmtHeight/2.,0,2*pi);
  G4Polycone *pmtHousingSolid = new G4Polycone("", 0, 2 * pi, N, Z, Rmin, Rmax);
  G4LogicalVolume *pmtHousingLogical = new G4LogicalVolume(pmtHousingSolid, steel, "pmtHousingLogical");
  G4VisAttributes *pmtHousingVisAtt = new G4VisAttributes(G4Color(.4, .6, .8));
  pmtHousingLogical->SetVisAttributes(pmtHousingVisAtt);

  //G4VPhysicalVolume* pmtHousingPhysical0 = new G4PVPlacement(0,G4ThreeVector(0, 0,-(fCryoHeight/2.)+pmtHeight),pmtHousingLogical,"physicalHousingPMT_0",theDetectorLogical,false,0);

  G4VPhysicalVolume *pmtHousingPhysical0 = new G4PVPlacement(0, G4ThreeVector(0, (1. / 2.) * fCryoID / 2, -(fCryoHeight / 2.) + pmtPlacing + pmtSpacing), pmtHousingLogical, "physicalHousingPMT_0", theDetectorLogical, false, 0);
  G4VPhysicalVolume *pmtHousingPhysical1 = new G4PVPlacement(0, G4ThreeVector(0, -(1. / 2.) * fCryoID / 2, -(fCryoHeight / 2.) + pmtPlacing + pmtSpacing), pmtHousingLogical, "physicalHousingPMT_1", theDetectorLogical, false, 0);

  //Place TPB disks
  G4double wlsThickness = 2.0 * um; //1*um;
  G4double wlsRadius = pmtRadius;   //2*inch;
  G4double acrylicThickness = 1 / 8. * inch;

  //place acrylic disk
  G4Tubs *acrylicSolid = new G4Tubs("acrylicSolid", 0, wlsRadius, acrylicThickness / 2., 0, 2 * pi);
  G4LogicalVolume *acrylicLogical = new G4LogicalVolume(acrylicSolid, G4Material::GetMaterial("Acrylic"), "acrylicLogical");
  G4VisAttributes *acrylicVisAtt = new G4VisAttributes(G4Colour(1.0, 1., 0.0));
  acrylicLogical->SetVisAttributes(acrylicVisAtt);
  G4VPhysicalVolume *acrylicPhysical0 = new G4PVPlacement(0, G4ThreeVector(0, (1. / 2.) * fCryoID / 2, -(fCryoHeight / 2.) + pmtHeight / 2 + pmtPlacing + acrylicThickness / 2 + pmtSpacing),
                                                          acrylicLogical, "physicalAcrylic_0", theDetectorLogical, false, 0);
  G4VPhysicalVolume *acrylicPhysical1 = new G4PVPlacement(0, G4ThreeVector(0, -(1. / 2.) * fCryoID / 2, -(fCryoHeight / 2.) + pmtHeight / 2 + pmtPlacing + acrylicThickness / 2 + pmtSpacing),
                                                          acrylicLogical, "physicalAcrylic_1", theDetectorLogical, false, 0);

  G4Tubs *wlsSolid = new G4Tubs("wlsSolid", 0, wlsRadius, wlsThickness / 2., 0, 2 * pi);
  G4LogicalVolume *wlsLogical = new G4LogicalVolume(wlsSolid, G4Material::GetMaterial("TPB"), "wlsLogical");
  G4VisAttributes *wlsVisAtt = new G4VisAttributes(G4Colour(0.0, 1., 0.0));
  wlsVisAtt->SetForceSolid(true);
  wlsLogical->SetVisAttributes(wlsVisAtt);

  G4VPhysicalVolume *wlsPhysical0 = new G4PVPlacement(0, G4ThreeVector(0, (1. / 2.) * fCryoID / 2, -(fCryoHeight / 2.) + pmtHeight / 2 + pmtPlacing + acrylicThickness + wlsThickness / 2 + pmtSpacing), wlsLogical, "physicalWLS_0", theDetectorLogical, false, 0);
  G4VPhysicalVolume *wlsPhysical1 = new G4PVPlacement(0, G4ThreeVector(0, -(1. / 2.) * fCryoID / 2, -(fCryoHeight / 2.) + pmtHeight / 2 + pmtPlacing + acrylicThickness + wlsThickness / 2 + pmtSpacing), wlsLogical, "physicalWLS_1", theDetectorLogical, false, 0);

  G4cout << "WLS_0 Surface is at (" << 0 << "," << (1. / 2.) * fCryoID / 2 << "," << -(fCryoHeight / 2.) + pmtHeight / 2 + pmtPlacing + acrylicThickness + wlsThickness / 2 + pmtSpacing + wlsThickness / 2. << ")" << G4endl;
  G4cout << "WLS_0 Center is at (" << 0 << "," << (1. / 2.) * fCryoID / 2 << "," << -(fCryoHeight / 2.) + pmtHeight / 2 + pmtPlacing + acrylicThickness + wlsThickness / 2 + pmtSpacing << ")" << G4endl;
  G4cout << "PMT_1 surface is at (" << 0 << "," << -(1. / 2.) * fCryoID / 2 << "," << -(fCryoHeight / 2.) + pmtHeight / 2 + pmtPlacing + acrylicThickness + wlsThickness / 2 + pmtSpacing - wlsThickness / 2. << ")" << G4endl;

  pmtPhysical0->CheckOverlaps(1000, 0, true);
  pmtPhysical1->CheckOverlaps(1000, 0, true);

  pmtHousingPhysical0->CheckOverlaps(1000, 0, true);
  pmtHousingPhysical1->CheckOverlaps(1000, 0, true);

  wlsPhysical0->CheckOverlaps(1000, 0, true);
  wlsPhysical1->CheckOverlaps(1000, 0, true);

  acrylicPhysical0->CheckOverlaps(1000, 0, true);
  acrylicPhysical1->CheckOverlaps(1000, 0, true);
  //
  airSpacePhys->CheckOverlaps(1000, 0, true);

  cryostatPhysical->CheckOverlaps(1000, 0, true);
  argonGasPhysical->CheckOverlaps(1000, 0, true);
  wellPhysical->CheckOverlaps(1000, 0, true);
  canPhysical->CheckOverlaps(1000, 0, true);
  vacuumPhysical->CheckOverlaps(1000, 0, true);
  vacWellPhysical->CheckOverlaps(1000, 0, true);
  physicalScintPanel1->CheckOverlaps(1000, 0, true);
  physicalScintPanel2->CheckOverlaps(1000, 0, true);

  //PMT glass:QE taken from PMT_r11065 data sheet
  const G4int num_entries = 22;
  G4double PMTGlassEnergy[num_entries] = {
      LambdaE / (100 * nanometer), LambdaE / (160.8 * nanometer), LambdaE / (170 * nanometer), LambdaE / (182.3 * nanometer), LambdaE / (200 * nanometer),
      LambdaE / (230 * nanometer), LambdaE / (250 * nanometer), LambdaE / (270 * nanometer), LambdaE / (300 * nanometer), LambdaE / (320 * nanometer),
      LambdaE / (340 * nanometer), LambdaE / (360 * nanometer), LambdaE / (380 * nanometer), LambdaE / (400 * nanometer), LambdaE / (450 * nanometer),
      LambdaE / (500 * nanometer), LambdaE / (550 * nanometer), LambdaE / (580 * nanometer), LambdaE / (600 * nanometer), LambdaE / (630 * nanometer),
      LambdaE / (660 * nanometer), LambdaE / (680 * nanometer)};
  G4double PMTGlassReflectivity[num_entries];
  /*
          = {0.0,0.0,0.0,0.0,0.0,
						0.0,0.0,0.0,0.0,0.0,
						0.0,0.0,0.0,0.0,0.0,
						0.0,0.0,0.0,0.0};
  */
  ///*
  //arXiv:1108.5584v2 [physics.ins-det] 26 Sep 2011
  //Demonstration and Comparison of Operation of
  //Photomultiplier Tubes at Liquid Argon Temperature...R. Acciarria et. al.
  G4double PMTGlassEfficiency[num_entries] = {0.0000, 0.0034, 0.0322, 0.0741, 0.1836,
                                              0.1910, 0.2189, 0.2429, 0.3135, 0.3413,
                                              0.3543, 0.3599, 0.3673, 0.3673, 0.308,
                                              0.2172, 0.1097, 0.0708, 0.0523, 0.0301,
                                              0.0153, 9.7172e-3};
  //array should be sorted from low energy to high
  for (int ij = 0; ij < num_entries; ij++)
  {
    PMTGlassEnergy[ij] = PMTGlassEnergy[(num_entries - 1) - ij];
    PMTGlassEfficiency[ij] = PMTGlassEfficiency[(num_entries - 1) - ij];
    //PMTGlassEfficiency[ij] = 1;//PMTGlassEfficiency[(num_entries - 1)-ij];
    PMTGlassReflectivity[ij] = 0;
  }
  //*/
  G4MaterialPropertiesTable *PMTGlassOptTable = new G4MaterialPropertiesTable();
  PMTGlassOptTable->AddProperty("REFLECTIVITY", PMTGlassEnergy, PMTGlassReflectivity, num_entries);
  PMTGlassOptTable->AddProperty("EFFICIENCY", PMTGlassEnergy, PMTGlassEfficiency, num_entries);
  G4OpticalSurface *PMTGlassOptSurface = new G4OpticalSurface("LArInstrPMTGlassSurface", glisur, ground, dielectric_metal);
  PMTGlassOptSurface->SetMaterialPropertiesTable(PMTGlassOptTable);

  G4MaterialPropertiesTable *PMTHousingOptTable = new G4MaterialPropertiesTable();
  PMTHousingOptTable->AddProperty("REFLECTIVITY", PMTGlassEnergy, PMTGlassReflectivity, num_entries);
  //0% EFFICIENCY so that no photons make it through the housing into the PMT glass
  PMTHousingOptTable->AddProperty("EFFICIENCY", PMTGlassEnergy, PMTGlassReflectivity, num_entries);
  G4OpticalSurface *PMTHousingOptSurface = new G4OpticalSurface("PMTHousingSurface", glisur, ground, dielectric_metal, 0.5);
  PMTHousingOptSurface->SetMaterialPropertiesTable(PMTHousingOptTable);

  G4OpticalSurface *WLSoptSurf = new G4OpticalSurface("WLS_rough_surf", glisur, ground, dielectric_dielectric, 0.1);
  G4OpticalSurface *GArLArOptSurf = new G4OpticalSurface("GArLAr_rough_surf", unified, groundfrontpainted, dielectric_dielectric, 0.5);

  G4OpticalSurface *SSOptSurface = new G4OpticalSurface("SS surface");
  SSOptSurface->SetType(dielectric_dielectric);
  SSOptSurface->SetFinish(ground);
  SSOptSurface->SetPolish(0.5);

  //Boundary between tpb and pmtWindow
  new G4LogicalBorderSurface("Acrylic_PMT_0", acrylicPhysical0, pmtPhysical0, PMTGlassOptSurface);
  new G4LogicalBorderSurface("Acrylic_PMT_1", acrylicPhysical1, pmtPhysical1, PMTGlassOptSurface);

  new G4LogicalBorderSurface("WLS_Acrylic_0", wlsPhysical0, acrylicPhysical0, WLSoptSurf);
  new G4LogicalBorderSurface("Acrylic_WLS_0", acrylicPhysical0, wlsPhysical0, WLSoptSurf);

  new G4LogicalBorderSurface("Acrylic_WLS_1", acrylicPhysical1, wlsPhysical1, WLSoptSurf);
  new G4LogicalBorderSurface("WLS_Acrylic_1", wlsPhysical1, acrylicPhysical1, WLSoptSurf);

  new G4LogicalBorderSurface("Argon_acrylic_0", theDetectorPhysical, acrylicPhysical0, WLSoptSurf);
  new G4LogicalBorderSurface("acrylic_Argon_0", acrylicPhysical0, theDetectorPhysical, WLSoptSurf);

  new G4LogicalBorderSurface("Argon_acrylic_1", theDetectorPhysical, acrylicPhysical1, WLSoptSurf);
  new G4LogicalBorderSurface("acrylic_Argon_1", acrylicPhysical1, theDetectorPhysical, WLSoptSurf);

  new G4LogicalBorderSurface("Housing_PMT_0", pmtHousingPhysical0, pmtPhysical0, PMTHousingOptSurface);
  new G4LogicalBorderSurface("Housing_PMT_1", pmtHousingPhysical1, pmtPhysical1, PMTHousingOptSurface);

  new G4LogicalBorderSurface("Argon_Housing_0", theDetectorPhysical, pmtHousingPhysical0, PMTHousingOptSurface);
  new G4LogicalBorderSurface("Argon_Housing_1", theDetectorPhysical, pmtHousingPhysical1, PMTHousingOptSurface);

  new G4LogicalBorderSurface("Argon_TPB_0", theDetectorPhysical, wlsPhysical0, WLSoptSurf);
  new G4LogicalBorderSurface("TPB_Argon_0", wlsPhysical0, theDetectorPhysical, WLSoptSurf);

  new G4LogicalBorderSurface("Argon_TPB_1", theDetectorPhysical, wlsPhysical1, WLSoptSurf);
  new G4LogicalBorderSurface("TPB_Argon_1", wlsPhysical1, theDetectorPhysical, WLSoptSurf);

  new G4LogicalBorderSurface("Argon_GAr", theDetectorPhysical, argonGasPhysical, GArLArOptSurf);
  new G4LogicalBorderSurface("GAr_Argon", argonGasPhysical, theDetectorPhysical, GArLArOptSurf);

  new G4LogicalBorderSurface("Cryo_Argon", cryostatPhysical, theDetectorPhysical, SSOptSurface);
  new G4LogicalBorderSurface("Argon_Cryo", theDetectorPhysical, cryostatPhysical, SSOptSurface);

  new G4LogicalBorderSurface("Cryo_GasArgon", cryostatPhysical, argonGasPhysical, SSOptSurface);
  new G4LogicalBorderSurface("GasArgon_Cryo", argonGasPhysical, cryostatPhysical, SSOptSurface);

  new G4LogicalBorderSurface("Well_Argon", wellPhysical, theDetectorPhysical, SSOptSurface);
  new G4LogicalBorderSurface("Argon_Well", theDetectorPhysical, wellPhysical, SSOptSurface);

  new G4LogicalBorderSurface("Well_GasArgon", wellPhysical, argonGasPhysical, SSOptSurface);
  new G4LogicalBorderSurface("GasArgon_Well", argonGasPhysical, wellPhysical, SSOptSurface);
}

int BACON_Baseline::GetSensitiveVolumeID(const string &volName)
{
  int sensVolID = 0;

  G4PhysicalVolumeStore *storePtr = G4PhysicalVolumeStore::GetInstance();
  G4VPhysicalVolume *pVol = storePtr->GetVolume(volName, false);
  G4String material = pVol->GetLogicalVolume()->GetMaterial()->GetName();

  ///*
  if (volName.find("physicalPMT_0") != string::npos)
  {
    sensVolID = 100;
  }
  else if (volName.find("physicalPMT_1") != string::npos)
  {
    sensVolID = 101;
  }
  else if (volName.find("physicalSIPM_0") != string::npos)
  {
    sensVolID = 200;
  }
  else if (volName.find("physicalSIPM_1") != string::npos)
  {
    sensVolID = 201;
  }
  else if (volName.find("physicalSIPM_2") != string::npos)
  {
    sensVolID = 202;
  }
  else if (volName.find("physicalSIPM_3") != string::npos)
  {
    sensVolID = 203;
  }
  else if (volName.find("physicalSIPM_4") != string::npos)
  {
    sensVolID = 204;
  }
  else if (volName.find("physicalSIPM_5") != string::npos)
  {
    sensVolID = 205;
  }

  //*/
  /*
  if( volName == "Detector"){
    sensVolID = 10000;
  }
  */

  return sensVolID;
}
