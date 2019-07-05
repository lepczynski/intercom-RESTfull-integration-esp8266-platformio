#include "FS.h"

#define STA_SSID "SSID"
#define STA_passphrase "passphrase"

void setup(){
	Serial.begin(115200);

	// SPIFFSConfig cfg;
	// cfg.setAutoFormat(false);
	// SPIFFS.setConfig(cfg);

	SPIFFS.begin();


	File file = SPIFFS.open("/properties.txt", "r");
	if (!file) {
    	Serial.println("file open failed");
	} else {
		String data = file.readStringUntil('#');
		Serial.println("/properties.txt:");
		Serial.println(data);
		Serial.println("====end of file====");
		Serial.print("File size is: ");
		Serial.println(file.size());
	}

	Serial.println("====== Writing to SPIFFS file =========");
	// write 10 strings to file
	File f=SPIFFS.open("log.txt", "a");
	for (int i=1; i<=3; i++) {
		f.print("Millis() : ");
		f.println(millis());
	}
	f.close();
	f=SPIFFS.open("log.txt", "r");
	if (!f) {
    	Serial.println("log file open failed !");
	} else {
		String data = f.readStringUntil('#');
		Serial.println("/log.txt:");
		Serial.println(data);
		Serial.println("====end of file====");
		Serial.print("File size is: ");
		Serial.println(f.size());
	}
	f.close();


	file.close();
	SPIFFS.end();

}

void loop(){
	return;
}