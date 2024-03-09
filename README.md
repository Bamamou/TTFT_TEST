## TFT TEST with DHT11 and ESP32
+ This require the below libraries
1.  Adafruit_sensos.h: For Adafruit sensors families
2.  DHT.h  : For the DHT sensor
1. Adafruit_GFX.h : for the TFT Display (software)
1. Adafruit_ILI9341.h : For the TFT Display (Hardware)
1. SPI.h
- It also requires other files related to the frames and the simulator.
1. frame.h 
1. Wokwi.toml : for the simulator bin and elf file
2. diagram.json : For the diagram of the components and the micro controller.
### Pin layout
+ DHT <br>
SDA---->GPIO12 <br>
GND---->GND  <br>
VCC----->VIN
- TFT_ILI9341 <br>
MOSI----->GPIO23 <br>
MISO----->GPIO19 <br>
CS-------->GPIO5 <br>
SCK------->GPIO18 <br>
VCC ------>VIN <br>
GND------->GND <br>
RST------->GPIO21 <br>
D/C------->GPIO4 <br>