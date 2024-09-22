#include <SPI.h>                             // Подключаем библиотеку SPI
#include <Adafruit_GFX.h>                    // Подключаем библиотеку Adafruit_GFX
#include <Max72xxPanel.h>                    // Подключаем библиотеку Max72xxPanel

int pinCS = 10;                              // Указываем к какому выводу подключен контакт CS
int numberOfHorizontalDisplays = 1;          // Количество матриц по горизонтали
int numberOfVerticalDisplays = 4;            // Количество матриц по-вертикали

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "<[^^] [1] [2] [3] [4] [5] [^^]>"; // текст, который будет плыть
int wait = 90; // время между крайними перемещениями букв

int spacer = 1; // расстояние между буквами
int width = 5 + spacer; // размер шрифта

void setup() {
    matrix.setIntensity(5);                    // Задаем яркость от 0 до 15
    matrix.setRotation(3);                     // Направление текста 1,2,3,4
}

void loop() {
    for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
        matrix.fillScreen(LOW);

        int letter = i / width;
        int x = (matrix.width() - 1) - i % width;
        int y = (matrix.height() - 8) / 2; // center the text vertically

        while ( x + width - spacer >= 0 && letter >= 0 ) {
            if ( letter < tape.length() ) {
                matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
            }
            letter--;
            x -= width;
        }

        matrix.write();
        delay(wait);
    }
}