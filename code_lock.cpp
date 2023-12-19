#include "header.hpp"

Servo	myservo;

int	 posKey = 0;
int  posValid = 0;
bool isDoorOpen = false;
char *password = "6789";
// u can chage the password here

int  position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char  keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPin[COLS] = {3, 2, A4, A5};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPin, ROWS, COLS);
