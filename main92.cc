// main92.cc is a part of the PYTHIA event generator.
// Copyright (C) 2022 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Keywords: analysis; root;

// This is a simple test program.
// Modified by Rene Brun and Axel Naumann to put the Pythia::event
// into a TTree.

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for saving Pythia events as trees in a file.
#include "TTree.h"
#include "TFile.h"

using namespace Pythia8;

int main() {

  // Create Pythia instance and set it up to generate hard QCD processes
  // above pTHat = 20 GeV for pp collisions at 14 TeV.
  Pythia pythia;
  pythia.readString("Bottomonium:states(3S1) = 553,100553,200553");
  pythia.readString("Bottomonium:O(3S1)[3S1(1)] = 9.28,4.63,3.54");
  pythia.readString("Bottomonium:O(3S1)[3S1(8)] = 0.15,0.045,0.075");
  pythia.readString("Bottomonium:O(3S1)[1S0(8)] = 0.02,0.006,0.01");
  pythia.readString("Bottomonium:O(3S1)[3P0(8)] = 0.02,0.006,0.01");
  pythia.readString("Bottomonium:gg2bbbar(3S1)[3S1(1)]g = on,on,on");
  pythia.readString("Bottomonium:gg2bbbar(3S1)[3S1(8)]g = on,on,on");
  pythia.readString("Bottomonium:qg2bbbar(3S1)[3S1(8)]q = on,on,on");
  pythia.readString("Bottomonium:qqbar2bbbar(3S1)[3S1(8)]g = on,on,on");
  pythia.readString("Bottomonium:gg2bbbar(3S1)[1S0(8)]g = on,on,on");
  pythia.readString("Bottomonium:qg2bbbar(3S1)[1S0(8)]q = on,on,on");
  pythia.readString("Bottomonium:qqbar2bbbar(3S1)[1S0(8)]g = on,on,on");
  pythia.readString("Bottomonium:gg2bbbar(3S1)[3PJ(8)]g    = on,on,on");
  pythia.readString("Bottomonium:qg2bbbar(3S1)[3PJ(8)]q    = on,on,on");
  pythia.readString("Bottomonium:qqbar2bbbar(3S1)[3PJ(8)]g = on,on,on");
  pythia.readString("Bottomonium:gg2bbbar(3S1)[3S1(1)]gm   = on,on,on");
  pythia.readString("553:onMode = off");
  pythia.readString("100553:onMode = on");
  pythia.readString("200553:onMode = on");
  pythia.readString("Bottomonium:states(3PJ) = 20553,555");
  pythia.readString("Bottomonium:O(3PJ)[3P0(1)]  = 0.085,0.085");
  pythia.readString("Bottomonium:O(3PJ)[3S1(8)] = 0.04,0.04");
  pythia.readString("Bottomonium:gg2bbbar(3PJ)[3PJ(1)]g = on,on");
  pythia.readString("Bottomonium:qg2bbbar(3PJ)[3PJ(1)]q = on,on");
  pythia.readString("Bottomonium:qqbar2bbbar(3PJ)[3PJ(1)]g = on,on");
  pythia.readString("Bottomonium:gg2bbbar(3PJ)[3S1(8)]g = on,on");
  pythia.readString("Bottomonium:qg2bbbar(3PJ)[3S1(8)]q = on,on");
  pythia.readString("Bottomonium:qqbar2bbbar(3PJ)[3S1(8)]g = on,on");
  pythia.readString("20553:m0 = 9.89278");
  pythia.readString("555:m0 = 9.91221");
  pythia.readString("20553:onMode = on");
  pythia.readString("555:onMode = on");
  pythia.readString("PhaseSpace:pTHatMin = 2.");
  pythia.readString("Beams:eCM = 8160.");
  //pythia.readString("Beams:eCM = 14000.");
  pythia.init();

  // Set up the ROOT TFile and TTree.
  TFile *file = TFile::Open("Upsilon1S_FeedDownTree.root","recreate");
  Event *event = &pythia.event;
  TTree *T = new TTree("T","ev1 Tree");

  static const int Max_size = 10000;
  int evt;
  int evtSize; 
  long int pdgid[Max_size];
  bool isFinal[Max_size];
  int mother1[Max_size], mother2[Max_size];
  long int mother1id[Max_size], mother2id[Max_size];
  bool decayNormal[Max_size];
  bool decayPrompt[Max_size];
  T->Branch("evt",&evt,"evt/I");
  T->Branch("evtSize",&evtSize,"evtSize/I");
  T->Branch("pdgid",pdgid,"pdgid[evtSize]/L");
  T->Branch("isFinal",isFinal,"isFinal[evtSize]/O");
  T->Branch("mother1",mother1,"mother1[evtSize]/I");
  T->Branch("mother2",mother2,"mother2[evtSize]/I");
  T->Branch("mother1id",mother1id,"mother1[evtSize]/L");
  T->Branch("mother2id",mother2id,"mother2[evtSize]/L");
  T->Branch("decayNormal",decayNormal,"decayNormal[evtSize]/O");
  T->Branch("decayPrompt",decayPrompt,"decayPrompt[evtSize]/O");

  const long long int nEvt = 10000;
 // Begin event loop. Generate event; skip if generation aborted.
  for (int iEvent = 0; iEvent < nEvt; ++iEvent) {
    if (!pythia.next()) continue;
    
    evt=iEvent;
    evtSize = event->size();
    for (int i = 0; i < evtSize; ++i) {
       pdgid[i] = pythia.event[i].id();
       isFinal[i] = pythia.event[i].isFinal();
       mother1[i] = pythia.event[i].mother1();
       mother2[i] = pythia.event[i].mother2();
       mother1id[i] = pythia.event[mother1[i]].id();
       mother2id[i] = pythia.event[mother2[i]].id();
       decayNormal[i] = (mother1[i]>0 && mother2[i]==0) ? true : false;
       decayPrompt[i] = (pythia.event[i].motherList().size()==0) ? true : false;
       if(pdgid[i]==553 && pythia.event[i].motherList().size() ==0) cout << "? " << endl;
    }

/*
      if(pythia.event[i].id() == 553){
        if(pythia.event[i].isFinal() == true){
          std::cout << "size " << pythia.event[i].motherList().size() << std::endl;
          for(int j=0; j<pythia.event[i].motherList().size(); j++){
            cout << " j : " << j << " - " << pythia.event[i].motherList()[j] << ", id = " << pythia.event[pythia.event[i].mother1()].id() << endl;
          }
          std::cout << "i - " << i << ", id = " << pythia.event[i].id() << std::endl;
          std::cout << "and " << i << ", status = " << pythia.event[i].status() << " , isFinal : " << pythia.event[i].isFinal() << std::endl;
        }
      }
    }
    std::cout << std::endl;
*/    // Fill the pythia event into the TTree.
    // Warning: the files will rapidly become large if all events
    // are saved. In some cases it may be convenient to do some
    // processing of events and only save those that appear
    // interesting for future analyses.
    T->Fill();

  // End event loop.
  }

  // Statistics on event generation.
  pythia.stat();

  //  Write tree.
  T->Print();
  T->Write();
  delete file;

  // Done.
  return 0;
}
