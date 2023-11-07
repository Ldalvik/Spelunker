#pragma once
#include <TFT_eSPI.h>

typedef struct TextBox {
  uint8_t datum;
  int color;
  int paddingColor;
  int padding;
  int x;
  int y;
  uint8_t size;
  uint8_t font;
  const char *text;
};

TextBox BaseTextBox() {
  struct TextBox baseTextBox;
  baseTextBox.datum = TL_DATUM;
  baseTextBox.color = TFT_WHITE;
  baseTextBox.paddingColor = TFT_BLACK;
  baseTextBox.padding = 50;
  baseTextBox.x = 0;
  baseTextBox.y = 0;
  baseTextBox.size = 3;
  baseTextBox.font = 1;
  baseTextBox.text = "default";
  return baseTextBox;
};

TextBox BaseButton() {
  struct TextBox baseButton;
  baseButton.datum = MC_DATUM;
  baseButton.color = TFT_BLACK;
  baseButton.paddingColor = TFT_WHITE;
  baseButton.padding = 350;
  baseButton.x = 0;
  baseButton.y = 0;
  baseButton.size = 4;
  baseButton.font = 1;
  baseButton.text = "default";
  return baseButton;
};

enum GameScreen {
  MAINSCREEN,
  MARKETPLACE,
  UPGRADESHOP,
  TRADER
};

void update(TFT_eSPI &lcd, TextBox textBox) {
  lcd.setTextDatum(textBox.datum);
  lcd.setTextColor(textBox.color, textBox.paddingColor);
  lcd.setTextPadding(textBox.padding);
  lcd.setTextSize(textBox.size);

  lcd.drawString(textBox.text, textBox.x, textBox.y, textBox.font);
}

void setText(TextBox &textBox, const char *item, int amount) {
    char buffer[70];
    sprintf(buffer, "%s%d", item, amount);
    textBox.text = strdup(buffer);
}

void setInventoryText(TFT_eSPI &lcd, TextBox &textBox, char *item, int amount, int x, int y, int color = TFT_WHITE, int size = 3) {
  textBox = BaseTextBox();
  textBox.x = x;
  textBox.y = y;
  textBox.color = color;
  textBox.size = size;
  setText(textBox, item, amount);
  update(lcd, textBox);
}
