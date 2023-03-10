/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/vcox/Documents/IoT/SuvaSmartRoom/Midterm1/src/Midterm1.ino"
/*
 * Project Midterm1
 * Description:This is the Welcome Box
 * Author:Vernon Cox
 * Date:7Mar23
 */

// setup() runs once, when the device is first turned on.

///////below this line is display stuff
#include <Adafruit_SSD1306.h>
#include <wemo.h>

void setup();
void loop();
#line 14 "c:/Users/vcox/Documents/IoT/SuvaSmartRoom/Midterm1/src/Midterm1.ino"
#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


bool buttonState;
bool toggleState;
int buttonread;
int rot1=1;
int rot2=2;
int rot3=3;
int rot0=0;
const int PINPIN=D13;

//below this line is PIR stuff

int led = 4;                // the pin that the LED is atteched to
int ms_sensor = 3;          // the pin that the motion sensor is atteched to
int button = 2;             // the pin that the button is a attached to
int state = LOW;            // by default, no motion detected
int ms_val = 0;             // variable to store the motion sensor status (value)
int ms_state = 0;
int button_val = 0;         // variable to store the button sensor status (value)

int count = 0;              // variable to store total people counted since device was turned on or reset
int button_presses = 0;

//SYSTEM_MODE(MANUAL); //when internet connection is needed.

SYSTEM_MODE(SEMI_AUTOMATIC); //when no internet connection is needed.


void setup() {

    //below this line is WEMO stuff

    // pinMode(D13,INPUT);
    // Serial.begin(9600);
    // waitFor(Serial.isConnected,10000);
    // Serial.print("Ready to Go\n");

    // WiFi.on();
    // WiFi.setCredentials("IoTNetwork");

    // WiFi.connect();
    // while(WiFi.connecting()) {
    // Serial.printf(".");


//below this line is display stuff
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)

  display.setCursor(0,0);
  display.display(); //this will show the Adafruit logo (splashscreen)
  delay(1500); //this will delay the splashscreen to increase the marketing effect
  display.clearDisplay();

//   display.setTextSize(2);
//   display.setTextColor(WHITE);
//   display.setCursor(25,25);
//   display.printf("Hello\n");
//   display.display();
//    delay(1500); 
//   display.clearDisplay();
//   display.setCursor(5,25);
//   display.printf("World\n");
//   display.display();
//    delay(1500); 
//   display.clearDisplay();
//   display.setCursor(5,25);
//   display.printf("My name is");
//   display.display();
//     delay(1000);
//   display.clearDisplay();
//   display.setCursor(5,25);
//   display.printf("Se%cor",164);
//   display.display();
//   delay(1000);
//   display.clearDisplay();
//   display.setCursor(3,25);
//   display.printf("Vernon Cox");
//   display.display();
//   delay(2000);
//   display.clearDisplay();
//   display.setCursor(0,25);
//   display.printf("BornOnDate:");
//   display.display();
//   delay(2000);
//   display.clearDisplay();
//   display.setCursor(15,25);
//   display.printf("%c%c%c%c%c%c%c", 50,54,65,80,82,53,56);
//   display.display();
//   delay(3000);

//   display.invertDisplay(true);
//   delay(1000);

// below this line is PIN stuff

  pinMode(led, OUTPUT);         // initalize LED as an output
  pinMode(ms_sensor, INPUT);    // initialize motion sensor as an input
  pinMode(button, INPUT);       // initialize button as an input
  digitalWrite(led, LOW);       // set the LED as off

}




void loop() {

    //below this line is WEMO stuff

// buttonState=digitalRead(PINPIN);
  
 
//   if(buttonState){
//      toggleState=!toggleState;
//   }
//      if(toggleState){
//       switchON(0);

//     Serial.printf("Button is pressed \n");
//   }
//     else{
//       switchOFF(0);
//       }
// delay(1000);

//below this line is PIN stuff

  ms_val = digitalRead(ms_sensor);      // read motion sensor value
  button_val = digitalRead(button);     // read button value
  
  if (ms_val == HIGH) {
      if (ms_state == LOW) {
      // Particle.publish("Motion Sensor Value");
          ms_state = HIGH;
      }
  }
  else {
      if (ms_state == HIGH) {
         // Particle.publish("Motion Sensor Value", "LOW");
          ms_state = LOW;
      }
  }

  if (button_val == LOW) {
        button_presses = button_presses + 1;                            // running total of total button presses


        if (ms_val == HIGH) {                     // motion sensor is activated
        //if (button_val == HIGH && ms_val == HIGH) {                     // check if button is pressed and motion sensor is activated
            count = count + 1;
            digitalWrite(led, HIGH);                                    // turn LED on
        
            if (state == LOW) {                                         // check if state is LOW
                state = HIGH;                                           // check if state is HIGH
            }
        }
        
        delay(500);                                                     // delay 500 milliseconds
    }

  
  else {
      digitalWrite(led, LOW);                       // turn LED OFF
      delay(500);                                   // delay 500 milliseconds 
      
      if (state == HIGH){                           // check if state is high
       // state = LOW;                                // update variable state to LOW
    }
  }
  
  
//   if (Time.second() == 0) {
//        Particle.publish( "Counter", "{ \"People Counted\": \"" + String(count) + "\","+              //Publishes people counted, button presses, and IR sensor triggers to Thingspeak
//        "\"Button Presses\": \"" + String(button_presses) + "\"}", 60, PRIVATE);
//   }
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(1,15);
    display.printf("Welcome U are\n");
    display.printf("vistor=%i\n",count);
    display.display();
    delay(1500); 
    display.clearDisplay();
}
