#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Bomb.h"
#include "HealingApple.h"

extern GameCamera *gamecamera;
extern Bomb *bomb[BOMBNUM];
extern int itemnum;
extern HealingApple *apple[APPLENUM];

Player::Player()
{
	modelresource.Load(player_data, "Assets/modelData/bodyg_alpha.X", &player_animation);
	modelresource.Load(knife_data, "Assets/modelData/knife.X", &knife_animation);
	//モデルの初期化
	player_model.Init(player_data.GetBody());
	knife_model.Init(knife_data.GetBody());
	light.SetAmbinetLight(CVector3::One);
	player_model.SetLight(&light);
	knife_model.SetLight(&light);
	position = CVector3::Zero;
	position = {0.0f, 3.0f, 0.0f };
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	characterController.Init(0.5f, 1.0f, position);
	radius = 3.0f;


	hp = MAXHP;
	itemnum = 0;
	animenum = 0;
	//player_animation.SetAnimationLoopFlag(0, false);	
	knife_animation.SetAnimationLoopFlag(0, false);
}

Player::~Player()
{

}

void Player::Update()
{
	if (Pad(0).IsTrigger(enButtonA))
	{
		player_animation.PlayAnimation(animenum);
		if (animenum == KNIFE)
		{
			knife_animation.PlayAnimation(0);
		}
	}
	if (Pad(0).IsTrigger(enButtonLB1) && 0 < animenum)
	{
		animenum--;
	}
	if (Pad(0).IsTrigger(enButtonRB1) && animenum < ANIMATIONNUM - 1)
	{
		animenum++;
	}
	Move();
	Rotation();
	player_animation.Update(3.0f / 60.0f);
	knife_animation.Update(3.0f / 60.0f);
	player_model.Update(position, rotation, CVector3::One);
	knife_model.Update(position, rotation, CVector3::One);
}

void Player::Move()
{
	CVector3 move_direction_z;	//正面へのベクトル
	CVector3 move_direction_x;	//横方向へのベクトル

	//プレイヤーの前(後ろ)方向のベクトルを取得
	CMatrix matrix = player_model.GetWorldMatrix();
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
	position.y += HEIGHT;
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
	player_model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
	knife_model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
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
