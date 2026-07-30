#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <AiEsp32RotaryEncoder.h>

#include <constants.h>

TFT_eSPI tft = TFT_eSPI();

#define ROTARY_ENCODER_A_PIN 33
#define ROTARY_ENCODER_B_PIN 32
#define ROTARY_ENCODER_BUTTON_PIN 25
#define ROTARY_ENCODER_VCC_PIN 21
#define ROTARY_ENCODER_STEPS 4

AiEsp32RotaryEncoder rotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN,
                                   ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN,
                                   ROTARY_ENCODER_STEPS);


void IRAM_ATTR readEncoderISR() {
  rotaryEncoder.readEncoder_ISR();
  tft.setTextSize(2);
}

void drawMenu() { // mode selector
  tft.fillRect(0, 0, 30, 300, TFT_BLACK); // clear old cursor area

  tft.setCursor(30, 75);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.println("Profiles");
  tft.setCursor(30, 150);
  tft.println("Settings (locked)");
  tft.setCursor(30, 225);
  tft.println("Instruments");
  tft.fillCircle(cursorX, (cursorY * cursorPos) + cursorR - 2, cursorR, TFT_GREEN);
}



void setup() {
  Serial.begin(115200);

  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setBoundaries(0, 100, false);
  rotaryEncoder.setAcceleration(0);

  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH); // backlight on

  tft.init();
  tft.fillScreen(TFT_BLACK);

  drawMenu();
  // tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // tft.setTextSize(2);
  // tft.setCursor(10, 10);
  // tft.println("Volume:");
  

  // drawVolumeBar(); // draw initial state


}

void loop() {
  if (menu) {
    if (rotaryEncoder.encoderChanged()) {
      if (cursorPos == 3) {
        cursorPos = 1;
      }
      else {
        cursorPos = cursorPos + 1;
      }
      drawMenu();
    }
  }

}