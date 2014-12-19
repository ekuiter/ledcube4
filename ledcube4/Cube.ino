namespace Cube {

  void init() {
    shifting = false;
    for (int i = 0; i < layers; i++)
      pinMode(layerPins[i], OUTPUT);
    for (int i = 0; i < columns; i++)
      pinMode(columnPins[i], OUTPUT);
    init_common();
  }

  void init_shifting(int data, int shift, int storage) {
    shifting = true;
    dataPin    = data;
    shiftPin   = shift;
    storagePin = storage;
    pinMode(dataPin,    OUTPUT);
    pinMode(shiftPin,   OUTPUT);
    pinMode(storagePin, OUTPUT);
    init_common();
  }

  void init_common() {
    randomSeed(analogRead(0));
    clear();
    display(1);
  }

  void display(int duration) {
    switchMode();
    if (modeChanged) return;
    if (mode == CLAP) {
      Audio::read();
      if (Audio::clapped)
        return;
    }
    unsigned long time = millis() + duration;
    if (shifting) {
      while (millis() < time) {
        for (int i = 0; i < layers; i++) {
          long data = 0;
          bitSet(data, i);
          for (int j = 0; j < columns; j++) {
            if (leds[i][j])
              bitSet(data, pov[j] + layers);
          }
          shift(data);
        }
      }
    } 
    else {
      while (millis() < time) {
        for (int i = 0; i < layers; i++) {
          for (int j = 0; j < layers; j++)
            digitalWrite(layerPins[j], LOW);
          for (int j = 0; j < columns; j++)
            digitalWrite(columnPins[j], LOW);
          digitalWrite(layerPins[i], HIGH);
          for (int j = 0; j < columns; j++) {
            if (leds[i][j])
              digitalWrite(columnPins[pov[j]], HIGH);
          }
        }
      }
    }
  }

  void shift(long data) {
    digitalWrite(storagePin, LOW);
    shiftOut(dataPin, shiftPin, MSBFIRST, (data >> 16) & 0xFF);
    shiftOut(dataPin, shiftPin, MSBFIRST, (data >> 8 ) & 0xFF);
    shiftOut(dataPin, shiftPin, MSBFIRST,  data        & 0xFF);
    digitalWrite(storagePin, HIGH);
  }

  void point_of_view(int view) {
    if (view == 1)
      pov = columns1;
    if (view == 2)
      pov = columns2;
    if (view == 3)
      pov = columns3;
    if (view == 4)
      pov = columns4;
  }

  void clear() {
    memset(leds, 0, sizeof(leds[0][0]) * layers * columns);
  }

  char is_on(int layer, int column) {
    return leds[layer][column];
  }

  char is_on(int number) {
    return is_on(number / columns, number % columns);
  }

  void on(int layer, int column) {
    leds[layer][column] = 1;
  }

  void on(int number) {
    on(number / columns, number % columns);
  }

  void off(int layer, int column) {
    leds[layer][column] = 0;
  }

  void off(int number) {
    off(number / columns, number % columns);
  }

  void column_on(int column) {
    for (int i = 0; i < layers; i++)
      leds[i][column] = 1;
  }

  void column_off(int column) {
    for (int i = 0; i < layers; i++)
      leds[i][column] = 0;
  }

  void column_image(int columnGrid, char* img) {
    int offset = columnGrid * layers;
    for (int i = 0; i < layers; i++) {
      for (int j = 0; j < layers; j++)
        leds[i][j + offset] = img[i * layers + j];
    }
  }

  void column_move(char direction) {
    char temp[layers][columns];
    int new_column;
    for (int i = 0; i < layers; i++) {
      for (int j = 0; j < columns; j++) {
        if (direction == FRONT)
          new_column = j >= (columns - layers) ? j - (columns - layers) : j + layers;
        else if (direction == BACK)
          new_column = j < layers ? columns - layers + j : j - layers;
        else
          return;
        temp[i][new_column] = leds[i][j];
      }
    }
    for (int i = 0; i < layers; i++) {
      for (int j = 0; j < columns; j++)
        leds[i][j] = temp[i][j];
    }
  }

  void layer_on(int layer) {
    memset(leds[layer], 1, sizeof(leds[layer]));
  }

  void layer_off(int layer) {
    memset(leds[layer], 0, sizeof(leds[layer]));
  }

  void layer_image(int layer, char* img) {
    for (int i = 0; i < columns; i++)
      leds[layer][i] = img[i];
  }

  void layer_move(char direction) {
    char temp[layers][columns];
    int new_layer;
    for (int i = 0; i < layers; i++) {
      if (direction == UP)
        new_layer = i == layers - 1 ? 0 : i + 1;
      else if (direction == DOWN)
        new_layer = i == 0 ? layers - 1 : i - 1;
      else
        return;
      for (int j = 0; j < columns; j++)
        temp[new_layer][j] = leds[i][j];
    }
    for (int i = 0; i < layers; i++) {
      for (int j = 0; j < columns; j++)
        leds[i][j] = temp[i][j];
    }
  }

  char* directions(int number) {
    return directions(number / columns, number % columns);
  }

  char* directions(int layer, int column) {
    dirs[DOWN] = dirs[UP] = dirs[LEFT] = dirs[RIGHT] = dirs[BACK] = dirs[FRONT] = -1;
    if (layer > 0)
      dirs[DOWN] = columns * (layer - 1) + column;
    if (layer < 3)
      dirs[UP] = columns * (layer + 1) + column;
    if ((column % layers) != 0)
      dirs[LEFT] = columns * layer + column - 1;
    if (((column + 1) % layers) != 0)
      dirs[RIGHT] = columns * layer + column + 1;
    if (column >= layers)
      dirs[BACK] = columns * layer + column - layers;
    if (column < (columns - layers))
      dirs[FRONT] = columns * layer + column + layers;
    return dirs;
  }

  char neighbour(int number, char direction) {
    return neighbour(number / columns, number % columns, direction);
  }

  char neighbour(int layer, int column, char direction) {
    char* dir = directions(layer, column);
    if (direction == -1 && lastDirection != -1)
      direction = lastDirection;
    while (direction == -1 || dir[direction] == -1) {
      direction = random(6);
      if (dir[direction] == -1)
        direction = -1;
    }
    if (is_on(dir[direction]))
      return neighbour(layer, column, -1);
    lastDirection = direction;
    return dir[direction];
  }

}
