#include <SPI.h>                             // Подключаем библиотеку SPI
#include <Adafruit_GFX.h>                    // Подключаем библиотеку Adafruit_GFX
#include <Max72xxPanel.h>                    // Подключаем библиотеку Max72xxPanel
#include "SSVQueueStackArray.h"              // Подключаем библиотеку для структуры данных

int pinCS = 10;                              // Указываем к какому выводу подключен контакт CS
int numberOfHorizontalDisplays = 1;          // Количество матриц по горизонтали
int numberOfVerticalDisplays = 4;            // Количество матриц по-вертикали

const short right = 1;                       // Направления
const short up = 2;
const short left = 3;
const short down = 4;

int current_x;                               // Текущие координаты
int current_y;
int length_snake = 10;                       // Длина змейки

SSVQueueStackArray <int> snake_x;            // Координаты змейки по х
SSVQueueStackArray <int> snake_y;            // Координаты змейки по y

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
void setup() {
  matrix.setIntensity(5);                    // Задаем яркость от 0 до 15
  matrix.setRotation(3);                     // Направление текста 1,2,3,4
}

void loop() {
  current_x = 5;                             // Задаем текущие координаты
  current_y = 5;
  int commands [94] = {1,1,1,4,4,            // Тестовые команды для змейки
                       4,1,1,1,1, 
                       1,2,2,2,3, 
                       3,3,3,3,3, 
                       3,3,4,4,4, 
                       1,1,1,1,1, 
                       2,2,2,1,1, 
                       1,1,1,4,4, 
                       4,4,4,1,1, 
                       1,1,1,1,2, 
                       2,2,2,1,1, 
                       1,1,1,1,1,
                       4,4,4,3,3,
                       3,3,3,3,3,
                       3,3,3,3,3,
                       3,3,3,3,3,
                       2,2,2,3,3,
                       3,3,3,3,3,
                       3,2,1,1};

  for(int command : commands){
    snakeDirection(current_x, current_y, command);
  }
}

void snakeDirection(int x, int y, int direction) {   //Задаем направления для змейки
    switch (direction) {
    case right:
			current_x++;
      snake(x, y);
			break;
    
    case down:
			current_y--;
      snake(x, y);
			break;
    
    case left:
			current_x--;
      snake(x, y);
			break;

		case up:
			current_y++;
      snake(x, y);
			break;

		default: 
			return;
	}
}

void snake(int x, int y){                            //отрисовка змейки
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