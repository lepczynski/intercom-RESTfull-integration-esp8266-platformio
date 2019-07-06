import usocket as socket

from machine import Pin
import network
from time import sleep

import gc
gc.collect()

ssid = 'nbrmc'
password = 'x98Xf82FbegihGumbbZS'

station = network.WLAN(network.STA_IF)

station.active(True)
station.connect(ssid, password)

while station.isconnected() == False:
  pass

print('Connection successful')
print(station.ifconfig())

switch = Pin(2, Pin.OUT)
