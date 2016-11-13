#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Bomb.h"

extern GameCamera *gamecamera;

Player::Player()
{
	//ÉÇÉfÉãÇÃèâä˙âª
	modeldata.LoadModelData("Assets/modelData/Player.X", NULL);
	model.Init(&modeldata);
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);

	position = CVector3::Zero;
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(180));

	bombdata.LoadModelData("Assets/modelData/car.X", NULL);
}


Player::~Player()
{

}

void Player::Update()
{
	if (Pad(0).IsTrigger(enButtonA))
	{
		Bomb *bomb;
		bomb = NewGO<Bomb>(0);
		bomb->Init(&bombdata);
	}
	Move();
	Rotation();
	model.Update(position, rotation, CVector3::One);
}

void Player::Move()
{

	CMatrix matrix = model.GetWorldMatrix();
	float speedscale = 0.3f;
	move_direction_z.x = matrix.m[2][0];
	move_direction_z.y = 0.0f;
	move_direction_z.z = matrix.m[2][2];
	move_direction_z.Normalize();
	move_direction_z.Scale(speedscale);

	move_direction_x.x = matrix.m[0][0];
	move_direction_x.y = 0.0f;
	move_direction_x.z = matrix.m[0][2];
	move_direction_x.Normalize();
	move_direction_x.Scale(speedscale);

	CVector3 addposx = move_direction_x;
	addposx.Scale(Pad(0).GetLStickXF());
	position.Add(addposx);

	CVector3 addposz = move_direction_z;
	addposz.Scale(Pad(0).GetLStickYF());
	position.Add(addposz);

}

void Player::Rotation()
{
	float anglespeed = 5.0f;
	static float anglex = 0;
	static float angley = 0;

	angley += Pad(0).GetRStickXF() * anglespeed;
	if (MIN_ANGLE < anglex && Pad(0).GetRStickYF() < 0
		|| anglex < MAX_ANGLE && 0 < Pad(0).GetRStickYF())
	{
		anglex += Pad(0).GetRStickYF() * anglespeed;
	}

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(angley));
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisX, CMath::DegToRad(anglex));
	rotation.Multiply(multi);
}

void Player::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

