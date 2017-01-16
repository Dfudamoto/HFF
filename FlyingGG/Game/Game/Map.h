#pragma once
#include "MapChip.h"
#include "ItemBox.h"
#include "HealingApple.h"
#include "DebuffItem.h"
#include "Bomb.h"
#include "Pitfall.h"
#include "BrokenWall.h"
#include "HelmetLight.h"
#include "Enemy.h"

class Map : public IGameObject
{
public:

	Map();
	~Map();
	void Start();
	void Update();
	void Delete();
	void ReInit();

	int applenum;
	int debuffnum;
	int mapchipnum;
	int itemboxnum;
	int enemynum;
	int wallnum;
	ItemBox *itembox[100];
	MapChip *mapchip[100];
	HelmetLight *helmet;
	int deletewindow;
};

