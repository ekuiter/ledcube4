namespace Cube {

  //change if needed

#define layers  4
#define columns 16

  //if you don't use shifting ...
  
  int columnPins[] = {/*0,1,2,3,4,5,6,7,8,9,10,11,12,13,18,19*/} // ... put your columns here
  ;
  
  int layerPins[] = {/*20,21,22,23*/} // ... same for layers
  ;

  //do not change

  char shifting;
  int dataPin;
  int shiftPin;
  int storagePin;

  char leds[layers][columns];
  char columns1[] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15                                                    
  };
  char columns2[] = {
    3,7,11,15,2,6,10,14,1,5,9,13,0,4,8,12    
  };
  char columns3[] = {
    15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0   
  };
  char columns4[] = {
    12,8,4,0,13,9,5,1,14,10,6,2,15,11,7,3    
  };
  char* pov = columns1;

  //directions
#define DOWN    0
#define UP      1
#define LEFT    2
#define RIGHT   3
#define BACK    4
#define FRONT   5
  char dirs[6] = {
    -1,-1,-1,-1,-1,-1    
  };
  char lastDirection = -1;

  void init();
  void init_shifting(int data, int shift, int storage);
  void init_common();
  void point_of_view(int view);
  void display(int duration);
  void shift(long data);
  void clear();
  void on(int layer, int column);
  void on(int number);
  char is_on(int layer, int column);
  char is_on(int number);
  void off(int layer, int column);
  void off(int number);
  void column_on(int column);
  void column_off(int column);
  void column_image(int columnGrid, char* img);
  void column_move(char direction);
  void layer_on(int layer);
  void layer_off(int layer);
  void layer_image(int layer, char* img);
  void layer_move(char direction);
  char* directions(int number);
  char* directions(int layer, int column);
  char neighbour(int number, char direction = -1);
  char neighbour(int layer, int column, char direction = -1);

}
