#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "TGraph.h"
#include "TMultiGraph.h"

#include "V1742Analyzer.h"

void V1742AnalyzeText(std::string inputFileName = "") {

  if (inputFileName == "")
    inputFileName = "PlotData.txt";

  std::ifstream inFile(inputFileName);
  std::string fileLine;

  std::map<std::string, V1742Channel*> channels;
  channels["TriggerChan"] = new V1742Channel("TriggerChan");
  channels["Channel0"] = new V1742Channel("Channel0");
  channels["Channel1"] = new V1742Channel("Channel1");
  channels["Channel2"] = new V1742Channel("Channel2");
  channels["Channel3"] = new V1742Channel("Channel3");
  channels["Channel4"] = new V1742Channel("Channel4");
  channels["Channel5"] = new V1742Channel("Channel5");
  channels["Channel6"] = new V1742Channel("Channel6");
  channels["Channel7"] = new V1742Channel("Channel7");

  while (std::getline(inFile, fileLine)) {

    std::stringstream linestream(fileLine);
    int timeSample;
    double triggerADC, adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7;

    linestream >> timeSample >> triggerADC >> adc0 >> adc1 >> adc2 >> adc3 >> adc4 >> adc5 >> adc6 >> adc7;

    channels["TriggerChan"]->AddSample(triggerChan);
    channels["Channel0"]->AddSample(chan0);
    channels["Channel1"]->AddSample(chan1);
    channels["Channel2"]->AddSample(chan2);
    channels["Channel3"]->AddSample(chan3);
    channels["Channel4"]->AddSample(chan4);
    channels["Channel5"]->AddSample(chan5);
    channels["Channel6"]->AddSample(chan6);
    channels["Channel7"]->AddSample(chan7);

  }

  V1742Analzer* v1742Analyzer = new V1742Analzer();
  v1742Analzer->AddChannels(channels);
  v1742Analzer->Analyze();

  return;

}
