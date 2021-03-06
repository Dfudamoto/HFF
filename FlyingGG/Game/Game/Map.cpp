#include "stdafx.h"
#include "Map.h"
#include "Scene.h"
#include "Goal.h"

CLight defaultlight;
extern HealingApple *apple[APPLENUM];
extern Bomb *bomb[BOMBNUM];
BrokenWall *wall[WALLNUM];
DebuffItem *debuffitem[DEBUFFNUM];
extern Scene *scene;
Enemy *enemy[ENEMYNUM];
extern Player *player;
extern GameCamera *gamecamera;
Goal *goal;
ItemBox *itembox[ITEMBOXNUM];

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
	debuffnum = 0;
	mapchipnum = 0;
	itemboxnum = 0;
	enemynum = 0;
	wallnum = 0;
	if (scene != nullptr)
	{
		deletewindow = scene->transition_num;
	}

	for (int i = 0;i < BOMBNUM;i++)
	{
		bomb[i] = nullptr;
	}
	for (int i = 0;i < APPLENUM;i++)
	{
		apple[i] = nullptr;
	}
	for (int i = 0;i < DEBUFFNUM;i++)
	{
		debuffitem[i] = nullptr;
	}
	for (int i = 0;i < WALLNUM;i++)
	{
		wall[i] = nullptr;
	}
	helmet = nullptr;
	goal = nullptr;

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
		if (strcmp(mapLocInfo[i].modelName, "bodyg_beta") == 0)
		{
			player = NewGO<Player>(0);
			player->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp(mapLocInfo[i].modelName, "apple") == 0)
		{
			
			apple[applenum] = NewGO<HealingApple>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			apple[applenum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			applenum++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "dragonfruit") == 0)
		{
			debuffitem[debuffnum] = NewGO<DebuffItem>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			debuffitem[debuffnum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			debuffnum++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "woodbox") == 0)
		{
			itembox[itemboxnum] = NewGO<ItemBox>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			itembox[itemboxnum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			itemboxnum++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "Enemy") == 0)
		{
			enemy[enemynum] = NewGO<Enemy>(0);
			enemy[enemynum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			enemynum++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "brokenwall") == 0)
		{
			wall[wallnum] = NewGO<BrokenWall>(0);
			wall[wallnum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			wallnum++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "Goal") == 0)
		{
			goal = NewGO<Goal>(0);
			goal->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else
		{
			mapchip[mapchipnum] = NewGO<MapChip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			mapchip[mapchipnum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			mapchipnum++;
		}
	}
	helmet = NewGO<HelmetLight>(0);
	gamecamera = NewGO<GameCamera>(0);
	if (scene != nullptr)
	{
		DeleteGO(scene->load);
		scene->load = nullptr;
	}

}
void Map::Update()
{
}

void Map::Delete()
{
	for (int i = 0;i < APPLENUM;i++)
	{
		if (apple[i] != nullptr)
		{
			apple[i]->Delete();
			apple[i] = nullptr;
		}
	}
	for (int i = 0;i < DEBUFFNUM;i++)
	{
		if (debuffitem[i] != nullptr)
		{
			debuffitem[i]->Delete();
			debuffitem[i] = nullptr;
		}
	}
	for (int i = 0;i < mapchipnum;i++)
	{
		mapchip[i]->Delete();
		mapchip[i] = nullptr;
	}

	for (int i = 0;i < itemboxnum;i++)
	{
		if (itembox[i] != nullptr)
		{
			itembox[i]->Delete();
			itembox[i] = nullptr;
		}
	}
	for (int i = 0;i < enemynum;i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Delete();
			enemy[i] = nullptr;
		}
	}
	helmet->Delete();
	helmet = nullptr;
	DeleteGO(this);
}

void Map::ReInit()
{
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	int applecount = 0;
	int debuffcount = 0;
	int itemboxcount = 0;
	int enemycount = 0;
	for (int i = 0; i < numObject; i++) {
		if (strcmp(mapLocInfo[i].modelName, "apple") == 0)
		{
			if (apple[applecount] == nullptr)
			{
				apple[applecount] = NewGO<HealingApple>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				apple[applecount]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			}
			else
			{
				apple[applecount]->ReInit();
			}
			applecount++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "dragonfruit") == 0)
		{
			if (debuffitem[debuffcount] == nullptr)
			{
				debuffitem[debuffcount] = NewGO<DebuffItem>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				debuffitem[debuffcount]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			}
			else
			{
				debuffitem[debuffcount]->ReInit();
			}
			debuffcount++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "woodbox") == 0)
		{
			if (itembox[itemboxcount] == nullptr)
			{
				itembox[itemboxcount] = NewGO<ItemBox>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				itembox[itemboxcount]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			}
			itemboxcount++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "Enemy") == 0)
		{
			if (enemy[enemycount] == nullptr)
			{
				enemy[enemycount] = NewGO<Enemy>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				enemy[enemycount]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			}
			else
			{
				enemy[enemycount]->ReInit();
			}
			itemboxcount++;
		}
	}
	player->ReInit();
	//if (scene != nullptr)
	//{
	//	DeleteGO(scene->load);
	//	scene->load = nullptr;
	//}
}