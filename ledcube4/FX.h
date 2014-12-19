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
  
  void (*effect)(int options);

  void loop();
  void clap();
  void visual();
  void run(void (*func)(int options), int options = 0, int count = 1);
  void rotate(void (*func)(int options), int options);
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

}
