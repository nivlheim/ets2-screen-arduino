#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ArduinoJson.h>

// Software SPI (slower updates, more flexible pin options):
// pin 3 - Serial clock out (SCLK)
// pin 4 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 7 - LCD chip select (CS)
// pin 6 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);

#define PROGRESSBAR_HEIGHT 5

int fuelParams[] = {0,0};

void setup()   {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  Serial.setTimeout(100);
  
  display.begin();
  display.setContrast(50);
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(BLACK);
}


void loop() {
  digitalWrite(13, HIGH);
  display.clearDisplay();
  drawFuelScreen();
  display.display();
}

void drawFuelScreen(){
  drawScreenTitle("Paliwo");
  display.print(fuelParams[0], DEC);
  display.print("/");
  display.print(fuelParams[1], DEC);
  display.print(" litrow");
  drawProgressbar(20, fuelParams[0], fuelParams[1]);
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

  fuelParams[0] = root["fuel"]["current"];
  fuelParams[1] = root["fuel"]["max"];
}

