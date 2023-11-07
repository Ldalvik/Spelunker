#include <TFT_eSPI.h>
#include "GameConfig.h"
#include "GameUtils.h"
#include "TextUtils.h"
#include "LcdUtils.h"

struct TextBox upgradeBtn;
struct TextBox traderBtn;

struct TextBox stoneTextBox;
struct TextBox coalTextBox;
struct TextBox ironTextBox;
struct TextBox goldTextBox;
struct TextBox diamondsTextBox;
struct TextBox moneyTextBox;

int CURRENT_SCREEN = MAINSCREEN;

hw_timer_t *miner = NULL;

void IRAM_ATTR MinerTask() {
  switch (getOre(GameData.upgrades.pickaxeType)) {
    case STONE:
      GameData.inventory.stone++;
      break;
    case COAL:
      GameData.inventory.coal++;
      break;
    case IRON:
      GameData.inventory.iron++;
      break;
    case GOLD:
      GameData.inventory.gold++;
      break;
    case DIAMOND:
      GameData.inventory.diamonds++;
      break;
  }
}

TFT_eSPI lcd = TFT_eSPI();

void setup() {
  Serial.begin(115200);

  miner = timerBegin(0, 80, true);
  timerAttachInterrupt(miner, &MinerTask, true);
  timerAlarmWrite(miner, GameConfig.MiningInterval, true);
  timerAlarmEnable(miner);

  Lcd_Init(lcd);
  //lcd.fillScreen(random(0x10000));
  //Draw_ShopBtns();
}

long lastMillis = 0;
void loop() {
  if (millis() - lastMillis >= GameConfig.LcdUpdateFreq) {
    switch (CURRENT_SCREEN) {
      case MAINSCREEN:
        {
          drawMainScreen();
        }
        break;
      case MARKETPLACE:
        {
          Draw_ShopBtns();
        }
        break;
      case UPGRADESHOP:
        {
        }
        break;
      case TRADER:
        {
        }
        break;
    }
    lastMillis = millis();
  }
}

void drawMainScreen() {
  setInventoryText(lcd, stoneTextBox, "Stone:    ", GameData.inventory.stone, 10, 10);
  setInventoryText(lcd, coalTextBox, "Coal:     ", GameData.inventory.coal, 10, 60);
  setInventoryText(lcd, ironTextBox, "Iron:     ", GameData.inventory.iron, 10, 110);
  setInventoryText(lcd, goldTextBox, "Gold:     ", GameData.inventory.gold, 10, 160, TFT_YELLOW);
  setInventoryText(lcd, diamondsTextBox, "Diamonds: ", GameData.inventory.diamonds, 10, 210, TFT_CYAN);

  setInventoryText(lcd, moneyTextBox, "$", GameData.money, 10, 285, TFT_GREEN, 4);
}

void Draw_ShopBtns() {
  // ------------------
  // |  Upgrade Shop  |
  // ------------------
  // |     Trader     |
  // ------------------
  upgradeBtn = BaseButton();
  upgradeBtn.x = lcd.width() / 2;
  upgradeBtn.y = 120;
  upgradeBtn.text = "Upgrade Shop";
  update(lcd, upgradeBtn);

  traderBtn = BaseButton();
  traderBtn.x = lcd.width() / 2;
  traderBtn.y = 200;
  traderBtn.text = "Trader";
  update(lcd, traderBtn);
}
