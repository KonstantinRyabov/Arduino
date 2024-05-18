#include <SPI.h>                             // Подключаем библиотеку SPI
#include <Adafruit_GFX.h>                    // Подключаем библиотеку Adafruit_GFX
#include <Max72xxPanel.h>                    // Подключаем библиотеку Max72xxPanel
#include <SSVQueueStackArray.h>              // Подключаем библиотеку для структуры данных

int pinCS = 10;                              // Указываем к какому выводу подключен контакт CS
int numberOfHorizontalDisplays = 1;          // Количество матриц по горизонтали
int numberOfVerticalDisplays = 4;            // Количество матриц по-вертикали

const short right = 1;                       // Направления
const short up = 2;
const short left = 3;
const short down = 4;

int current_x = 5;                               // Текущие координаты
int current_y = 5;
int length_snake = 3;                            // Длина змейки
bool is_first_food = true;
int command = 1;

int PIN_ANALOG_X = 0;
int PIN_ANALOG_Y = 1;

const short SPEED = 800;

SSVQueueStackArray <int> snake_x;            // Координаты змейки по х
SSVQueueStackArray <int> snake_y;            // Координаты змейки по y

int food_rand_x = 32;
int food_rand_y = 8;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  matrix.setIntensity(5);                    // Задаем яркость от 0 до 15
  matrix.setRotation(3);                     // Направление текста 1,2,3,4

}

void loop() {

  int food_x;
  int food_y;
  
  if(is_first_food){
    food_x = random(food_rand_x);
    food_y = random(food_rand_y);
    matrix.drawPixel(food_x, food_y, HIGH);
    is_first_food = false;
  }

  int x = analogRead(PIN_ANALOG_X);
  int y = analogRead(PIN_ANALOG_Y);
  
  if (x > 1000) {
    command = 2;
  }
  else if (x < 100){
    command = 4;
  }
  else if (y > 1000){
    command = 1;
  }
  else if (y < 100){
    command = 3;
  }


  snakeDirection(current_x, current_y, command);

  if(current_x < 0){
    current_x = 32;                 
  }

  if(current_x > 32){
    current_x = 0;
  }

  if(current_y < 0){
    current_y = 8;
  }

  if(current_y > 8){
    current_y = 0;
  }

  if((food_x == current_x) && (food_y == current_y)){
      length_snake++;
      matrix.drawPixel(food_x, food_y, LOW);

      food_x = random(food_rand_x);
      food_y = random(food_rand_y);
      matrix.drawPixel(food_x, food_y, HIGH);
    }
  }


void snakeDirection(int x, int y, int direction) {   //Задаем направления для змейки
    switch (direction) {
    case right:
      current_x++;
      delay(SPEED);
      snake(x, y);
      break;
    
    case down:
      current_y--;
      delay(SPEED);
      snake(x, y);
      break;
    
    case left:
      current_x--;
      delay(SPEED);
      snake(x, y);
      break;

    case up:
      current_y++;
      delay(SPEED);
      snake(x, y);
      break;

    default: 
      return;
	}
}

void snake(int x, int y){                            //Отрисовка змейки
    matrix.drawPixel(x, y, HIGH);
    matrix.write();
    delay(200);

    snake_x.push(x);
    snake_y.push(y);

    if(snake_x.getCount() == length_snake){
      int tail_x = snake_x.pop();
      int tail_y = snake_y.pop();
      matrix.drawPixel(tail_x, tail_y, LOW);
      matrix.write();
    }
    

} 