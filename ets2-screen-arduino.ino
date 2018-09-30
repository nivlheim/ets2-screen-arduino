#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ArduinoJson.h>

#include "telemetry.h"
#include "screens.h"

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
  
  if(telemetryData.engine.enabled) {
    digitalWrite(13, HIGH);
    drawFuelScreen(display, telemetryData);
  } else {
    digitalWrite(13, LOW);
  }
  
  display.display();
}

void serialEvent(){
  StaticJsonBuffer<512> jsonBuffer;
  String inputMessage = Serial.readString();
  JsonObject& root = jsonBuffer.parseObject(inputMessage);
  saveTelemetryData(telemetryData, root);
}

