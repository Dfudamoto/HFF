#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Bomb.h"

extern GameCamera *gamecamera;

Player::Player()
{
	//モデルの初期化
	modeldata.LoadModelData("Assets/modelData/Player.X", NULL);
	model.Init(&modeldata);
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	position = CVector3::Zero;
	position = {0.0f, 23.0f, 10.0f };
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(180));

	bombdata.LoadModelData("Assets/modelData/car.X", NULL);
	characterController.Init(0.5f, 1.0f, position);
	radius = 3.0f;
}


Player::~Player()
{

}

void Player::Update()
{
	//ボムを投げる
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

	CVector3 move_direction_z;	//正面へのベクトル
	CVector3 move_direction_x;	//横方向へのベクトル

	//プレイヤーの前方向のベクトルを取得
	CMatrix matrix = model.GetWorldMatrix();
	float speedscale = 30.0f;
	move_direction_z.x = matrix.m[2][0];
	move_direction_z.z = matrix.m[2][2];
	move_direction_z.Normalize();
	move_direction_z.Scale(speedscale);
	move_direction_z.Scale(Pad(0).GetLStickYF());
	
	//プレイヤーの横方向へのベクトルの取得
	move_direction_x.x = matrix.m[0][0];
	move_direction_x.z = matrix.m[0][2];
	move_direction_x.Normalize();
	move_direction_x.Scale(speedscale);
	move_direction_x.Scale(Pad(0).GetLStickXF());

	CVector3 move = characterController.GetMoveSpeed();
	move.x = 0.0f;
	move.z = 0.0f;
	move.Add(move_direction_x);
	move.Add(move_direction_z);
	if (Pad(0).IsTrigger(enButtonB))
	{
		characterController.Jump();
		move.y = 10.0f;
	}
	//決定した移動速度をキャラクタコントローラーに設定。
	characterController.SetMoveSpeed(move);
	//キャラクターコントローラーを実行。
	characterController.Execute();
	//実行結果を受け取る。
	position = characterController.GetPosition();
	//position.y = 0.0f;

}

void Player::Rotation()
{
	float anglespeed = 5.0f;
	static float anglex = 0;
	static float angley = 0;

	angley += Pad(0).GetRStickXF() * anglespeed;
	if (MIN_ANGLE < anglex && -Pad(0).GetRStickYF() < 0
		|| anglex < MAX_ANGLE && 0 < -Pad(0).GetRStickYF())
	{
		anglex -= Pad(0).GetRStickYF() * anglespeed;
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

