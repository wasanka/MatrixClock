
//We always have to include the library
#include "LedControl.h"
#include "Dht11.h"
#include<stdlib.h>


#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(16,5,4,4); 

#define DHTPIN 14
//#define DHTTYPE DHT11

//DHT dht(DHTPIN, DHTTYPE,15);

static char fahrenheitTemp[7];
static char humidityTemp[7];

int h = 0;
int t = 0;
String forcastDescription = "Not Loaded Yet!";
String outsideTemperature = "";
String outsideTemperatureLow = "";
String outsideTemperatureHigh = "";
String outsideHumidity = "";
String dateTime = "";

int speakerPin = 2;
int ledPin = 12;
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

const char* ssid     = "Neptune";
const char* password = "Datamini!2345";


// 
// http://www.pial.net/8x8-dot-matrix-font-generator-based-on-javascript-and-html/


void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin(115200);
  for(int row=0;row<4;row++) {
    lc.shutdown(row,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(row,1);
    /* and clear the display */
    lc.clearDisplay(row);
  }
//  dht.begin();

  pinMode(speakerPin, OUTPUT);   
  //march();

  connectToWIFI();
  loadDateTime();
}

// http://api.timezonedb.com/v2/get-time-zone?key=930VYQUQGHVN&format=json&by=zone&zone=America/New_York

void loadDateTime(){

  // WiFiFlientSecure for SSL/TLS support
  WiFiClient client;

  const char* host    =  "api.timezonedb.com";
  const int port  = 80;
  String resource = "/v2/get-time-zone?key=930VYQUQGHVN&format=json&by=zone&zone=America/New_York";

  if (! client.connect(host, port)) {
    //debug("Connection failed. Halting execution.");
    lc.print("WD Failed");
  }

  // This will send the request to the server
  client.print(String("GET ") + resource + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      lc.print(">>> WD Timeout !");
      client.stop();
      return;
    }
  }

  // Skipping response headers
  char endOfHeaders[] = "11a";

  client.setTimeout(5000);
  bool ok = client.find(endOfHeaders);

  if (!ok) {
    Serial.println("No response or invalid response!");
  }

  
  String content = "";
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    content += client.readStringUntil('\r');
    
  }

  Serial.println(content);
  
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(content);

//  for (JsonObject::iterator it=root.begin(); it!=root.end(); ++it)
//  {
//    Serial.println(it->key);
//    Serial.println(it->value.asString());
//  }

  dateTime = root["formatted"].asString();
  dateTime = dateTime.substring(0, 16);
  Serial.println("--"+dateTime+"--");
}

void loadData(){

  // WiFiFlientSecure for SSL/TLS support
  WiFiClient client;

  const char* host    =  "api.openweathermap.org";
  const int port  = 80;
  String resource = "/data/2.5/weather?q=Livingston,nj&appid=ff10c2711d857a0819c830c2ddba4bf0&units=imperial";

  if (! client.connect(host, port)) {
    //debug("Connection failed. Halting execution.");
    lc.print("WD Failed");
  }

  // This will send the request to the server
  client.print(String("GET ") + resource + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      lc.print(">>> WD Timeout !");
      client.stop();
      return;
    }
  }

  // Skipping response headers
  char endOfHeaders[] = "\r\n\r\n";

  client.setTimeout(5000);
  bool ok = client.find(endOfHeaders);

  if (!ok) {
    Serial.println("No response or invalid response!");
  }

  
  String content = "";
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    content += client.readStringUntil('\r');
    
  }

  Serial.print(content);
  
//  debug("---"+content+"---");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(content);

  //JsonObject& weather = root["weather"];

  forcastDescription = root["weather"][0]["description"].asString();
  outsideTemperature = root["main"]["temp"].asString();
  outsideTemperatureLow = root["main"]["temp_min"].asString();
  outsideTemperatureHigh = root["main"]["temp_max"].asString();
  outsideHumidity = root["main"]["humidity"].asString();
}

boolean connectToWIFI(){

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    Serial.print(".");
  }

  return true;
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ 
    digitalWrite(ledPin, HIGH);   
    //use led to visualize the notes being played
    
    int x;   
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)   
    {    
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    }    
    
    digitalWrite(ledPin, LOW);
    //set led back to low
    
    delay(20);
    //a little delay to make all notes sound separate
}    

void sayonara(){

  beep(speakerPin, a, 500);
  beep(speakerPin, a, 500);
  beep(speakerPin, g, 500);
  beep(speakerPin, f, 1500);

  beep(speakerPin, a, 500);
  beep(speakerPin, a, 500);
  beep(speakerPin, g, 500);
  beep(speakerPin, f, 1500);

  beep(speakerPin, a, 500);
  beep(speakerPin, b, 500);
  beep(speakerPin, c, 500);

  beep(speakerPin, c, 500);
  beep(speakerPin, b, 250);
  beep(speakerPin, a, 250);
  beep(speakerPin, b, 500);

  beep(speakerPin, g, 500);
  beep(speakerPin, a, 500);
  beep(speakerPin, b, 500);

  beep(speakerPin, b, 500);
  beep(speakerPin, a, 250);
  beep(speakerPin, g, 250);
  beep(speakerPin, a, 500);

  beep(speakerPin, a, 500);
  beep(speakerPin, a, 500);
  beep(speakerPin, b, 500);
  beep(speakerPin, cH, 1500);

  beep(speakerPin, a, 500);
  beep(speakerPin, a, 500);
  beep(speakerPin, g, 500);
  beep(speakerPin, f, 1500);
}

