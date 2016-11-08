#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
	camera.SetPosition({ 0.0f, 10.0f, 10.0f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
}


GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	camera.Update();
}
