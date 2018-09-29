#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 3 - Serial clock out (SCLK)
// pin 4 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 7 - LCD chip select (CS)
// pin 6 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);

#define PROGRESSBAR_HEIGHT 10

String lastMessage = "1,1";

void setup()   {
  Serial.begin(9600);
  Serial.setTimeout(100);
  display.begin();

  display.setContrast(60);
  display.setRotation(2);
  
  // text display tests
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
}


void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(lastMessage);

  int delimeterIndex = lastMessage.indexOf('/');
  int firstVal = lastMessage.substring(0,delimeterIndex).toInt();
  int secondVal = lastMessage.substring(delimeterIndex + 1).toInt();
  drawProgressbar(30, firstVal, secondVal);
  display.display();
}

void drawProgressbar(int y, int value, int rangeMax) {
  int realValue = map(value, 0, rangeMax, 0, 82);
  display.println(realValue);
  display.drawRect(0, y, 84, PROGRESSBAR_HEIGHT, BLACK);
  if(realValue > 0) {
    display.fillRect(1, y + 1, realValue, PROGRESSBAR_HEIGHT - 2, BLACK);
  }
}

void serialEvent(){
  lastMessage = Serial.readString();
}

void drawFuelScreen(){
  display.setTextColor(WHITE, BLACK);
  display.println("Paliwo");
}

