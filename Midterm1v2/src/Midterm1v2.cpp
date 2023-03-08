/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/vcox/Documents/IoT/SuvaSmartRoom/Midterm1v2/src/Midterm1v2.ino"
/*
 * Project Midterm1v2
 * Description:This is the Welcome Box
 * Author:Vernon Cox
 * Date:7Mar23
 */

//below is the line for the entire code
#include <IotClassroom_CNM.h>

///////below are the lines is display stuff
#include <Adafruit_SSD1306.h>
//#include <wemo.h>

void setup();
void loop();
#line 15 "c:/Users/vcox/Documents/IoT/SuvaSmartRoom/Midterm1v2/src/Midterm1v2.ino"
#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//below are the lines for the LCD stuff
bool buttonState;
bool toggleState;
int buttonread;
int rot1=1;
int rot2=2;
int rot3=3;
int rot0=0;
const int PINPIN=D2;

//below are the lines is PIR stuff

int led = 4;                // the pin that the LED is atteched to
int ms_sensor = 3;          // the pin that the motion sensor is atteched to
int button = 2;             // the pin that the button is a attached to
int state = LOW;            // by default, no motion detected
int ms_val = 0;             // variable to store the motion sensor status (value)
int ms_state = 0;           // variable to store the motion sensor cycles
int button_val = 0;         // variable to store the button sensor status (value)
int count = 0;              // variable to store total people counted since device was turned on or reset
int button_presses = 0;

//below are the lines for the room lite stuff
const int NUMBULBS=7;
int BULB=1; 
int bulbCount;
int color;
const int buttonPin(D13); //this is the pin# of the button to turn on lights


//SYSTEM_MODE(MANUAL); //when internet connection is needed.

SYSTEM_MODE(SEMI_AUTOMATIC); //when no internet connection is needed.


void setup() {

    //below this line is WEMO and room lite stuff
    pinMode(D13,INPUT);
    pinMode(D2,INPUT);
    Serial.begin(9600);
    waitFor(Serial.isConnected,10000);
    Serial.print("Ready to Go\n");

    WiFi.on();
    WiFi.setCredentials("IoTNetwork");
    WiFi.connect();
    while(WiFi.connecting()) {
    Serial.printf(".");
    }
    Serial.printf("\n\n");

    //below this line is display stuff
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)
    display.setCursor(0,0);
    display.display(); //this will show the Adafruit logo (splashscreen)
    delay(1500); //this will delay the splashscreen to increase the marketing effect
    display.clearDisplay();


    // below this line is PIN stuff

    pinMode(led, OUTPUT);         // initalize LED as an output
    pinMode(ms_sensor, INPUT);    // initialize motion sensor as an input
    pinMode(button, INPUT);       // initialize button as an input
    digitalWrite(led, LOW);       // set the LED as off
}

void loop() {

        //below this line is PIN stuff
    ms_val = digitalRead(ms_sensor);      // read motion sensor value
    button_val = digitalRead(button);     // read button value
  
    if (ms_val == HIGH) {
      if (ms_state == LOW) {
          ms_state = HIGH;
          }
    }
    else {
      if (ms_state == HIGH) {
          ms_state = LOW;
      }
    }

    if (button_val == HIGH) {
        button_presses = button_presses + 1;                            // running total of total button presses


        if (ms_val == HIGH) {            // motion sensor is activated
            count = count + 1;
            digitalWrite(led, HIGH);                                    // turn LED on
        
            if (state == LOW) {                                         // check if state is LOW
                state = HIGH;                                           // check if state is HIGH
            }
            else {
                digitalWrite(led, LOW);                       // turn LED OFF
            }
      
        }
        delay(1500);                                   // delay 1500 milliseconds 
    }   
    

    
      if (state == HIGH){                           // check if state is high
       // state = LOW;                                // update variable state to LOW
         }
    
    //below are the line for the DISPLAY
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(1,15);
    display.printf("Welcome U are\n");
    display.printf("vistor=%i\n",count);
    display.display();
    delay(1500); 
    display.clearDisplay();

    //below this line is WEMO stuff
    buttonState=digitalRead(PINPIN);
        if(buttonState){
            toggleState=!toggleState;
         }
        if(toggleState){
            switchON(0);
            Serial.printf("Button is pressed \n");
         }
        else{
            switchOFF(0);
        }
    delay(1000);

    //below are the lines for the room lite stuff
    Serial.printf("Setting color of bulb %i to color %i\n",BULB,45000);
    setHue(BULB,true,45000,155,255);
    delay(30000);
    setHue(BULB,false,45000,155,255); 
    delay(2000);
    for (bulbCount=1; bulbCount<=NUMBULBS;bulbCount++){
        setHue(bulbCount,true,45000,155,255);
    }
}