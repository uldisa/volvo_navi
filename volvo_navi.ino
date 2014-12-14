/*
Volvo RTI screen control
 
 */
#include "pins.h"
#include "rti.h"
//#include "melbus.h"
//#include "canbus.h"

uint16_t selector;
int8_t position;	// Calculated current position
int8_t last_position;	//Previous position

void setup()  
{
	#ifdef DEBUG
		Serial.begin(57600);
		Serial.write("Debugging started");
	#endif 
	pinMode(A3,INPUT);	
	rti_setup();
	//melbus_setup();
	//canbus_setup();
	last_position=255;
}
// 3.38 kom
// 8.95 kom

void loop() // run over and over
{	
	selector=analogRead(A3);

	position = round((double)(selector*(3.38 + 8.95) * 15.0) / ((double)(1023.0 * 3.38 )));
	Serial.print(selector);
	Serial.print(" ");
	Serial.println(position);
	if(last_position!=position) {
		rti_set_brightness(position);
		last_position=position;
	}
	rti_loop();
	//melbus_loop();
	//canbus_loop();
}
