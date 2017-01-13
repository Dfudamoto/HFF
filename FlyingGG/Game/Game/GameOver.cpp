#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver()
{
	back.Load("Assets/sprite/GameOver.jpg");
	back_sp.Init(&back);
	back_sp.SetSize({ 1330.5f, 730.5f });
	back_sp.SetPivot({ 0.0f, 0.5f });
	back_sp.SetPosition({ -650.0f, 0.0f });
}

GameOver::~GameOver()
{
}

void GameOver::Render(CRenderContext& rendercontext)
{
	back_sp.Draw(rendercontext);
}