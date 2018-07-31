// V1742Analzer.h

#include <map>
#include <string>

class V1742Channel {

 public:

  V1742Channel(std::string name);

  std::string GetName() { return fName; }
  void AddSample(double adc);
  int GetNSamples() { return fADCs.size(); }
  double GetSample(int sample) { return fADCs.at(sample); }

 private:

  std::string fName;
  std::vector<double> fADCs;

};

V1742Channel::V1742Channel(std::string name) {
  fName = name;
}

void V1742Channel::AddSample(double adc) {
  fADCs.push_back(adc);
}

class V1742Analyzer {

 public:

  V1742Analyzer();
  void AddChannels(std::map<std::string, V1742Channel*> channels);
  void Analyze();

 private:

  std::map<std::string, V1742Channel*> fChannels;

};


