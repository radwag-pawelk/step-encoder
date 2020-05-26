/*
    Name:       STEP_ENC.ino
    Created:	24.05.2020 08:52:07
    Author:     PAWEL-ASUS\pawel
*/

#define PIN_ENCA 10
#define PIN_ENCB 11

volatile uint8_t lastA, lastB;
#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(PIN_ENCA, PIN_ENCB);


void setup()
{
	pinMode(PIN_ENCA, INPUT_PULLUP);
	pinMode(PIN_ENCB, INPUT_PULLUP);
	lastA = digitalRead(PIN_ENCA);
	lastB = digitalRead(PIN_ENCB);
	Serial.begin(57600);
	delay(1000);
	Serial.print("A-B: ");
}

int read_encoder() {
	uint8_t currA = digitalRead(PIN_ENCA);
	if (currA == lastA) return 0;
	lastA = currA;
	if (currA != digitalRead(PIN_ENCB)) return 1;
	else return -1;
}

long oldPosition = -999;

void loop2() {
	long newPosition = myEnc.read();
	if (newPosition != oldPosition) {
		oldPosition = newPosition;
		Serial.println(newPosition);
	}
}

long count = 0;

void loop()
{
	int x = read_encoder();
	if (x == 0) return;
	count++;
	Serial.print(count);
	Serial.print(": ");
	Serial.print(x);
	Serial.println();
}
