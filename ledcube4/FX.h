namespace FX {

  //effect options
#define NONE      0b0
#define NOCLEAR   0b1
#define ROTATE    0b10
#define MIRROR    0b100
#define UPPER     0b1000
#define LOWER     0b10000
#define LAYER     0b100000
#define COLUMN    0b1000000

#define EFFECT_NUMBER 10

  //number of -1's controls snake length
  char snakeLeds[] = {
    -1, -1, -1, -1   
  };
  //percentage of sudden snake direction change
  char changeProbability = 40;

  //image shown by image effect
  char img[] = { 
    1,1,1,1,1,1,1,0,1,1,0,0,1,0,0,0            
  };

  typedef void (*effect_func)(int options);
  effect_func effect;

  struct effect_info {
    effect_func func;
    String name;
    int options;
    int count;
  };

  void loop();
  void clap();
  void visual();
  void run(effect_func func, int options = 0, int count = 1);
  void rotate(effect_func func, int options);
  void blend(int options);
  void fill(int options);
  void scanner(int options);
  void randomize(int options);
  void extend_from_corner(int options);
  void snake(int options);
  void up_down(int options);
  void image(int options);
  void fan(int options);
  void visualize(int options);

  struct effect_info effects[EFFECT_NUMBER] = {
    { .func = blend,              .name = "blend",              .options = MIRROR,                  .count = 1 },
    { .func = fill,               .name = "fill",               .options = MIRROR | ROTATE,         .count = 1 },
    { .func = scanner,            .name = "scanner",            .options = MIRROR | ROTATE,         .count = 1 },
    { .func = randomize,          .name = "randomize",          .options = NONE,                    .count = 400 },
    { .func = extend_from_corner, .name = "extend_from_corner", .options = UPPER | MIRROR | ROTATE, .count = 1 },
    { .func = snake,              .name = "snake",              .options = NONE,                    .count = 30 },
    { .func = up_down,            .name = "up_down",            .options = NONE,                    .count = 20 },
    { .func = image,              .name = "image",              .options = MIRROR | ROTATE | LAYER, .count = 1 },
    { .func = fan,                .name = "fan",                .options = NONE,                    .count = 10 },
    { .func = visualize,          .name = "visualize",          .options = COLUMN,                  .count = 1 }
  };

  struct effect_info* to_effect(String cmd);
}
