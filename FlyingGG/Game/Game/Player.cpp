#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Bomb.h"

extern GameCamera *gamecamera;
extern Bomb *bomb[BOMBNUM];
extern int itemnum;

Player::Player()
{
	modelresource.Load(modeldata, "Assets/modelData/bodyg.X", NULL);
	//モデルの初期化


	model.Init(modeldata.GetBody());
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	position = CVector3::Zero;
	position = {0.0f, 3.0f, 0.0f };
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	characterController.Init(0.5f, 1.0f, position);
	radius = 3.0f;
	bombcount = 1;
	for (int i = 0;i < BOMBNUM;i++)
	{
		bomb[i] = nullptr;
	}
	hp = 130;
	itemnum = 0;
}

Player::~Player()
{

}

void Player::Update()
{
	//ボムを投げる
	if (Pad(0).IsTrigger(enButtonA) && bombcount > 0)
	{
		//Bomb *bomb;
		//bomb = NewGO<Bomb>(0);
		//bomb->Init();
		//bombcount--;
	}
	Move();
	Rotation();
	model.Update(position, rotation, CVector3::One);

}

void Player::Move()
{
	CVector3 move_direction_z;	//正面へのベクトル
	CVector3 move_direction_x;	//横方向へのベクトル

	//プレイヤーの前(後ろ)方向のベクトルを取得
	CMatrix matrix = model.GetWorldMatrix();
	float speedscale = 10.0f;
	move_direction_z.x = matrix.m[2][0];
	move_direction_z.z = matrix.m[2][2];
	move_direction_z.y = 0.0f;
	move_direction_z.Normalize();
	move_direction_z.Scale(speedscale);
	move_direction_z.Scale(Pad(0).GetLStickYF());
	
	//プレイヤーの横方向へのベクトルの取得
	move_direction_x.x = matrix.m[0][0];
	move_direction_x.z = matrix.m[0][2];
	move_direction_x.y = 0.0f;
	move_direction_x.Normalize();
	move_direction_x.Scale(speedscale);
	move_direction_x.Scale(Pad(0).GetLStickXF());

	CVector3 move = characterController.GetMoveSpeed();
	//前(後ろ)と横の移動量の足し算
	move.x = 0.0f;
	move.z = 0.0f;
	move.Add(move_direction_x);
	move.Add(move_direction_z);
	//ジャンプ処理
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

	position.y += 2.0f;

}

void Player::Rotation()
{
	//プレイヤーの回転角度と回転速度
	float anglespeed = 5.0f;
	static float anglex = 0;
	static float angley = 0;

	angley += Pad(0).GetRStickXF() * anglespeed;
	//プレイヤーの回転できる角度の限度チェック
	if (MIN_ANGLE < anglex && -Pad(0).GetRStickYF() < 0
		|| anglex < MAX_ANGLE && 0 < -Pad(0).GetRStickYF())
	{
		anglex += -Pad(0).GetRStickYF() * anglespeed;
	}

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(angley));
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisX, CMath::DegToRad(anglex));
	rotation.Multiply(multi);
}

void Player::Render(CRenderContext& rendercontext)
{
	//model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void Player::BombDam(CVector3& bombpos)
{
	CVector3 distance;
	distance.Subtract(position, bombpos);
	if (distance.Length() < 20.0f)
	{
		hp -= 10;
	}
}
