#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

extern Player *player; 

GameCamera::GameCamera()
{
	//camera.SetUp({ 0.0f, 0.0f, 1.0f, });
	//CVector3 position = player->position;
	//position.y += 20.0f;
	//camera.SetPosition(position);
	//camera.SetTarget(player->position);
}

GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	if (player != nullptr)
	{
		CMatrix matrix = player->player_model.GetWorldMatrix();
		CVector3 target;

		target.x = matrix.m[2][0];
		target.y = matrix.m[2][1];
		target.z = matrix.m[2][2];
		CVector3 position = player->position;

		target.Add(player->position);
		camera.SetPosition(position);
		camera.SetTarget(target);
	}
	else
	{
		camera.SetPosition(CVector3::Zero);
		camera.SetTarget(CVector3::Zero);
	}
	camera.Update();
}
