#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "ItemBox.h"
#include "HealingApple.h"
#include "DebuffItem.h"
#include "Bomb.h"
#include "Pitfall.h"

CLight defaultlight;
extern HealingApple *apple[APPLENUM];
extern Bomb *bomb[BOMBNUM];

struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

//マップの配置情報。
SMapInfo mapLocInfo[] = {
#include "locationInfo.h"
};

Map::Map()
{
	defaultlight.SetAmbinetLight({ 1.0f, 1.0f, 1.0f });
	applenum = 0;
	for (int i = 0;i < BOMBNUM;i++)
	{
		bomb[i] = nullptr;
	}
	for (int i = 0;i < APPLENUM;i++)
	{
		apple[i] = nullptr;
	}
}


Map::~Map()
{
}
void Map::Start()
{
	//マップにいくつのオブジェクトが配置されているか調べる。
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < numObject; i++) {
		if (strcmp(mapLocInfo[i].modelName, "apple") == 0)
		{
			
			apple[applenum] = NewGO<HealingApple>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			apple[applenum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			applenum++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "papaya") == 0)
		{
			DebuffItem* debuffitem = NewGO<DebuffItem>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			debuffitem->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp(mapLocInfo[i].modelName, "woodbox") == 0)
		{
			ItemBox* itembox = NewGO<ItemBox>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			itembox->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else
		{
			MapChip* mapChip = NewGO<MapChip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
	}
}
void Map::Update()
{

}
