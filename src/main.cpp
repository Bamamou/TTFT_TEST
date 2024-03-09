#include "SPI.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include "frame.h"
#include <DHT.h>

//Instantiate both the DHT sensor and the Display
DHT dht(DHT_Pin, DHT22);  // Instantiate a dht element from the DHT object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup() {
  tft.begin();
  pinMode(DHT_Pin, INPUT);
  tft.invertDisplay(false);    // Do not invert the colors of the display
  tft.setRotation(1);          // Rotate the display
  Serial.begin(115200);
}

void loop() {
  nowTemp   = dht.readTemperature(false);                //temperature from the dht
  nowHumid  = dht.readHumidity();                       //humidity from the dht
  tft.setTextColor(ILI9341_WHITE);
  // Battery icon
  tft.fillRect(290, 12, 15, 13, ILI9341_RED);
  tft.drawBitmap(285, 2, frames1[frame1], FRAME_WIDTH, FRAME_HEIGHT, ILI9341_WHITE);
  frame1 = (frame1 + 1) % FRAME_COUNT1;
  // Weather icon
  tft.fillRect(95, 0, 40, 35, ILI9341_BLACK);
  if (nowTemp > 0 && nowTemp < 50)
  {
    tft.drawBitmap(100, 0, frames2[frame2], FRAME_WIDTH, FRAME_HEIGHT, ILI9341_YELLOW);
    frame2 = (frame2 + 4) % FRAME_COUNT2;
  }

  else if (nowTemp >= 50)
  {
    tft.drawBitmap(100, 0, frames5[frame5], FRAME_WIDTH, FRAME_HEIGHT, ILI9341_RED);
    frame5 = (frame5 + 4) % FRAME_COUNT5;
  }
  else
  {
    tft.drawBitmap(100, 0, frames4[frame4], FRAME_WIDTH, FRAME_HEIGHT, ILI9341_WHITE);
    frame4 = (frame4 + 4) % FRAME_COUNT4;
  }

  // Network icon
  tft.fillRect(0, 0, 35, 30, ILI9341_BLACK);
  tft.drawBitmap(1, 0, frames3[frame3], FRAME_WIDTH, FRAME_HEIGHT, ILI9341_WHITE);
  frame3 = (frame3 + 1) % FRAME_COUNT3;
// DHT compute heat Index in percentage
  if ((humidity != nowHumid) || (temperature != nowTemp)) {
    tft.fillRect(0, 60, 300, 40, ILI9341_BLACK);
    tft.setTextSize(0.8);
    tft.setCursor(0, 80);
    tft.print("Heat Index: " + String(dht.computeHeatIndex((temperature, humidity, false)))+ "%");
  }

  // Extract the temperature value in C and in K
  if (temperature != nowTemp) {
    tft.fillRect(0, 100, 300, 40, ILI9341_BLACK);
    tft.setFont(&FreeMonoBoldOblique12pt7b);

    if (nowTemp >= 50)
    {
      tft.setTextColor(ILI9341_RED);
    }
    else if (nowTemp <= 0)
    {
      tft.setTextColor(ILI9341_BLUE);
    }
    tft.setTextSize(0.8);
    tft.setCursor(0, 120);
    tft.print("Temperature: " + String(nowTemp) + "C"); //Draw new time
    //Convert that temp from C to K and display
    tft.fillRect(0, 140, 300, 40, ILI9341_BLACK);
    tft.setTextSize(0.8);
    tft.setCursor(0, 160);
    tft.print("Temperature: " + String(nowTemp + 273.15) + "K"); //Draw new time
    temperature = nowTemp;
  }
// Extract and display Humidity in Percentage
  if (humidity != nowHumid) {
    tft.fillRect(0, 180, 300, 40, ILI9341_BLACK);
    tft.setFont(&FreeMonoBoldOblique12pt7b);

    if (nowHumid >= 50)
    {
      tft.setTextColor(ILI9341_RED);
    }

    tft.setTextSize(0.8);
    tft.setCursor(0, 200);
    tft.print("Humidity: " + String(nowHumid) + "%"); //Draw new time
    humidity = nowHumid;
  }

  delay(250);
}

