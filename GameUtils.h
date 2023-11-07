#pragma once

enum PickaxeType {
  WOODEN_PICK,
  STONE_PICK,
  IRON_PICK,
  GOLD_PICK,
  DIAMOND_PICK,
  NETHERACK_PICK
};

enum OreType {
  STONE,
  COAL,
  IRON,
  GOLD,
  DIAMOND
};

typedef struct {
  OreType ore;
  int weight;
} OreData;

OreData defaultTable[] = {
  { STONE, 70 },
  { COAL, 30 }
};

OreData stonePickTable[] = {
  { STONE, 65 },
  { COAL, 20 },
  { IRON, 15 }
};

OreData ironPickTable[] = {
  { STONE, 50 },
  { COAL, 20 },
  { IRON, 15 },
  { GOLD, 10 },
  { DIAMOND, 5 }
};

OreData goldPickTable[] = {
  { STONE, 45 },
  { COAL, 20 },
  { IRON, 15 },
  { GOLD, 10 },
  { DIAMOND, 5 },
};


OreData diamondPickTable[] = {
  { STONE, 35 },
  { COAL, 20 },
  { IRON, 15 },
  { GOLD, 10 },
  { DIAMOND, 5 },
};

OreType getOre(PickaxeType pickaxeType) {
  OreData* table = defaultTable;

  switch (pickaxeType) {
    case STONE_PICK:
      table = stonePickTable;
      break;
    case IRON_PICK:
      table = ironPickTable;
      break;
    case GOLD_PICK:
      table = goldPickTable;
      break;
    case DIAMOND_PICK:
      table = diamondPickTable;
      break;
  }

  int totalWeight = 0;
  int count = sizeof(OreData) / sizeof(table);

  for (int i = 0; i < count; i++) {
    totalWeight += table[i].weight;
  }

  int randomNumber = rand() % totalWeight;
  int weightSum = 0;

  for (int i = 0; i < count; i++) {
    weightSum += table[i].weight;
    if (randomNumber < weightSum) return table[i].ore;
  }
  return STONE;
}
