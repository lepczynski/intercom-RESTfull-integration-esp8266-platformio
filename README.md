# intercom-integration-esp8266-platformio
A tiny RESTfull API for opening an old intercom that has to emulate reciever pick-up and after setupable delay closing the physical gate circuit.


# ToDo:
## NECESSARY:
-~~make a fritzing schematic~~  
-~~find out the current going through the phycisal gate circuit when opening the gate~~  
-~~post photos of the intercom circuit~~ 
-json config load (arduinoJson6)  
-if that doesn't work - fallback to either arduinoJson5 or line parsing a text file  
-create a user at my http server for OTA
-OTA  

## AFTER 1st working version:  
-HTTPS letsenrypt → for PUT on /config
-multi WiFi credentials  
-GitLab CI/CD integration (Docker)  
-Authentication for sensitive endpoints (or all? - configurable)


# REST End-points:
- GET: /open or /o  > get method for easier cli integration like so: ```curl 192.168.1.101/open```  
- GET: /health  or /h  
- PUT: /delay_ms?t=500  
- PUT: /pulse_length_ms?t=500  
- GET: /restart  
- PUT: /OTA/address?a="http://lepi.pl/OTA/RPLUS-intercom"  
- GET: /OTA/reload > check for updates at address  
- GET: /config → json with config but only https and with AUTHENTICATION


# BOM:
- resistors: 2x 1kohm [min.500ohm (over 1kohm doesn't close the relay)  (12mA per pin on Wemos)]  
- transistors: 2x CTBC 547B JS (I hope they're not running JavaScript xD)  
- 2x relay RZ2 G4,5 ITT West Germany  (>29 yrs old)  
- micro-usb power supply  
