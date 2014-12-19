namespace Audio {

#define CLAP_THRESHOLD 600
#define CLAP_RESONANCE 300

  class Analyzer{
public:
    Analyzer();
    Analyzer(int strobePin, int RstPin, int analogPin);
    void Init();
    void ReadFreq(int*);

private:
    int _DCPin;
    int _StrobePin;
    int _RSTPin;
    void RstModule();
    unsigned long _TimepointSt;
    unsigned long _TimepointNow;
  };

  Analyzer analyzer = Analyzer(analyzerPin1, analyzerPin2, analyzerPin3);
  int frequencies[7];
  unsigned long time;
  int average;
  char clapped;
  int timer;

  void init();
  void read();

}
