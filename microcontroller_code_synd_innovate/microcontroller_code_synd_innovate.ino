
#include <ESP8266WiFi.h>
  #include <FirebaseArduino.h>

#define sensor A0;
#define FIREBASE_HOST "deepblue-cab89.firebaseio.com"
#define FIREBASE_AUTH "xtZQJiddqcdlM7GHLz39VDxcGFgbHFJryikYZj2h"
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "12345679"

WiFiClient client;

String MakerIFTTT_Key ;
; String MakerIFTTT_Event;
char *append_str(char *here, String s) {
  int i = 0;
  while (*here++ = s[i]) {
    i++;
  };
  return here - 1;
}
char *append_ul(char *here, unsigned long u) {
  char buf[20];
  return append_str(here, ultoa(u, buf, 10));
}
char post_rqst[256]; char *p; char *content_length_here; char *json_start; int compi;

// defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

// defines variablesx
long duration;
int distance;
int sensorValue;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
int sensorValue;
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(2000);

  // append a new value to /logs
  int uname1 = Firebase.getInt("Profile/kush/threshold1");
//  Firebase.setInt("Profile/kush/Dustbin", distance);
  if(distance < uname1 && distance != 0){
  
 if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
    if (client.connect("maker.ifttt.com", 80)) {
    MakerIFTTT_Key = "b9pSYCQqNJAHulm-Wd4VKF";
    MakerIFTTT_Event = "sms";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "ADD_MOBILE_NO");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "Dustbin full");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "");
    p = append_str(p, "\"}");

    compi = strlen(json_start);
    content_length_here[0] = '0' + (compi / 10);
    content_length_here[1] = '0' + (compi % 10);
    client.print(post_rqst);}
  delay(1000);
}

sensorValue = analogRead(A0);       // read analog input pin 0
//Serial.print("AirQuality=");
//Serial.print(sensorValue);
//Serial.println("");
//delay(1000); 
int uname = Firebase.getInt("Profile/kush/threshold");
Firebase.setInt("Profile/kush/Air quality", sensorValue);
if(sensorValue > uname){


  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
    if (client.connect("maker.ifttt.com", 80)) {
    MakerIFTTT_Key = "b9pSYCQqNJAHulm-Wd4VKF";
    MakerIFTTT_Event = "sms";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;  
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "ADD_MOBILE_NO");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "Air quality is poor");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "");
    p = append_str(p, "\"}");

    compi = strlen(json_start);
    content_length_here[0] = '0' + (compi / 10);
    content_length_here[1] = '0' + (compi % 10);
    client.print(post_rqst);}
  delay(4000);
}
}
