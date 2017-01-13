#include "stdafx.h"
#include "Load.h"
#include "Scene.h"
#include "Player.h"
#include "GameCamera.h"


extern Scene *scene;
extern GameCamera *gamecamera;
extern Player *player;

Load::Load()
{
	back.Load("Assets/sprite/Load.jpg");
	back_sp.Init(&back);
	back_sp.SetSize({ 1330.5f, 730.5f });
	back_sp.SetPivot({ 0.0f, 0.5f });
	back_sp.SetPosition({ -650.0f, 0.0f });
	deletewindow = scene->transition_num;
	initflg = true;
}


Load::~Load()
{
}

void Load::Start()
{
	if (deletewindow == Scene::TITLE)
	{
		DeleteGO(scene->title);
		scene->title = nullptr;
	}
	else if (deletewindow == Scene::GAMEOVER)
	{
		DeleteGO(scene->gameover);
		scene->gameover = nullptr;
	}
}

void Load::Update()
{
	if (initflg)
	{
		//player = NewGO<Player>(0);
		//gamecamera = NewGO<GameCamera>(0);
		//scene->map = NewGO<Map>(0);
		//scene->hpbar = NewGO<HPBar>(1);
		//scene->itemshow = NewGO<ItemShow>(1);
		initflg = false;
	}
}

void Load::Render(CRenderContext& rendercontext)
{
	back_sp.Draw(rendercontext);

}
