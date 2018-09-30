#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ArduinoJson.h>

#include "lib/telemetry.h"

// pin 3 - Serial clock out (SCLK)
// pin 4 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 7 - LCD chip select (CS)
// pin 6 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);
telemetryDataStruct telemetryData;

void setup()   {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(100);
  
  display.begin();
  display.setContrast(50);
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(BLACK);
}

void loop() {
  display.clearDisplay();
  if(telemetryData.engineEnabled) {
    digitalWrite(13, HIGH);
    drawFuelScreen();
  } else {
    digitalWrite(13, LOW);
  }
  
  display.display();
}

void drawFuelScreen(){
  const int currentFuel = telemetryData.fuel.current;
  const int maxFuel = telemetryData.fuel.max;
  drawScreenTitle("Paliwo");
  display.print(currentFuel, DEC);
  display.print("/");
  display.print(maxFuel, DEC);
  display.print(" litrow");
  drawProgressbar(20, currentFuel, maxFuel);
}

void drawScreenTitle(String title){
  display.fillRect(0, 0, 84, 9, BLACK);
  display.setCursor(1,1);
  display.setTextColor(WHITE, BLACK);
  display.print(title);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0,11);
}

void drawProgressbar(int yOffset, int value, int rangeMax) {
  const int PROGRESSBAR_HEIGHT = 5;
  int realValue = map(value, 0, rangeMax, 0, 82);
  display.drawRect(0, yOffset, 84, PROGRESSBAR_HEIGHT, BLACK);
  if(realValue > 0) {
    display.fillRect(1, yOffset + 1, realValue, PROGRESSBAR_HEIGHT - 2, BLACK);
  }
}

void serialEvent(){
  StaticJsonBuffer<200> jsonBuffer;
  String inputMessage = Serial.readString();
  JsonObject& root = jsonBuffer.parseObject(inputMessage);
  saveTelemetryData(telemetryData, root);
}

