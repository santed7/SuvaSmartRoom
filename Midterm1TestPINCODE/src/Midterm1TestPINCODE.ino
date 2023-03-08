/*
 * Project Midterm1TestPINCODE
 * Description:
 * Author:
 * Date:
 */

/* Pin diagram of motion sensor and button
 *
 *
 *  /-------------------------------------------------------------------\
 *  |              +-----+                                              |
 *  |   +----------| USB |---------+                                    |
 *  |   | O        +-----+      O  |                                    |
 *  |   | [ ] RESET                |                                    |
 *  \---| [*] 3V3                  |                                    |
 *      | [ ] MODE                 |                                    |
 *      | [*] GND                  |                                    |
 *      | [ ] A0          Lipo [ ] |                                    | 
 *      | [ ] A1  +-------+ EN [ ] |                                    |
 *      | [ ] A2  |   *   | VIN[ ] |                                    |
 *      | [ ] A3  | ARGON | D8 [ ] |                                    |
 *      | [ ] A4  |       | D7 [ ] |            GND                     |
 *      | [ ] A5  +-------+ D6 [ ] |            |                       |
 *      | [ ] D13           D5 [ ] |            1k Resistor             |
 *      | [ ] D12           D4 [ ] |            |                       |
 *      | [ ] D11           D3 [*] |------------|-----Motion Sensor-----|
 *      | [ ] D10           D2 [*] |----------------|--Button-----------/
 *      | [ ] D9            D1 [ ] |                |
 *      | [ ] NC            D0 [*] |----|---LED     |
 *      |   WIFI0         0NFC     |    |           1k Resistor
 *      |O                        O|    |           |
 *      +--------------------------+    |           |
 *                                     GND         GND
 *      
 */


int led = 4;                // the pin that the LED is atteched to
int ms_sensor = 3;          // the pin that the motion sensor is atteched to
int button = 2;             // the pin that the button is a attached to
int state = LOW;            // by default, no motion detected
int ms_val = 0;             // variable to store the motion sensor status (value)
int ms_state = 0;
int button_val = 0;         // variable to store the button sensor status (value)
//int IR_val = 0;             // variable to store the IR sensor status (value)
//int IR_state = 0;
int count = 0;              // variable to store total people counted since device was turned on or reset
int button_presses = 0;
//int IR_triggers = 0;

SYSTEM_MODE(SEMI_AUTOMATIC); //when no internet connection is needed.

void setup() {
  pinMode(led, OUTPUT);         // initalize LED as an output
  pinMode(ms_sensor, INPUT);    // initialize motion sensor as an input
  pinMode(button, INPUT);       // initialize button as an input
  digitalWrite(led, LOW);       // set the LED as off
  //Particle.subscribe("Detect", IR_func, MY_DEVICES);
}

// int IR_func(const char *event, const char *data) {
//     if (data) {                 // check if any data was sent
//         count = count + 1;          // set IR_val to HIGH
//     }
    
//     return count;              // return IR_val so it carries over to the rest of the code
// }


void loop(){
  ms_val = digitalRead(ms_sensor);      // read motion sensor value
  button_val = digitalRead(button);     // read button value
  
  if (ms_val == HIGH) {
      if (ms_state == LOW) {
          Particle.publish("Motion Sensor Value", "HIGH");
          ms_state = HIGH;
      }
  }
  else {
      if (ms_state == HIGH) {
          Particle.publish("Motion Sensor Value", "LOW");
          ms_state = LOW;
      }
  }

  if (button_val == HIGH) {
        button_presses = button_presses + 1;                            // running total of total button presses

        if (button_val == HIGH && ms_val == HIGH) {                     // check if button is pressed and motion sensor is activated
            count = count + 1;
            digitalWrite(led, HIGH);                                    // turn LED on
        
            if (state == LOW) {                                         // check if state is LOW
                state = HIGH;                                           // check if state is HIGH
            }
        }
        
        delay(500);                                                     // delay 500 milliseconds
    }
  /*
  if (IR_val == HIGH) {
        IR_triggers = IR_triggers + 1;                              // running total of total IR sensor
  
        if (IR_val == HIGH && ms_val == HIGH) {                     // check if IR and motion sensors are activated
            count = count + 1;
            digitalWrite(led, HIGH);                                // turn LED on

            delay(500);                                             // delay 500 milliseconds
        
            if (state == LOW) {                                     // check if state is LOW
                state == HIGH;                                      // update variable state to HIGH
            }
        }
        
        IR_val = LOW;                                               // set IR val to low
    }
  */
  
  else {
      digitalWrite(led, LOW);                       // turn LED OFF
      delay(500);                                   // delay 500 milliseconds 
      
      if (state == HIGH){                           // check if state is high
        state = LOW;                                // update variable state to LOW
    }
  }
  
  
  
  
  if (Time.second() == 0) {
       Particle.publish( "Counter", "{ \"People Counted\": \"" + String(count) + "\","+              //Publishes people counted, button presses, and IR sensor triggers to Thingspeak
       "\"Button Presses\": \"" + String(button_presses) + "\"}", 60, PRIVATE);
  }
  
}