/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/vcox/Documents/IoT/SuvaSmartRoom/MS_test_v2/src/MS_test_v2.ino"
/*
 * Project MS_test_v2
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/vcox/Documents/IoT/SuvaSmartRoom/MS_test_v2/src/MS_test_v2.ino"
const int PIR_SENSOR_OUTPUT_PIN = 5;	/* PIR sensor O/P pin */
int warm_up;

SYSTEM_MODE(SEMI_AUTOMATIC); 

void setup() {
pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);
Serial.begin(9600);	/* Define baud rate for serial communication */
delay(20000);	/* Power On Warm Up Delay */
}

void loop() {
int sensor_output;
sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN);
if(sensor_output == LOW )
  {
if(warm_up == 1 )
     {
Serial.print("Warming Up\n\n");
warm_up = 0;
delay(2000);
    }
Serial.print("No object in sight\n\n");
delay(1000);
  }
else
  {
Serial.print("Object detected\n\n");    
warm_up = 1;
delay(1000);
  }  
}