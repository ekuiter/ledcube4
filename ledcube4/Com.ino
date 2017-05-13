namespace Com {
  static String input;
  static bool inputComplete = false;
 
  void init() {
    input.reserve(200);
  }

  bool available() {
    if (inputComplete)
      return true;
    while (Serial.available()) {
      char c = Serial.read();
      if (c == '\n')
	inputComplete = true;
      else
	input += c;
    }
    return inputComplete;
  }

  String read() {
    String ret = input;
    input = "";
    inputComplete = false;
    return ret;
  }
}
