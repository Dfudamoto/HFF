#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
	camera.SetPosition({ 0.0f, 20.0f, 0.0f });
	camera.SetTarget(CVector3::Zero);
}


GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	camera.Update();
}
