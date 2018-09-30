void drawScreenTitle(Adafruit_PCD8544& display, String title){
  display.fillRect(0, 0, 84, 9, BLACK);
  display.setCursor(1,1);
  display.setTextColor(WHITE, BLACK);
  display.print(title);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0,11);
}

void drawProgressbar(Adafruit_PCD8544& display, int yOffset, int value, int rangeMax) {
  const int PROGRESSBAR_HEIGHT = 5;
  int realValue = map(value, 0, rangeMax, 0, 82);
  display.drawRect(0, yOffset, 84, PROGRESSBAR_HEIGHT, BLACK);
  if(realValue > 0) {
    display.fillRect(1, yOffset + 1, realValue, PROGRESSBAR_HEIGHT - 2, BLACK);
  }
}
