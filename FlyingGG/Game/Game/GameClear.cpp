#include "stdafx.h"
#include "GameClear.h"


GameClear::GameClear()
{
	back.Load("Assets/sprite/GameClear.jpg");
	back_sp.Init(&back);
	back_sp.SetSize({ 1330.5f, 730.5f });
	back_sp.SetPivot({ 0.0f, 0.5f });
	back_sp.SetPosition({ -650.0f, 0.0f });
}


GameClear::~GameClear()
{
}

void GameClear::Render(CRenderContext& rendercontext)
{
	back_sp.Draw(rendercontext);
}
