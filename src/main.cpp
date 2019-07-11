#include "FS.h"

#define PIN_PHONE_OUT 2 // D4
#define PIN_PHONE_IN 0 // D3
#define PIN_DOOR_OUT 4 // D2

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server;

// #define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

void(*reset)( void ) = 0; // reboot function

void openDoor();
void health();

StaticJsonDocument<600> config;

bool offlineMode = false;
bool phoneUp = false;

void setup(){
    Serial.begin(115200);
    Serial.print("Serial on @ 115200");

    // Serial.println("Turning off SPIFFS autoformat...");
    // SPIFFSConfig cfg;
    // cfg.setAutoFormat(false);
    // SPIFFS.setConfig(cfg);

    Serial.println("Mounting SPIFFS file system...");
    SPIFFS.begin();

    Serial.println("Opening properties.json file...");
    File propertiesFile = SPIFFS.open("/properties.json", "r");

    if (!propertiesFile) {
        Serial.println("file opening failed!");
    } else {
        size_t propertiesSize = propertiesFile.size();
        Serial.print("Property file size: ");
        Serial.println(propertiesSize);

        // arduinojson5 ?
        // std::unique_ptr<char[]> buf(new char[propertiesSize]);

        // Serial.println("Reading the file into a buffer");
        // propertiesFile.readBytes(buf.get(), propertiesSize);
        // Serial.println("Buffer read.");
        // Serial.println(buf.get());

        // Attempt deserializing json
        DeserializationError error = deserializeJson( config, propertiesFile );
        if( error ) {
            Serial.print("ERROR: Failed to parse properties: ");
            Serial.println( error.c_str() );
            // toDo: wire up some defaults
            Serial.println("FATAL ERROR: No config! :<\nHere be dragons !");
        }

    }

    // char ssid[32] = "";
    // serializeJson(config['SSID'], ssid);
    auto ssid = config["SSID"].as<char*>();
    
    Serial.print("auto .as<char*> ssid: ");
    Serial.println(ssid);
    Serial.println();
    Serial.println();


    char passphrase[64] = ""; //config['passphrase'];
    serializeJson(config['passphrase'], passphrase);

    char hostname[64] = ""; // config['hostname'];
    serializeJson(config['hostname'], hostname);

    int wifiMaxConnectionTrials = 20;
    serializeJson(config['wifiMaxConnectionTrials'], &wifiMaxConnectionTrials);

    propertiesFile.close();
    SPIFFS.end();

    // Connect

    Serial.println("WiFi setting Station mode...");
    WiFi.mode(WIFI_STA);
    
    Serial.print("WiFi hostname: ");
    Serial.println(hostname);
    WiFi.hostname(hostname);
    
    Serial.print("WiFi SSID: ");
    Serial.println(ssid);
    
    Serial.print(" WiFi pass: ");
    // Serial.println(config['passphrase'].as<String>());
    Serial.println(passphrase);
    
    Serial.print("Connecting");
    // WiFi.config(ip, dns, gateway, subnet_mask);
    WiFi.begin( ssid, passphrase);

    int connectionTrials = 0;

    while(WiFi.status()!=WL_CONNECTED && connectionTrials < wifiMaxConnectionTrials){
        Serial.print(".");
        connectionTrials++;
        delay(333);
    }

    if(WiFi.status()!=WL_CONNECTED) {
        Serial.print("Failed connecting to WiFi, entering offline mode");

        // toDo: implement offline mode
    }

    Serial.println();
    Serial.println("V0.04");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());



    pinMode(PIN_DOOR_OUT, OUTPUT);

    pinMode(PIN_PHONE_IN, INPUT_PULLUP); // INPUT_PULLDOWN);
    pinMode(PIN_PHONE_OUT, OUTPUT);

    server.on("/o", openDoor);
    server.on("/h", health);
    server.begin();

    digitalWrite(PIN_DOOR_OUT, false);
    digitalWrite(PIN_PHONE_OUT, false);

}


void loop(){

    phoneUp = digitalRead(PIN_PHONE_IN);

    if(!offlineMode) {
        server.handleClient();
    }

    
    if(phoneUp) {  // If the phone is picked up - close the circuit
        digitalWrite(PIN_PHONE_OUT, true);
    } else {
        digitalWrite(PIN_PHONE_OUT, false);
    }

    if(Serial.available()) {
        char incoming = Serial.read();
        // Serial.print("[");
        // Serial.print(incoming);
        // Serial.print("]");
        if(incoming=='o') {
            openDoor();
        } else if(incoming=='h') {
            health();
        }
    }

}

void health(){
        Serial.println();
        Serial.println("Health ok!");
        server.send(200, "text/plain", "Health ok!\n");
}

void openDoor(){
    bool phone = digitalRead(PIN_PHONE_IN);

    if(phone) {
        Serial.println("Picking up the phone...");
        digitalWrite(PIN_PHONE_OUT, true);
        delay(500);

        Serial.println("Opening the gate for 2,5s...");
        digitalWrite(PIN_DOOR_OUT, true);
        delay(2500);

        Serial.println("Closing the gate...");
        digitalWrite(PIN_DOOR_OUT, false);

        Serial.println("Hangin' up....");
        digitalWrite(PIN_PHONE_OUT, false);


        server.send(200, "text/plain", "Gate successfully opened!\n");


    } else {
        Serial.println("The phone is up, ABORTING !");
        server.send(409, "text/plain", "The phone is up, ABORTING !\n");
    }
}
