#include "stdafx.h"
#include "HPBar.h"
#include "Player.h"

extern Player *player;

HPBar::HPBar()
{
	hp.Load("Assets/sprite/hp.png");
	hpspr.Init(&hp);
	hpspr.SetPosition({-600.0f, 300.0f});
	hpspr.SetPivot({ 0.0f, 0.0f });
	hpspr.SetSize({ 130.0f, 15.0f });
	hpb.Load("Assets/sprite/hp_back.png");
	hpbspr.Init(&hpb);
	hpbspr.SetPosition({ -600.0f, 300.0f });
	hpbspr.SetPivot({ 0.0f, 0.0f });
	hpbspr.SetSize({ 130.0f, 15.0f });
}


HPBar::~HPBar()
{
}

void HPBar::Update()
{

	hpspr.SetSize({ (float)(player->hp), 15.0f });
}

void HPBar::Render(CRenderContext& rendercontext)
{
	hpbspr.Draw(rendercontext);
	hpspr.Draw(rendercontext);
}
