#pragma once

#include "GameUtils.h"

struct _GameConfig {
  int MiningInterval = 1000000;  // us
  int LcdUpdateFreq = 1000;      // ms
};

struct _GameData {
  int money = 0;

  struct {
    int stone = 0;
    int coal = 0;
    int iron = 0;
    int gold = 0;
    int diamonds = 0;
  } inventory;

  struct {
      PickaxeType pickaxeType = WOODEN_PICK;
      int efficiencyLvl = 0;
      int fortuneLvl = 0;
    } upgrades;
};

inline _GameConfig GameConfig;
inline _GameData GameData;
