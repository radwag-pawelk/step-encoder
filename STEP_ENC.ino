/*
	Name:       STEP_ENC.ino
	Created:	24.05.2020 08:52:07
	Author:     PAWELK
*/

#include <Encoder.h>

//

// Rotary encoders pins
#define PIN_ENCA 2	// pin A/CLK
#define PIN_ENCB 3	// pin B

#ifdef USE_ENCODER
Encoder myEnc(PIN_ENCA, PIN_ENCB);
long oldPosition = -999;
void loop() {
	long newPosition = myEnc.read();
	if (newPosition != oldPosition) {
		oldPosition = newPosition;
		Serial.println(newPosition);
	}
}
#endif // USE_ENCODER




volatile uint8_t lastA;				// Last digit state
volatile uint8_t mask = B00110011;	// Shifting mask


void setup()
{
	// PD4-PD7 as output; stepper motors driving lines
	DDRD = B11110000;
	PORTD = PORTD & B11000000;

	// PD3-PD4 as input for rotary encoders pins
	pinMode(PIN_ENCA, INPUT_PULLUP);
	pinMode(PIN_ENCB, INPUT_PULLUP);

	// default state on startup
	PORTD = (PORTD & B00001111) | (mask & B11110000);
	Serial.begin(115200);
}

void loop()
{
	int x = encoder_read();
	if (x == 0) return;
	rotare(x);
}

// Detection of encoder rotation changes
// 1 - right
// 0 - none
// -1- left
int encoder_read() {
	uint8_t currA = digitalRead(PIN_ENCA);
	if (currA == lastA) return 0;
	lastA = currA;
	if 	(currA != digitalRead(PIN_ENCB)) 
		return 1;
	else 
		return -1;
}

// Makes one step turn
void rotare(int8_t step) {
	if (step > 0) 
		mask = (mask << 1) | (mask >> (8 - 1));
	else 
		mask = (mask >> 1) | (mask << (8 - 1));
	PORTD = (PORTD & B00001111) | (mask & B11110000);
}


