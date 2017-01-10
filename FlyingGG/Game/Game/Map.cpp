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

//�}�b�v�̔z�u���B
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
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
	for (int i = 0; i < numObject; i++) {
		if (strcmp(mapLocInfo[i].modelName, "apple") == 0)
		{
			
			apple[applenum] = NewGO<HealingApple>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			apple[applenum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			applenum++;
		}
		else if (strcmp(mapLocInfo[i].modelName, "papaya") == 0)
		{
			DebuffItem* debuffitem = NewGO<DebuffItem>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			debuffitem->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp(mapLocInfo[i].modelName, "woodbox") == 0)
		{
			ItemBox* itembox = NewGO<ItemBox>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			itembox->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else
		{
			MapChip* mapChip = NewGO<MapChip>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
	}
}
void Map::Update()
{

}
