#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"

extern GameCamera *gamecamera;

Player::Player()
{
	//ƒ‚ƒfƒ‹‚Ì‰Šú‰»
	modeldata.LoadModelData("Assets/modelData/Player.X", NULL);
	model.Init(&modeldata);
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);

	position = CVector3::Zero;
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(180));
	


}


Player::~Player()
{

}

void Player::Update()
{
	float speedscale = 0.3f;
	CMatrix matrix = model.GetWorldMatrix();
	move_direction_z.x = matrix.m[2][0];
	move_direction_z.y = matrix.m[2][1];
	move_direction_z.z = matrix.m[2][2];
	move_direction_z.Scale(speedscale);

	move_direction_x.x = matrix.m[0][0];
	move_direction_x.y = matrix.m[0][1];
	move_direction_x.z = matrix.m[0][2];
	move_direction_x.Scale(speedscale);
	Move();
	Rotation();
	model.Update(position, rotation, CVector3::One);
}

void Player::Move()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		position.Subtract(move_direction_x);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		position.Add(move_direction_x);
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		position.Add(move_direction_z);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		position.Subtract(move_direction_z);
	}
}

void Player::Rotation()
{
	CQuaternion multiy;
	int angle = 0;
	int rad = 6;
	if (Pad(0).IsPress(enButtonA))
	{
		angle += rad;
	}
	if (Pad(0).IsPress(enButtonB))
	{
		angle -= rad;
	}
	multiy.SetRotation(CVector3::AxisY, CMath::DegToRad(angle));
	rotation.Multiply(multiy);
}

void Player::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

