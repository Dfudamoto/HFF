#pragma once
#include "Title.h"
#include "Map.h"
#include "Player.h"
#include "GameCamera.h"
#include "HPBar.h"
#include "ItemShow.h"
#include "GameOver.h"
#include "Load.h"

class Scene : public IGameObject
{
public:
	enum
	{
		TITLE,
		LOAD,
		GAMEPLAY,
		GAMEOVER,
		GAMECLEAR,
	};
	Scene();
	~Scene();

	void Start();

	void Update();

	ItemShow *itemshow;
	HPBar *hpbar;
	Map *map;
	GameOver *gameover;
	Title *title;
	Load *load;
	bool	transition_flg;
	int		transition_num;
	int		loadcount;
};

