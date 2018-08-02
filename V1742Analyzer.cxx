// V1742Analyzer.cxx

#include "V1742Analyzer.h"

// -----------------------------------------------------------------------------
// V1742Channel
// -----------------------------------------------------------------------------
novatb::V1742Channel::V1742Channel(unsigned int channel, std::string name) {
  fName = name;
  fChannel = channel;
}

// -----------------------------------------------------------------------------
void novatb::V1742Channel::AddSample(uint16_t adc) {
  fWaveform.push_back(adc);
}

// -----------------------------------------------------------------------------
void novatb::V1742Channel::AddWaveform(std::vector<uint16_t> waveform) {
  fWaveform = waveform;
}

// -----------------------------------------------------------------------------
std::string novatb::V1742Channel::GetName() {
  return fName;
}

// -----------------------------------------------------------------------------
unsigned int novatb::V1742Channel::GetChannel() {
  return fChannel;
}

// -----------------------------------------------------------------------------
unsigned int novatb::V1742Channel::GetNSamples() {
  return fWaveform.size();
}

// -----------------------------------------------------------------------------
uint16_t novatb::V1742Channel::GetSample(unsigned int sample) {
  return fWaveform.at(sample);
}

// -----------------------------------------------------------------------------
std::vector<uint16_t> novatb::V1742Channel::GetWaveform() {
  return fWaveform;
}

// -----------------------------------------------------------------------------
// V1742Event
// -----------------------------------------------------------------------------
novatb::V1742Event::V1742Event(unsigned int eventNumber) {
  fEventNumber = eventNumber;
}

// -----------------------------------------------------------------------------
void novatb::V1742Event::AddChannel(V1742Channel* channel) {
  fChannels.push_back(channel);
}

// -----------------------------------------------------------------------------
novatb::V1742Channel* novatb::V1742Event::GetChannel(unsigned int channel) {
  if (channel > this->GetNChannels()) {
    std::cout << "Error: requested channel " << channel
	      << " is greater than total number of channels ("
	      << this->GetNChannels() << ")" << std::endl;
    return nullptr;
  }
  return fChannels[channel];
}

// -----------------------------------------------------------------------------
std::vector<novatb::V1742Channel*> novatb::V1742Event::GetChannels() {
  return fChannels;
}

// -----------------------------------------------------------------------------
unsigned int novatb::V1742Event::GetNChannels() {
  return fChannels.size();
}

// -----------------------------------------------------------------------------
unsigned int novatb::V1742Event::EventNumber() {
  return fEventNumber;
}

// -----------------------------------------------------------------------------
// V1742Analzer
// -----------------------------------------------------------------------------
novatb::V1742Analyzer::V1742Analyzer() {
}

// -----------------------------------------------------------------------------
novatb::V1742Analyzer::~V1742Analyzer() {
  for (unsigned int event = 0; event < fWaveforms.size(); ++event)
    for (unsigned int channel = 0; channel < fWaveforms[event].size(); ++channel)
      delete fWaveforms[event][channel];
}

// -----------------------------------------------------------------------------
void novatb::V1742Analyzer::AddEvent(V1742Event* event) {
  fEvents.push_back(event);
}

// -----------------------------------------------------------------------------
void novatb::V1742Analyzer::Analyze() {

  // Look over all events
  for (std::vector<V1742Event*>::const_iterator eventIt = fEvents.begin(); eventIt != fEvents.end(); ++eventIt) {

    unsigned int eventNumber = (*eventIt)->EventNumber();

    // Get the channels for the event
    const std::vector<V1742Channel*> v1742Channels = (*eventIt)->GetChannels();
    std::cout << "Event " << eventNumber << " has " << v1742Channels.size() << " channels." << std::endl;

    // Get the waveforms for each channel
    for (std::vector<V1742Channel*>::const_iterator v1742Channel = v1742Channels.begin(); v1742Channel != v1742Channels.end(); ++v1742Channel) {

      unsigned int channelNumber = (*v1742Channel)->GetChannel();
      std::string channelName = (*v1742Channel)->GetName();
      unsigned int nSamples = (*v1742Channel)->GetNSamples();
      std::cout << " Channel " << channelNumber << " has " << nSamples << " samples" << std::endl;

      // Make a histogram to represent a waveform on this channel
      TH1F* hist = new TH1F(Form("Event%dChannel%d", eventNumber, channelNumber), ";Time;ADC;", nSamples, 0, nSamples);

      // Fill the histogram by looping over all samples
      for (unsigned int sample = 0; sample < nSamples; ++sample)
	hist->Fill(sample, (*v1742Channel)->GetSample(sample));

      // Save the histogram in the event map
      fWaveforms[eventNumber][channelNumber] = hist;

    } // channel

  } // event

  return;

}

// -----------------------------------------------------------------------------
void novatb::V1742Analyzer::Write(std::string outFileName) {

  TFile* outFile = new TFile(outFileName.c_str(), "RECREATE");
  TCanvas* canv = new TCanvas("canv","",800,600);
  TLegend* leg = new TLegend(0.75,0.55,0.88,0.88);

  for (unsigned int event = 0; event < fWaveforms.size(); ++event) {
    TString subdir = Form("Event%d", event);
    canv->Clear();
    leg->Clear();
    outFile->cd();
    outFile->mkdir(subdir);
    for (unsigned int channel = 0; channel < fWaveforms[event].size(); ++channel) {
      canv->cd();
      TH1* hist = fWaveforms[event][channel];
      hist->GetYaxis()->SetRangeUser(0,5000);
      hist->SetLineColor(channel+1);
      hist->SetLineWidth(2);
      hist->Draw("hist same");
      leg->AddEntry(hist, fEvents[event]->GetChannel(channel)->GetName().c_str(), "l");
      outFile->cd(subdir);
      hist->Write(Form("Channel%d", channel));
    }
    canv->cd();
    leg->Draw();
    outFile->cd(subdir);
    canv->Write(Form("Event%dAllChannels", event));
  }

  outFile->Close();
  delete outFile;

}
