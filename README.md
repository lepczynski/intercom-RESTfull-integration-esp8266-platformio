# intercom-integration-esp8266-platformio
A tiny RESTfull API for opening an old intercom that has to emulate reciever pick-up and after setupable delay closing the physical gate circuit.


#Already found-out:

-intercom has a all-time 9V supply lines  
-[SSR relay datasheet](https://omronfs.omron.com/en_US/ecb/products/pdf/en-g3mc.pdf) (I got the and they're small - if I'll need I'll swap that for a mechanical one, the goal is so that it is small enough to put it into the oryginal intercom case

#ToDo:

-make a fritzing schematic  
-find out the current going through the phycisal gate circuit when opening the gate  
-add platformio code  
-add dockerization or sth other aiming for the average computer-user friendliness level  
-post photos of the intercom circuit and case  

#Details:

- $MCU_IP_ADDRESS/open  
- $MCU_IP_ADDRESS/health  
- $MCU_IP_ADDRESS/delay_ms?t=500  
