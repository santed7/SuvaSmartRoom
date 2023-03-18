/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/vcox/Documents/IoT/SuvaSmartRoom/Midterm2/Midterm2v1/src/Midterm2v1.ino"
/*
 * Project Midterm2
 * Description:Midterm2
 * Author:Vernon Cox
 * Date:17Mar23
 */


#include <math.h>
#include "Adafruit_MQTT_SPARK.h"
#include "HX711.h"
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "credentials.h"

 void setup();
void loop ();
void getWiFi();
#line 17 "c:/Users/vcox/Documents/IoT/SuvaSmartRoom/Midterm2/Midterm2v1/src/Midterm2v1.ino"
HX711 myScale (14, 17); // my (2) digital pins [2 are needed]

 //const int CAL_FACTOR=95; // changing value changes get_units units (lb , g, ton , etc .)
 //const int SAMPLES=10; // number of data points averaged when using get_units or get_value
 int soilentGreen=A5; //moistSensor readings
 //float weight, rawData, calibration;
 //int offset;

 int pumpState;
 int pumpread;
 const int pumpPIN=D11;
 
 


/*
Copy the Adafruit.io Setup line and the next four lines to a credentials.h file
//************************* Adafruit.io Setup *****************************************
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883        // use 1883 for SSL
#define AIO_USERNAME    "username"	// replace with your Adafruit.io username
#define AIO_KEY         "key"		    // replace with your Adafruit.io key
*/

/************ Global State (you don't need to change this!) ***   ***************/ 
TCPClient TheClient; 

 // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 

/****************************** Feeds ***************************************/ 
// Setup Feeds to publish or subscribe 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 
Adafruit_MQTT_Subscribe subFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/suvabuttononoff"); 
//Adafruit_MQTT_Publish pubFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/suvaRand");
//Adafruit_MQTT_Publish pubFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/weight");
Adafruit_MQTT_Publish pubFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/soilentGreen");

/************Declare Variables*************/
unsigned int last, lastTime;
float subValue,pubValue;

/************Declare Functions*************/
void MQTT_connect();
bool MQTT_ping();
//srand(unsigned int seed_value);
//int random = rand();

//void getWiFi();
SYSTEM_MODE(SEMI_AUTOMATIC);



 void setup() {

    Serial.begin(9600);
    waitFor(Serial.isConnected,10000);
    delay(1000);

    WiFi.clearCredentials();
    Serial.printf("Has Credentials = %i\n\n",WiFi.hasCredentials());

    delay(1000);

    WiFi.setCredentials("DDCIOT","ddcIOT2020");
    WiFi.setCredentials("ParentHouse","Suva9fiji");


  // Connect to Internet but not Particle Cloud
    WiFi.on();
    WiFi.connect();
    while(WiFi.connecting()) {
      Serial.printf(".");
      delay(100);
  }
  Serial.printf("\n\n");
  delay(3000);
  getWiFi();
  pinMode(D7,OUTPUT);
  pinMode(soilentGreen, INPUT);
  pinMode(pumpPIN, OUTPUT);

  //Serial.print("Ready to Go");
  digitalWrite(pumpPIN,HIGH);
  delay(6000);
  digitalWrite(pumpPIN,LOW);
  delay(6000);
  digitalWrite(pumpPIN,HIGH);
  delay(6000);
  digitalWrite(pumpPIN,LOW);



  // Setup MQTT subscription
  mqtt.subscribe(&subFeed);//must tell Argon to subscribe

  
//  myScale.set_scale(); // initialize loadcell
//  delay(5000); // this is time for the loadcell settle
//  myScale.tare(29.25); // set the tare weight (or zero )
//  myScale.set_scale(CAL_FACTOR); // adjust when calibrating scale to desired units
 
 
 }

 void loop () {
  soilentGreen=analogRead(soilentGreen);

  MQTT_connect();
  MQTT_ping();
 // Using data from loadcell
//  weight = myScale.get_units(SAMPLES); // return weight in units set by set_scale ();
//  delay(5000); // gonna wait between readings


  // this is our 'wait for incoming subscription packets' busy subloop 
  // Adafruit_MQTT_Subscribe *subscription;
  // while ((subscription = mqtt.readSubscription(100))) {
  //   if (subscription == &subFeed) {
  //     weight = atoi((char *)subFeed.lastread);//ASCII to float
  //     Serial.printf("Button is Pushed %i \n",suvaButtonOnOff); 
      // if(suvaButtonOnOff){
      //   digitalWrite(D7,HIGH);//turns on the (small) D7 light on the Argon when Adafruit button is pushed
      // }
      //   else{
      //     digitalWrite(D7,LOW);//turns off the (small) D7 light on the Argon when Adafruit button is pushed
      //   }
  //   }
  
    
  // }
   if(WiFi.hasCredentials()) {
    digitalWrite(D7,HIGH);
    delay(250);
    digitalWrite(D7,LOW);
    delay(250);
  }
}


