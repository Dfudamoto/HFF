#include "stdafx.h"
#include "Bomb.h"
#include "GameCamera.h"
#include "Player.h"

extern GameCamera *gamecamera;
extern Player *player;
Bomb *bomb;


Bomb::Bomb()
{
	modeldata.LoadModelData("Assets/modelData/testbomb.x", NULL);
	model.Init(&modeldata);
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	position = player->position;
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	CMatrix matrix = player->model.GetWorldMatrix();
	axisx.x = matrix.m[0][0];
	axisx.y = matrix.m[0][1];
	axisx.z = matrix.m[0][2];
	axisx.Normalize();
	move_direction.x = matrix.m[2][0];
	move_direction.y = matrix.m[2][1];
	move_direction.z = matrix.m[2][2];
	move_direction.Scale(0.3f);
	fallspeed = 0.3f;
}

Bomb::~Bomb()
{

}

void Bomb::Update()
{


	float gravity = -0.0108f;
	position.Add(move_direction);
	fallspeed += gravity;
	position.y += fallspeed;

	//モデルの回転
	CQuaternion multi;
	multi.SetRotation(axisx, CMath::DegToRad(-10));
	rotation.Multiply(multi);

	CollCheck();
	//モデルの更新
	model.Update(position, rotation, CVector3::One);
}

void Bomb::CollCheck()
{
	if (position.y < 0.0f)
	{
		DeleteGO(this);
	}
}

void Bomb::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

