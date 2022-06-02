#ifndef header_H
#define header_H

#include <TF1.h>
#include <TCut.h>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <iostream>
#include <TLine.h>
#include <TMath.h>
#include <TTree.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLegend.h>

double br_1P_0to1Sgamma = 0.0194;
double br_1P_1to1Sgamma = 0.352;
double br_1P_2to1Sgamma = 0.18;

double br_2P_0to1Sgamma = 3.8e-05;
double br_2P_1to1Sgamma = 0.099;
double br_2P_2to1Sgamma = 0.066;

double br_2P_0to2Sgamma = 0.0138;
double br_2P_1to2Sgamma = 0.181;
double br_2P_2to2Sgamma = 0.089;

double br_2Sto1S = 17.85 + 8.6 + 2.9e-04;// + 6.9*br_1P_1to1Sgamma + 7.15*br_1P_2to1Sgamma + 3.8*br_1P_0to1Sgamma;
double br_3Sto1S = 4.37 + 2.20;// + 10.6*br_2Sto1S + 13.1*(br_2P_2to1Sgamma + br_2P_2to2Sgamma*br_2Sto1S) + 12.6*(br_2P_1to1Sgamma + br_2P_1to2Sgamma*br_2Sto1S) + 5.9*(br_2P_0to1Sgamma + br_2P_0to2Sgamma*br_2Sto1S);
double br_3Sto2S = 10.6;

struct branchingRatioToDimuons { double Y1S, Y2S, Y3S;};
branchingRatioToDimuons brToDM = {2.48, 1.93, 2.18};

struct branchingRatio { double Y2Sto1S, Y3Sto1S, Y3Sto2S;};
branchingRatio br = {br_2Sto1S, br_3Sto1S, br_3Sto2S};

int fExpCMSnS =0;
int fExpLHCbnS =1;
TString fDir[2] = {"Table 6","Table 19"};
TString fHistName[2] = {"Hist1D_y","Hist1D_y"};
TString fn[2] = {"YnS_CMS_7TeV_SR_corr_vs_pT_absy1p2.root","YnS_LHCb_8TeV_SR_corr_vs_pT_y2to4p5.root"};
TString dir = "/home/CMS/DataFiles/QuarkoniaFeedDown/";

double getErrorPropaDivide(double a, double da, double b, double db){
  double err = a/b*TMath::Sqrt((da/a)*(da/a) + (db/b)*(db/b));
  return err;
};

#endif
