#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

extern Player *player; 

GameCamera::GameCamera()
{
<<<<<<< HEAD
	camera.SetPosition({ 0.0f, 0.0f, 10.0f });
	//camera.SetPosition({ 0.0f, 20.0f, 40.0f });
=======
	camera.SetPosition({ 0.0f, 5.0f, -10.0f });
	camera.SetPosition({ 0.0f, 20.0f, 40.0f });
>>>>>>> b99628ebff3d3627687ebe3aebe194de88152e22
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	//camera.SetUp({ 0.0f, 0.0f, .0f, });
}

GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	CMatrix matrix = player->model.GetWorldMatrix();
	CVector3 target;

	target.x = matrix.m[2][0];
	target.y = matrix.m[2][1];
	target.z = matrix.m[2][2];
	CVector3 position = player->position;
	position = target;
	position.Scale(-1.0f);
	//position.y += 1.0f;

	//target.Add(player->position);
	//camera.SetPosition(position);
	//camera.SetTarget(target);
	camera.Update();
}