void getWiFi() {
  WiFiAccessPoint ap[10];
  int sectype,cytype,found,i;
  byte mac[6];

  String security[6] = {"WLAN_SEC_UNSEC", "WLAN_SEC_WEP", "WLAN_SEC_WPA", "WLAN_SEC_WPA2", "WLAN_SEC_WPA_ENTERPRISE", "WLAN_SEC_WPA2_ENTERPRISE"};
  String cypher[4] = {"N/A","WLAN_CIPHER_AES", "WLAN_CIPHER_TKIP", "WLAN_CIPHER_AES_TKIP"};

  Serial.printf("Scan Argon for WiFi Information \n");
  Serial.printf("ip address: %s \n", WiFi.localIP().toString().c_str());
  WiFi.macAddress(mac);
  Serial.printf("mac: %02X:%02X:%02X:%02X:%02X:%02X \n", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
  found = WiFi.getCredentials(ap, 5);
  Serial.printf("Credentials for %d Access Points Found \n",found);
  for (i = 0; i < found; i++) {
    sectype = (int) ap[i].security;
    cytype = (int) ap[i].cipher;
    for(int j=0;j<6;j++){
       mac[j] = ap[i].bssid[j];
    }
      
    Serial.printf("AP%d - ssid: %s \n", i,ap[i].ssid);
    Serial.printf("AP%d - mac: %02X:%02X:%02X:%02X:%02X:%02X \n", i,mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    Serial.printf("AP%d - security: %d (security %s) \n", i,sectype,security[sectype].c_str());
    Serial.printf("AP%d - cipher:   %d (cipher %s) \n\n", i,cytype, cypher[cytype].c_str());
  }
    
//lines below for puslishing
  if((millis()-lastTime > 6000)) {
    if(mqtt.Update()) {
      pubFeed.publish(soilentGreen);
    
      } 
      Serial.printf("Moisture reading is %i \n",soilentGreen); 
    lastTime = millis();
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
 
  // Return if already connected.
  if (mqtt.connected()) {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.printf("Error Code %s\n",mqtt.connectErrorString(ret));
       Serial.printf("Retrying MQTT connection in 5 seconds...\n");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds and try again
  }
  Serial.printf("MQTT Connected!\n");
}

bool MQTT_ping() {
  static unsigned int last;
  bool pingStatus;

  //keep the connection alive

  if ((millis()-last)>120000) {
      Serial.printf("Pinging MQTT \n");
      pingStatus = mqtt.ping();
      if(!pingStatus) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
      }
      last = millis();
  }
  return pingStatus;
}

 //these next few lines are optional if I get the above to work

 // Other useful HX711 methods
//  rawData = myScale.get_value(SAMPLES);// returns raw loadcell reading minus offset
//  offset = myScale.get_offset(); // returns the offset set by tare ();
//  calibration = myScale.get_scale (); // returns the cal_factor used by set_scale ();