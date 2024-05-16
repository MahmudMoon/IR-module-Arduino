/**
 * A simple test-sketch that uses the IRemote library to detect when the power on/off button
 * is pressed on an NEC remote control. If a button press is detected, the sketch toggles
 * the on-board state of the LED (pin 13 on the Arduino Uno).
 */

#include <IRremote.h>

#define IR_RECEIVE_PIN 2
#define LED_PIN 8

IRrecv receiver(IR_RECEIVE_PIN);
IRsend sender;

void setup()
{
  // There's no need to set up the IR_RECEIVE_PIN with pinMode
  // the library takes care of that...
  // pinMode(IR_RECEIVE_PIN, INPUT);
 
  pinMode(LED_PIN, OUTPUT);

  pinMode(IR_RECEIVE_PIN, INPUT);

  Serial.begin(9600);

  while(!Serial)
  {  }

  // Enable the IR receiver
  receiver.enableIRIn();

  Serial.print("IR Receiver ready!");
}

void loop()
{

  uint32_t data = 0xFF609F;
  uint8_t len = 32;

  sender.sendNEC(data, len);
  decode_results results;

  // decode returns 1 if something was received
  // otherwise it returns 0
  // The code and protocol type get stored in results
  if (receiver.decode(&results))
  {
	// The ON/OFF button was pressed on my remote
	// Note: The codes might vary across different remote controls!
	if(results.value == 0xFF609F)
  	digitalWrite(LED_PIN, HIGH);
    
	Serial.print(results.bits);
	Serial.print(": ");
	Serial.println(results.value, HEX);


	receiver.resume(); // Receive the next value
  }

  Serial.println(digitalRead(IR_RECEIVE_PIN));
}