#pragma once
#include <TFT_eSPI.h>

void Lcd_Init(TFT_eSPI &lcd, uint8_t brightness = 255);
void Lcd_Standby(TFT_eSPI &lcd, uint8_t max_brightness = 255);

/* Displays a random color for 4 seconds, then fades in and out for (max_brightness * 2) ms */
void Lcd_Standby(TFT_eSPI &lcd, uint8_t max_brightness) {
  for (uint8_t i = max_brightness; i > 0; i--) {
    ledcWrite(7, i);
    delay(1);
  }
  lcd.fillScreen(random(0x10000));

  for (uint8_t i = 0; i < max_brightness; i++) {
    ledcWrite(7, i);
    delay(1);
  }
  delay(4000);
}

/* Initialize the display and backlight, optional brightness level to lower ambient light/conserve battery */
void Lcd_Init(TFT_eSPI &lcd, uint8_t brightness) {
  // Backlight config
  int pin = 48,
      channel = 7,
      frequency = 44100,
      resolution = 8;

  pinMode(pin, OUTPUT);                       // Set pin mode to  output
  ledcSetup(channel, frequency, resolution);  // Set the PWM channel frequency and max resolution
  ledcAttachPin(pin, channel);                // Attach the channel to a PWM pin
  ledcWrite(channel, brightness);             // Set below 255 to lower ambient light or conserve battery

  // TFT_eSPI setup
  lcd.init();
  lcd.fillScreen(TFT_BLACK);
  lcd.setRotation(1);
}