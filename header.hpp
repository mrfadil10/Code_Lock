# include <SPI.h>
# include <MFRC522.h>
# include <Servo.h>
# include <Keypad.h>

# define SS_PIN 10
# define RST_PIN 9
# define SERVO_PIN 8

#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

MFRC522 mfrc522(SS_PIN, RST_PIN);