// V1742Analzer.h

#ifndef V1742ANALYZER_H
#define V1742ANALYZER_H

// stl
#include <iostream>
#include <map>
#include <vector>
#include <string>

// root
#include "TString.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"

namespace novatb {
  class V1742Channel;
  class V1742Event;
  class V1742Analyzer;
}

// -----------------------------------------------------------------------------
class novatb::V1742Channel {

 public:

  V1742Channel(unsigned int channel, std::string name);

  void AddSample(uint16_t adc);
  void AddWaveform(std::vector<uint16_t> waveform);
  unsigned int GetChannel();
  std::string GetName();
  unsigned int GetNSamples();
  uint16_t GetSample(unsigned int sample);
  std::vector<uint16_t> GetWaveform();

 private:

  std::string fName;
  unsigned int fChannel;
  std::vector<uint16_t> fWaveform;

};

// -----------------------------------------------------------------------------
class novatb::V1742Event {

 public:

  V1742Event(unsigned int eventNumber);

  void AddChannel(V1742Channel* channel);
  V1742Channel* GetChannel(unsigned int channelNumber);
  std::vector<V1742Channel*> GetChannels();
  unsigned int GetNChannels();
  unsigned int EventNumber();

 private:

  unsigned int fEventNumber;
  std::vector<V1742Channel*> fChannels;

};

// -----------------------------------------------------------------------------
class novatb::V1742Analyzer {

 public:

  V1742Analyzer();
  ~V1742Analyzer();

  void AddEvent(V1742Event* event);
  void Analyze();
  void Write(std::string outFileName);

 private:

  std::vector<V1742Event*> fEvents;
  std::map<int, std::map<int, TH1F*> > fWaveforms;

};

#endif
