#include <JC3248W535EN-Touch-LCD.h>

JC3248W535EN screen;

uint16_t touchX, touchY;

void setup() {
  Serial.begin(115200);

  // Initialize the screen
  if (!screen.begin()) {
    Serial.println("Screen initialization failed!");
    return;
  }
  screen.clear(255, 255, 255);
  screen.drawQRCode("https://google.com", 0, 0, 5, 255, 255, 255, 0, 0, 0);
}
void loop() {
}