void march()
{    
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note
    
    beep(speakerPin, a, 500); 
    beep(speakerPin, a, 500);     
    beep(speakerPin, a, 500); 
    beep(speakerPin, f, 350); 
    beep(speakerPin, cH, 150);
    
    beep(speakerPin, a, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);
    //first bit
    
    beep(speakerPin, eH, 500);
    beep(speakerPin, eH, 500);
    beep(speakerPin, eH, 500);    
    beep(speakerPin, fH, 350); 
    beep(speakerPin, cH, 150);
    
    beep(speakerPin, gS, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);
    //second bit...
    
    beep(speakerPin, aH, 500);
    beep(speakerPin, a, 350); 
    beep(speakerPin, a, 150);
    beep(speakerPin, aH, 500);
    beep(speakerPin, gSH, 250); 
    beep(speakerPin, gH, 250);
    
    beep(speakerPin, fSH, 125);
    beep(speakerPin, fH, 125);    
    beep(speakerPin, fSH, 250);
    delay(250);
    beep(speakerPin, aS, 250);    
    beep(speakerPin, dSH, 500);  
    beep(speakerPin, dH, 250);  
    beep(speakerPin, cSH, 250);  
    //start of the interesting bit
    
    beep(speakerPin, cH, 125);  
    beep(speakerPin, b, 125);  
    beep(speakerPin, cH, 250);      
    delay(250);
    beep(speakerPin, f, 125);  
    beep(speakerPin, gS, 500);  
    beep(speakerPin, f, 375);  
    beep(speakerPin, a, 125); 
    
    beep(speakerPin, cH, 500); 
    beep(speakerPin, a, 375);  
    beep(speakerPin, cH, 125); 
    beep(speakerPin, eH, 1000); 
    //more interesting stuff (this doesn't quite get it right somehow)
    
    beep(speakerPin, aH, 500);
    beep(speakerPin, a, 350); 
    beep(speakerPin, a, 150);
    beep(speakerPin, aH, 500);
    beep(speakerPin, gSH, 250); 
    beep(speakerPin, gH, 250);
    
    beep(speakerPin, fSH, 125);
    beep(speakerPin, fH, 125);    
    beep(speakerPin, fSH, 250);
    delay(250);
    beep(speakerPin, aS, 250);    
    beep(speakerPin, dSH, 500);  
    beep(speakerPin, dH, 250);  
    beep(speakerPin, cSH, 250);  
    //repeat... repeat
    
    beep(speakerPin, cH, 125);  
    beep(speakerPin, b, 125);  
    beep(speakerPin, cH, 250);      
    delay(250);
    beep(speakerPin, f, 250);  
    beep(speakerPin, gS, 500);  
    beep(speakerPin, f, 375);  
    beep(speakerPin, cH, 125); 
           
    beep(speakerPin, a, 500);            
    beep(speakerPin, f, 375);            
    beep(speakerPin, c, 125);            
    beep(speakerPin, a, 1000);       
    //and we're done \ó/    
}

void loop() {

  lc.print(dateTime);
  loadData();
  loadDateTime();
  
  readInsideTemperature();
  lc.print("Inside Humidity " + String(h) + "%");
  lc.print("Inside Temperature " + String(t) + "F");

  lc.print(dateTime);
  
  lc.print("Forcast : " + forcastDescription);
  lc.print("Outdoor Temperature : " + outsideTemperature + "F");
  lc.print("Outdoor Humidity : " + outsideHumidity + "%");

  lc.print(dateTime);
  
  lc.print("Outdoor Temp Low : " + outsideTemperatureLow + "F");
  lc.print("Outdoor Temp High : " + outsideTemperatureHigh + "F");

  lc.print("Birds by Nisitha Wickramasinghe.... Do you hear that?    It was a chirp!    I heard it on the patio    While you were taking a slurp....     The bird was in a tree    It had the colors red, yellow and blue    I wish I could say 'Hi!'   because I really like birds, I do!");

//
//  float h = dht.readHumidity();
//  float f = dht.readTemperature();
//  f = dht.readTemperature(true);
//            
//  if (isnan(h)) {
//    lc.print("DHT Failed!");
//  } else {
//
//    // You can delete the following lc.print's, it's just for debugging purposes
//    lc.print("Humidity: " + String(h) + "% Temperature: " + String(f) + "F") ;
//  }
  
//  lc.print("This is Nisitha's, Hasindu's & Diniru's Clock");
//  lc.print("10:10 am");
//  delay(1000);
//  lc.print("Outside Temperature...");
//  lc.print("- 38F -");
//  delay(1000);
//  //lc.print("Inside Temperature...");
//  //lc.print("- 71F -");
//  lc.print("High 41F Low 31F");
//  lc.print("10:10 am");
//  delay(1000);
//  lc.print("Today forcast: ");
//  lc.print("light rain");
//  lc.print("10:10 am");
//  delay(1000);
//  lc.print("<<<<<<<<<            ");

  
}

void readInsideTemperature(){
    static Dht11 sensor(DHTPIN);
    h = 0;
    t = 0;
    switch (sensor.read()) {
    case Dht11::OK:

        
        for(int i = 0; i < 10; i++){
          h = h + sensor.getHumidity();
          t = t + sensor.getTemperature();
        };

        h = h / 10;
        t = t / 10;

        t = (t * 18 + 5)/10 + 32;
        
        break;

    case Dht11::ERROR_CHECKSUM:
        lc.print("Checksum error");
        break;

    case Dht11::ERROR_TIMEOUT:
        lc.print("Timeout error");
        break;

    default:
        lc.print("Unknown error");
        break;
    }
}
 
    

