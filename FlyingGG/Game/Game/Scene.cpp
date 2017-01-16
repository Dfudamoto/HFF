#include "stdafx.h"
#include "Scene.h"

extern Player *player;
extern GameCamera *gamecamera;


Scene::Scene()
{
	transition_flg = true;
	transition_num = TITLE;
	loadcount = 0;
}


Scene::~Scene()
{
}

void Scene::Start()
{
	title = NewGO<Title>(0);
}

void Scene::Update()
{

	switch(transition_num)
	{
	case TITLE:
		if (Pad(0).IsTrigger(enButtonA))
		{
			load = NewGO<Load>(0);
			transition_num = LOAD;
			transition_flg = false;
		}
		break;
	case LOAD:
		if (1 <= loadcount)
		{
			player = NewGO<Player>(0);
			gamecamera = NewGO<GameCamera>(0);
			map = NewGO<Map>(0);
			hpbar = NewGO<HPBar>(1);
			itemshow = NewGO<ItemShow>(1);
			transition_num = GAMEPLAY;
		}
		loadcount++;
		break;
	case GAMEPLAY:
		if (player != nullptr && player->hp <= 0)
		{
			transition_num = GAMEOVER;
			transition_flg = true;
		}
		break;
	case GAMEOVER:
		map->ReInit();
		transition_num = GAMEPLAY;
		break;
	case GAMECLEAR:
		break;
	}

}
