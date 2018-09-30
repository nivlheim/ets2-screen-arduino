#include "guiElements.h"

void drawFuelScreen(Adafruit_PCD8544& display, telemetryDataStruct& telemetryData){
  const int currentFuel = telemetryData.fuel.current;
  const int maxFuel = telemetryData.fuel.max;
  drawScreenTitle(display, "Paliwo");
  display.print(currentFuel, DEC);
  display.print("/");
  display.print(maxFuel, DEC);
  display.print(" litrow");
  drawProgressbar(display, 20, currentFuel, maxFuel);
}
