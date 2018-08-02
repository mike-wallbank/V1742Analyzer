#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "TGraph.h"
#include "TMultiGraph.h"
#include "TSystem.h"

// Load the libraries
#include "V1742Analyzer.h"
#include "V1742Analyzer.cxx"

void V1742AnalyzeText(std::string inputFileName = "") {

  // // Need to load library which defined the analysis classes
  // gInterpreter->AddIncludePath("/home/nfs/wallbank/local_product_installation/lariatonline/v05_04_00/slf7.x86_64.e14.s50.prof/lib/");
  // gInterpreter->AddIncludePath("/home/nfs/wallbank/lariat-online/daq/include/");
  // gSystem->Load("/home/nfs/wallbank/local_product_installation/lariatonline/v05_04_00/slf7.x86_64.e14.s50.prof/lib/libLariatDaq.so");
  // gSystem->Load("/home/nfs/wallbank/local_product_installation/lariatonline/v05_04_00/slf7.x86_64.e14.s50.prof/lib/libdaq_lariat-artdaq_lariat-artdaq_NovaTestBeam_V1742Analysis_module");

  if (inputFileName == "")
    inputFileName = "PlotData.txt";

  std::ifstream inFile(inputFileName);
  std::string fileLine;

  if (!inFile) {
    std::cout << "ERROR: Input file " << inputFileName << " not found." << std::endl;
    return;
  }

  // Make all channel objects
  novatb::V1742Channel* chan0 = new novatb::V1742Channel(0, "Channel 0");
  novatb::V1742Channel* chan1 = new novatb::V1742Channel(1, "Channel 1");
  novatb::V1742Channel* chan2 = new novatb::V1742Channel(2, "Channel 2");
  novatb::V1742Channel* chan3 = new novatb::V1742Channel(3, "Channel 3");
  novatb::V1742Channel* chan4 = new novatb::V1742Channel(4, "Channel 4");
  novatb::V1742Channel* chan5 = new novatb::V1742Channel(5, "Channel 5");
  novatb::V1742Channel* chan6 = new novatb::V1742Channel(6, "Channel 6");
  novatb::V1742Channel* chan7 = new novatb::V1742Channel(7, "Channel 7");
  novatb::V1742Channel* chanTrig = new novatb::V1742Channel(8, "Trigger Channel");

  while (std::getline(inFile, fileLine)) {

    std::stringstream linestream(fileLine);
    int timeSample;
    uint16_t triggerADC, adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7;

    linestream >> timeSample >> triggerADC >> adc0 >> adc1 >> adc2 >> adc3 >> adc4 >> adc5 >> adc6 >> adc7;

    chan0->AddSample(adc0);
    chan1->AddSample(adc1);
    chan2->AddSample(adc2);
    chan3->AddSample(adc3);
    chan4->AddSample(adc4);
    chan5->AddSample(adc5);
    chan6->AddSample(adc6);
    chan7->AddSample(adc7);
    chanTrig->AddSample(triggerADC);

  }

  // Add all channels to an event
  novatb::V1742Event* v1742Event = new novatb::V1742Event(0);
  v1742Event->AddChannel(chan0);
  v1742Event->AddChannel(chan1);
  v1742Event->AddChannel(chan2);
  v1742Event->AddChannel(chan3);
  v1742Event->AddChannel(chan4);
  v1742Event->AddChannel(chan5);
  v1742Event->AddChannel(chan6);
  v1742Event->AddChannel(chan7);
  v1742Event->AddChannel(chanTrig);

  // Make a V1742 analyzer object to do the actual analysis
  novatb::V1742Analyzer* v1742Analyzer = new novatb::V1742Analyzer();
  v1742Analyzer->AddEvent(v1742Event);
  v1742Analyzer->Analyze();
  v1742Analyzer->Write("V1742Analysis_Text.root");

  return;

}
