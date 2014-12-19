namespace Audio {

  Analyzer::Analyzer(void) {
    _StrobePin = 4;
    _RSTPin = 5;
    _DCPin = 0;
  }

  Analyzer::Analyzer(int StrobePin, int RstPin, int AnalogPin) {
    _StrobePin = StrobePin;
    _RSTPin = RstPin;
    _DCPin = AnalogPin;
  }

  void Analyzer::Init() {
    pinMode(_StrobePin, OUTPUT);
    pinMode(_RSTPin, OUTPUT);
    RstModule();
  }

  void Analyzer::RstModule() {
    digitalWrite(_StrobePin, LOW);
    digitalWrite(_RSTPin, HIGH);
    digitalWrite(_StrobePin, HIGH);
    digitalWrite(_StrobePin, LOW);
    digitalWrite(_RSTPin, LOW);
    delayMicroseconds(72);  
  }

  void Analyzer::ReadFreq(int *value) {
    static boolean RstState = false;
    if (!RstState) {
      _TimepointSt = millis();
      RstState = true;
    }
    else {
      _TimepointNow = millis();
      if (_TimepointNow - _TimepointSt > 3000) {
        RstModule();
        RstState = false;
      }
    }

    for (byte band = 0; band < 7; band++) {
      delayMicroseconds(10);
      value[band] = analogRead(_DCPin);
      delayMicroseconds(50);
      digitalWrite(_StrobePin, HIGH);
      delayMicroseconds(18);
      digitalWrite(_StrobePin, LOW);
    }  
  }

  void init() {
    analyzer.Init();
  }

  void read() {
    static boolean waiting = false;
    if (!waiting) {
      time = millis();
      waiting = true;
    }
    else {
      if (millis() - time > 100) {
        analyzer.ReadFreq(frequencies); //frequencies in Hz: 63,160,400,1K,2.5K,6.25K,16K
        waiting = false;
        average = 0;
        for (int i = 0; i<7; i++)
          average += max((frequencies[i]-100),0);
        average /= 7;
        if (timer > 0)
          timer--;
        if (average > CLAP_THRESHOLD && clapped == false && timer == 0) {
          Cube::clear();
          Cube::display(1);
          clapped = true;
          timer = CLAP_RESONANCE / 100;
        }
      }
    }
  }

}
