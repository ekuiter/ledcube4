namespace FX {

  void loop() {
    run(blend, MIRROR);
    run(fill, MIRROR | ROTATE);

    run(blend, MIRROR);
    run(scanner, MIRROR | ROTATE);

    run(blend, MIRROR);
    run(randomize, NONE, 400);

    run(blend, MIRROR);
    run(extend_from_corner, UPPER | MIRROR | ROTATE);
    run(extend_from_corner, LOWER | MIRROR | ROTATE);
    run(extend_from_corner, UPPER | MIRROR | ROTATE);
    run(extend_from_corner, LOWER | MIRROR | ROTATE);

    run(blend, MIRROR);
    run(snake, NONE, 30);

    run(blend, MIRROR);
    run(up_down, NONE, 20);

    run(blend, MIRROR);
    run(image, MIRROR | ROTATE | LAYER, 2);
    run(image, MIRROR | ROTATE | COLUMN, 2);

    run(blend, MIRROR);
    run(fan, NONE, 10);
  }

  void clap() {
    run(fill, MIRROR | ROTATE);
    run(scanner, MIRROR | ROTATE);
    run(randomize);
    run(extend_from_corner, UPPER | MIRROR | ROTATE);
    run(extend_from_corner, LOWER | MIRROR | ROTATE);
    run(snake);
    run(up_down);
    run(image, MIRROR | ROTATE | LAYER);
    run(image, MIRROR | ROTATE | COLUMN);
    run(fan);
  }

  void visual() {
    run(visualize, COLUMN);
    //run(visualize, LAYER);
  }

  void run(effect_func func, int options, int count) {
    if (modeChanged) return;
    Audio::clapped = false;
    Cube::point_of_view(1);
    effect = func;
    if (mode == CLAP) {
      if (!(options & NOCLEAR))
        Cube::clear();
      while(!Audio::clapped) {
        if (modeChanged) return;
        if (options & ROTATE)
          rotate(effect, options);
        else
          effect(options);
      }
    } 
    else {
      if (!(options & NOCLEAR))
        Cube::clear();
      for (int runCount = 0; runCount < count; runCount++) {
        if (modeChanged) return;
        if (options & ROTATE)
          rotate(effect, options);
        else
          effect(options);
      }
    }
  }

  void rotate(effect_func func, int options) {
    for (int i = 1; i <= 4; i++) {
      Cube::point_of_view(i);
      Cube::clear();
      func(options);
    }
  }

  void blend(int options) {
    for (int j = 0; j < 64; j++) {
      Cube::clear();
      Cube::on(j);
      Cube::display(5);
    }
    if (options & MIRROR) {
      for (int j = 62; j > 0; j--) {
        Cube::clear();
        Cube::on(j);
        Cube::display(5);
      }
    }
  }

  void fill(int options) {
    for (int j = 0; j < 64; j++) {
      Cube::on(j);
      Cube::display(20);
    }
    if (options & MIRROR) {
      for (int j = 63; j >= 0; j--) {
        Cube::off(j);
        Cube::display(4);
      }
    }
  }

  void scanner(int options) {
    for (int i = 0; i < 16; i++) {
      Cube::clear();
      Cube::column_on(i);
      Cube::layer_on(i / 4);
      Cube::display(50);
    }
    if (options & MIRROR) {
      for (int i = 15; i >= 0; i--) {
        Cube::clear();
        Cube::column_on(i);
        Cube::layer_on(i / 4);
        Cube::display(50);
      }
    }
  }

  void randomize(int options) {
    Cube::on(random(64));
    Cube::on(random(64));
    Cube::off(random(64));
    Cube::off(random(64));
    Cube::off(random(64));
    Cube::display(10);
  }

  void extend_from_corner(int options) {
    int* layer;
    int tempUpper[] = { 3,2,1,0 };
    int tempLower[] = { 0,1,2,3 };
    if (!(options & UPPER) && !(options & LOWER))
      return;
    if (options & UPPER)
      layer = tempUpper;
    if (options & LOWER)
      layer = tempLower;
    Cube::on(layer[0], 0);
    Cube::display(50);
    Cube::on(layer[1], 0);
    Cube::on(layer[1], 1);
    Cube::on(layer[1], 4);
    Cube::on(layer[1], 5);
    Cube::display(50);
    int leds[] = {
      0,1,2,4,5,6,8,9,10        
    };
    for (int i = 0; i < 11; i++)
      Cube::on(layer[2], leds[i]);
    Cube::display(50);
    Cube::layer_on(layer[3]);
    Cube::display(50);
    if (options & MIRROR) {
      Cube::layer_off(layer[3]);
      Cube::display(50);
      int leds[] = {
        0,1,2,4,5,6,8,9,10                                                    
      };
      for (int i = 0; i < 11; i++)
        Cube::off(layer[2], leds[i]);
      Cube::display(50);
      Cube::off(layer[1], 0);
      Cube::off(layer[1], 1);
      Cube::off(layer[1], 4);
      Cube::off(layer[1], 5);
      Cube::display(50);
      Cube::off(layer[0], 0);
      Cube::display(50);
    }
  }

  void snake(int options) {
    int snakeLength = sizeof(snakeLeds) / sizeof(snakeLeds[0]);
    int startLed = random(64);
    for (int i = 0; i < snakeLength; i++) {
      if (snakeLeds[i] != -1)
        Cube::off(snakeLeds[i]);
      int last = i == 0 ? snakeLength - 1 : i - 1;
      int led = snakeLeds[last] == -1 ? startLed : snakeLeds[last];
      char changeDirection = random(100) + 1 < changeProbability ? true : false;
      char direction = changeDirection ? random(6) : -1;
      snakeLeds[i] = Cube::neighbour(led, direction);
      Cube::on(snakeLeds[i]);
      Cube::display(50);
    }
  }

  void up_down(int options) {
    int column1 = random(16);
    int column2 = column1;
    while (column1 == column2)
      column2 = random(16);
    for (int i = 0; i < layers; i++) {
      int j = layers - 1 - i;
      Cube::off(i == 0 ? layers - 1 : i - 1, column1);
      Cube::on(i, column1);
      Cube::off(j == layers - 1 ? 0 : j + 1, column2);
      Cube::on(j, column2);
      Cube::display(50);
    }
    Cube::display(80);
  }

  void image(int options) {
    void (*image_func)(int layer, char* image);
    void (*move_func)(char direction);
    char direction, direction_mirror;
    if (options & LAYER) {
      image_func = Cube::layer_image;
      move_func = Cube::layer_move;
      direction = UP;
      direction_mirror = DOWN;
    } 
    else if (options & COLUMN) {
      image_func = Cube::column_image;
      move_func = Cube::column_move;
      direction = FRONT;
      direction_mirror = BACK;
    } 
    else
      return;
    for (int i = 0; i < 4; i++) {
      i == 0 ? image_func(0, img) : move_func(direction);
      Cube::display(80);
    }
    if (options & MIRROR) {
      for (int i = 0; i < 2; i++) {
        move_func(direction_mirror);
        Cube::display(80);
      }
    }
    move_func(direction_mirror);
  }

  void fan(int options) {
    int fanSpeed = 80;
    Cube::column_on(0);
    Cube::column_on(5);
    Cube::column_on(10);
    Cube::column_on(15);
    Cube::display(fanSpeed);
    Cube::clear();
    Cube::column_on(1);
    Cube::column_on(5);
    Cube::column_on(10);
    Cube::column_on(14);
    Cube::display(fanSpeed);
    Cube::clear();
    Cube::column_on(2);
    Cube::column_on(6);
    Cube::column_on(9);
    Cube::column_on(13);
    Cube::display(fanSpeed);
    Cube::clear();
    Cube::column_on(3);
    Cube::column_on(6);
    Cube::column_on(9);
    Cube::column_on(12);
    Cube::display(fanSpeed);
    Cube::clear();
    Cube::column_on(7);
    Cube::column_on(6);
    Cube::column_on(9);
    Cube::column_on(8);
    Cube::display(fanSpeed);
    Cube::clear();
    Cube::column_on(11);
    Cube::column_on(5);
    Cube::column_on(10);
    Cube::column_on(4);
    Cube::display(fanSpeed);
    Cube::clear();
  }

  void visualize(int options) {
    Audio::read();
    Cube::clear();
    char bands[] = {
      3,4,5,6       
    };
    for (int i = 0; i < 4; i++) {
      int leds = map(Audio::frequencies[bands[i]], 0, 1023, 0, 16);
      if (leds) {
        if (options & LAYER) { 
          for (int j = 0; j < 4; j++) {
            if (leds > 4 * j)
              Cube::on(j, i);            
            if (leds > 4 * j + 1)
              Cube::on(j, 4 + i);
            if (leds > 4 * j + 2)
              Cube::on(j, 8 + i);
            if (leds > 4 * j + 3)
              Cube::on(j, 12 + i);
          }
        } 
        else if (options & COLUMN) {
          for (int j = 0; j < 4; j++) {
            if (leds > j)
              Cube::on(j, i);
            if (leds > 4 + j)
              Cube::on(j, 4 + i);
            if (leds > 8 + j)
              Cube::on(j, 8 + i);
            if (leds > 12 + j)
              Cube::on(j, 12 + i);
          }
        }
      }
    }
    Cube::display(1);
  }

  struct effect_info* to_effect(String cmd) {
    for (int i = 0; i < EFFECT_NUMBER; i++)
      if (effects[i].name == cmd)
	return &effects[i];
    return nullptr;
  }

}
