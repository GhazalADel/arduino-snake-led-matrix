#include <FastLED.h>
#include <EEPROM.h>


#define DATA_PIN 11
#define UP 5
#define RIGHT 4
#define LEFT 3
#define DOWN 2

CRGB board[256];
int snake[128];
int snakeSize = 3;
int foodPoint;
int pushedButton;
int initialHead = 100;

int prevMove = -1;
bool gameDone = false;

//https://forum.arduino.cc/t/the-reliable-but-not-very-sexy-way-to-seed-random/65872
void reseedRandom( void )
{
  static const uint32_t HappyPrime = 937;
  union
  {
    uint32_t i;
    uint8_t b[4];
  }
  raw;
  int8_t i;
  unsigned int seed;
  
  for ( i=0; i < sizeof(raw.b); ++i )
  {
    raw.b[i] = EEPROM.read( i );
  }

  do
  {
    raw.i += HappyPrime;
    seed = raw.i & 0x7FFFFFFF;
  }
  while ( (seed < 1) || (seed > 2147483646) );

  randomSeed( seed );  

  for ( i=0; i < sizeof(raw.b); ++i )
  {
    EEPROM.write( i, raw.b[i] );
  }
}

void setup() {
  Serial.begin(9600);
  reseedRandom();
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(board, 256);
  pinMode(UP, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  initializeGame();
}

void loop() {
  getButtons();
  move();
  updateBoard();
  delay(500);
}

void initializeGame(){
  snakeSize = 3;
  foodPoint = random(256);
  while(foodPoint>=98 && foodPoint<=100){
    foodPoint = random(256);
  }
  for(int i = 0; i < (sizeof(snake)/sizeof(snake[0])); i++) {
    snake[i] = 0;
  }
  for(int i = 0; i < (sizeof(board)/sizeof(board[0])); i++) {
    board[i] = CRGB(3, 252, 107);
  }
  
  for (int i = 0; i < snakeSize; i++) {
    snake[i] = initialHead - i;
    board[snake[i]] = CRGB(232, 252, 3);
  }
  board[foodPoint] = CRGB(252, 3, 65);
  FastLED.show();
}

// int generateRandomNumber(int lower, int upper){
//   //srand(time(0));
//   //randomSeed(1);
//   //delay(100);
//   return random(lower,upper);
// }

void getButtons(){
  if (digitalRead(UP) == LOW) {
    prevMove = UP;
  }
  else if (digitalRead(LEFT) == LOW) {
    prevMove = LEFT;
  }
  else if (digitalRead(RIGHT) == LOW) {
    prevMove = RIGHT;
  }
  else if (digitalRead(DOWN) == LOW) {
    prevMove = DOWN;
  }
  Serial.println(prevMove);

}

void move(){
  if(prevMove != -1){
    int snakeHead = snake[0];
    if (prevMove == UP){
      snakeHead -= 16;
    }else if (prevMove == DOWN){
      snakeHead += 16;
    }else if (prevMove == LEFT){
      snakeHead -= 1;
    }else if (prevMove == RIGHT){
      snakeHead += 1;
    }
    for (int i = snakeSize - 1; i > 0; i--) {
      snake[i] = snake[i - 1];
    }
    snake[0] = snakeHead;
    if(!isCollision()){
        if(snake[0]==foodPoint){
          snakeSize += 1;
          if(snakeSize == 100){
            endGame(true);
          }
          foodPoint = random(256);
          while(foodPoint>=snake[snakeSize-2] && foodPoint<=snake[0]){
            foodPoint = random(256);
          }
        }
      }else{
        endGame(false);
      }
    }
}

bool isCollision(){
  int snakeHead = snake[0];
  if (snakeHead < 0 || snakeHead >= 256){
    return true;
  }
  if(prevMove == RIGHT && snakeHead%16==15){
    return true;
  }
  if(prevMove == LEFT && snakeHead%16==0){
    return true;
  }
  for (int i = 1; i < snakeSize; i++) {
    if (snakeHead == snake[i]) {
      return true;
    }
  }
  return false;
}
void endGame(bool isWinner){
  for(int i = 0; i < (sizeof(board)/sizeof(board[0])); i++) {
    board[i] = CRGB(0, 0, 0);
  }
  board[67] = CRGB(252, 3, 65);
  board[68] = CRGB(252, 3, 65);
  board[83] = CRGB(252, 3, 65);
  board[84] = CRGB(252, 3, 65);
  board[76] = CRGB(252, 3, 65);
  board[75] = CRGB(252, 3, 65);
  board[91] = CRGB(252, 3, 65);
  board[92] = CRGB(252, 3, 65);
  board[114] = CRGB(252, 3, 65);
  board[130] = CRGB(252, 3, 65);
  board[146] = CRGB(252, 3, 65);
  board[125] = CRGB(252, 3, 65);
  board[141] = CRGB(252, 3, 65);
  board[157] = CRGB(252, 3, 65);

  if(isWinner){
    for(int i = 147; i <= 156; i++){
      board[i] = CRGB(252, 3, 65);
    }
  }else{
    for(int i = 115; i <= 124; i++){
      board[i] = CRGB(252, 3, 65);
    }
  }
  FastLED.show();
  delay(3000);
  initializeGame();
}
void updateBoard(){
  for(int i = 0; i < (sizeof(board)/sizeof(board[0])); i++) {
    board[i] = CRGB(3, 252, 107);
  }
  for (int i = 0; i < snakeSize; i++) {
    board[snake[i]] = CRGB(232, 252, 3);
  }
  board[foodPoint] = CRGB(252, 3, 65);
  FastLED.show();
}
