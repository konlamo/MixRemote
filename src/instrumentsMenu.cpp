#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <AiEsp32RotaryEncoder.h>

#include <constants.h>

TFT_eSPI tft = TFT_eSPI();



void drawVolumeBar() {
  // Clear old bar area first so shrinking the value doesn't leave old pixels
  tft.fillRect(10, 30, 220, 25, TFT_BLACK);
  tft.fillRect(10, 30, map(volume, 0, 100, 0, 220), 25, TFT_GREEN);

  tft.setCursor(50, 100);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.print("Value: ");
  tft.println(volume);
  tft.setCursor(50, 140);
  tft.print("clicked: ");
  tft.println(clicked);
}



// rotary volume refresh loop:

  // if (rotaryEncoder.encoderChanged()) {
  //   volume = rotaryEncoder.readEncoder();
  //   Serial.print("Value: ");
  //   Serial.println(volume);
  //   drawVolumeBar();
  // }

  // if (rotaryEncoder.isEncoderButtonClicked()) {
  //   clicked += 1;
  //   Serial.print("Clicked: ");
  //   Serial.println(clicked);
  //   drawVolumeBar();
  // }