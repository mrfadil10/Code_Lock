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
bool isRFIDValid = false;

int RedpinLock = A0;
int GreenpinUnlock = A1;
int YellowpinUnlock = A2;

void	setup ()
{
	Serial.begin(9600);
	SPI.begin();
	mfrc522.PCD_Init();
	myservo.attach(SERVO_PIN);
	pinMode(RedpinLock, OUTPUT);
	pinMode(GreenpinUnlock, OUTPUT);
	pinMode(YellowpinUnlock, OUTPUT);

	LockedPosition(true);

	Serial.println("Put your card to the reader...");
	Serial.println();
}

void	loop()
{
	if (isRFIDValid == false)
	{
		char key = keypad.getKey();
		if (!key)
			return ;
		Serial.println("Key pressed" + String(key));
		if (key == '*' || key == '#')
		{
			//close door
			Serial.println("Door closed, resuse RFID");
			posKey = 0;
			posValid = 0;
			if (isDoorOpen == true)
				LockedPosition(true);
			isDoorOpen = false;
			isRFIDValid = false;
			return ;
		}
		if (isDoorOpen)
			return ;
		if (key == password[posKey])
			posValid++;
	}
	posKey++;
	if (posKey == 4 && posValid < 4)
	{
		Serial.println("Door opened, resuse RFID");
		posKey = 0;
		posValid = 0;
		return ;
	}
	Serial.println("Position: " + String(position));
	if (posValid == 4)
	{
		isDoorOpen = true;
		Serial.println("Door opening ...");
		LockedPosition(false);
		Serial.println("Door opened.");
	}
	delay(100);
	return ;
}

LockedPosition(false);
Serial.printIn("Door opened.");
}
delay(100);
return;

}

if (! mfrc522.PICC_IsNewCardPresent()) {
return ;

}

if (! mfrc522.PICC_ReadCardSerial()) {

return;

}

Serial.print("UID tag :");
String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
	Serial.print(mfrc522.uid.uidByte[i] < 0x10?" 0":"");
	Serial.print(mfrc522.uid.uidByte[i], HEX);
	content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
	content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.printIn();
Serial.print("Message : ");
content.toUpperCase();
if (content.substring(1) == "69 CD C8 2B")
{
	Serial.printIn("Authorized access by RFID");
	Serial.println("Now enter password");
	Serial.println();
	isRFIDValid = true;
	digitalWrite(RedpinLock,LOW);
	digitalWrite(GreenpinUnlock, LOW);
	digitalWrite(YellowpinUnlock, HIGH);
}
else
{
	Serial.println("Access denied");
	for (int i = 0; i < 3; i++)
	{
		digitalWrite(RedpinLock,LOW);
		delay(100);
		digitalWrite(RedpinLock,HIGH);
	}
	delay(DENIED_DELAY);
}

void LockedPosition(int locked)
{
	if (locked)
	{
		digitalWrite(RedpinLock,HIGH);
		digitalWrite(GreenpinUnlock, LOW);
		digitalWrite(YellowpinUnlock, LOW);
		myservo.write(11);
		for (int pos = 0; pos <= 180; pos += 5)
		{
			myservo.write(pos);
			delay(15);
		}
	}
	else
	{
		digitalWrite(RedpinLock, LOW);
		digitalWrite(GreenpinUnlock, HIGH);
		digitalWrite(YellowpinUnlock, LOW);
		myservo.write(90);
		for (int pos = 180; pos >= 0; pos -= 5)
		{
			myservo.write(pos);
			delay(15);
		}
	}
}