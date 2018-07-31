// V1742Analyzer.cxx

#include "V1742Analyzer.h"

V1742Analyzer::V1742Analyzer() {
}

void V1742Analyzer::AddChannels(std::map<std::string, V1742Channel*> channels) {
  fChannels = channels;
}

void V1742Analyzer::Analyze() {

  for (std::map<std::string, V1742Channel*>::const_iterator chanIt = fChannels.begin(); chanIt != fChannels.end(); ++chanIt) {
    std::cout << "Channel " << chanIt->second->GetName() << ":" << std::endl;
    for (int sample = 0; sample < chanIt->second->GetNSamples(); ++sample)
      std::cout << "  Sample " << sample << ": " << chanIt->second->GetSample(sample) << std::endl;
  }

  return;

}
