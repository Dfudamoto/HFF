#include "stdafx.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Player.h"

extern GameCamera *gamecamera;
extern Player *player;
extern Enemy *enemy[ENEMYNUM];

Enemy::Enemy()
{
	light.SetAmbinetLight(CVector3::Zero);
	light.SetDiffuseLightColor(0, { 1.0f, 1.0f, 1.0f, 1.0f });
	discovery = false;
	rotswitch = false;
	saverad = 0.0f;
	reusecount = 0;
	reuse = false;
	nockbackflg = false;
	timer = 0.0f;
	sticknum = 0;
	move_angle = CVector3::Zero;
	hp = 2;
}


Enemy::~Enemy()
{
}

void Enemy::Init(const char *modelname, CVector3 position, CQuaternion rotation)
{
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", modelname);
	//モデルデータをロード。
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModelを初期化。
	model.Init(modeldata.GetBody());
	//デフォルトライトを設定して。
	model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	charactercontroller.Init(0.3f, 0.3f, position);
	model.Update(position, rotation, CVector3::One);

	model.SetShadowCasterFlag(true);
	timer = 0.0f;
	CMatrix matrix = model.GetWorldMatrix();
	CVector3 movespeed;
	movespeed.x = matrix.m[2][0];
	movespeed.y = matrix.m[2][1];
	movespeed.z = matrix.m[2][2];
	movespeed.Normalize();
	charactercontroller.SetMoveSpeed(movespeed);
}

void Enemy::Update()
{
	Delete();
	if (deleteflg)
	{
		return;
	}
	CVector3 distance;
	distance.Subtract(player->position, position);
	if (discovery && distance.Length() < 5.0f)
	{
		//player->NockBack();
	}
	//if (!charactercontroller.IsJump())
	//{
	//	nockbackflg = false;
	//}
	if (nockbackflg)
	{
		nockbacktimer += 1.0f;
		if (nockbacktimer >= 30.0f)
		{
			nockbackflg = false;
			nockbacktimer = 0.0f;
		}
	}
	if (player->attackflg)
	{
		CVector3 distance;
		distance.Subtract(player->hitbox_position, position);
		if (distance.Length() < 2.0f)
		{
			hp--;
		}
	}
	Move();
	charactercontroller.Execute();
	position = charactercontroller.GetPosition();
	position.y += 1.5f;
	model.Update(position, rotation, CVector3::One);
	if (player->attackflg)
	{
		NockBack2();
	}
	if (hp <= 0 && !deleteflg)
	{
		deleteflg = true;
	}
}

void Enemy::Move()
{
	if (nockbackflg)
	{
		return;
	}
	if (discovery)
	{
		CMatrix matrix = model.GetWorldMatrix();
		CVector3 direction;
		direction.Subtract(player->position, position);
		if (direction.Length())
		{
			direction.Normalize();
			move_angle = direction;
			move_angle.Scale(0.005f);
		}
		direction.y = 0.0f;
		direction.Normalize();

		//float rad = direction.x / direction.Length();
		//if (rotswitch)
		//{
		//	float angle = 180.0f - CMath::RadToDeg(asin(rad));
		//	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(angle));

		//}
		//else
		//{
		//	rotation.SetRotation(CVector3::AxisY, asin(rad));
		//}
		//float border = 20.0f;
		//float nowrad = rad * 180.0f;
		//float radborder = 88.0f;
		//if((rad * 90.0f > radborder || rad * 90.0f < -radborder))
		//{
		//	if ((border <= saverad - nowrad || -border >= saverad - nowrad))
		//	{
		//		if (Pad(0).GetLStickXF() < 0)
		//		{
		//			sticknum = -1;
		//		}
		//		else if (Pad(0).GetLStickXF() > 0)
		//		{
		//			sticknum = 1;
		//		}

		//		rotswitch = !rotswitch;
		//		saverad = nowrad;
		//		reusecount = 0;
		//	}
		//	else
		//	{
		//		if (reusecount % 2 == 1)
		//		{
		//			rotswitch = !rotswitch;
		//			reusecount = 0;
		//		}
		//	}
		//	reuse = true;
		//}
		//else
		//{
		//	if (reuse)
		//	{
		//		reusecount++;
		//		if (sticknum == -1 && Pad(0).GetLStickXF() > 0 || sticknum == 1 && Pad(0).GetLStickXF() < 0)
		//		{
		//			rotswitch = !rotswitch;
		//		}
		//		reuse = false;

		//	}
		//}
		//回転させる
		CVector3 moveXZ = move_angle;		//方向ベクトル
		moveXZ.y = 0.0f;
		float angle;

		//AxisZとmoveXZのなす角を求める
		if (moveXZ.Length() > 0.0f)
		{
			angle = moveXZ.Dot(CVector3::AxisZ);
			angle /= (moveXZ.Length() + 0.0001f);
			angle = acosf(angle);
			angle = angle * 180.0 / CMath::PI;

			if (moveXZ.x < 0.0f)
			{
				angle *= -1.0f;
			}
		}
		rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(angle));
		CVector3 movespeed = direction;
		movespeed.Scale(5.0f);
		charactercontroller.SetMoveSpeed(CVector3::Zero);
	}
	else
	{
		timer += 1.0f / 60.0f;
		if (timer > 5.0f)
		{
			CQuaternion multi;
			multi.SetRotation(CVector3::AxisY, CMath::DegToRad(180));
			rotation.Multiply(multi);
			CVector3 movespeed = charactercontroller.GetMoveSpeed();
			movespeed.Scale(-1.0f);
			charactercontroller.SetMoveSpeed(movespeed);
			timer = 0.0f;
		}
		CVector3 distance;
		distance.Subtract(position, player->position);
		distance.y = 0.0f;
		if (distance.Length() < 5.0f)
		{
			discovery = true;
		}

	}
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	distance.Scale(0.2f);


	float light_scale = 1.0f / distance.Length();
	direction.Normalize();
	float light_limit = 1.0f;
	if (light_scale > light_limit)
	{
		light_scale = light_limit;
	}
	direction.Scale(light_scale);
	light.SetDiffuseLightDirection(0, direction);
}


void Enemy::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void Enemy::Delete()
{
	if (!deleteflg)
	{
		return;
	}
	for (int i = 0;i < ENEMYNUM;i++)
	{
		if (enemy[i] != nullptr && enemy[i]->deleteflg)
		{
			enemy[i] = nullptr;
		}
	}
	charactercontroller.RemoveRigidBoby();
	model.SetShadowCasterFlag(false);
	DeleteGO(this);
}

void Enemy::NockBack()
{
	CVector3 distance;
	distance.Subtract(player->hitbox_position, position);
	if (distance.Length() > 5.0f)
	{
		return;
	}
	charactercontroller.Jump();
	CMatrix matrix = model.GetWorldMatrix();
	CVector3 movespeed;
	movespeed.x = -matrix.m[2][0];
	movespeed.y = 0.0f;
	movespeed.z = -matrix.m[2][2];
	movespeed.Normalize();
	movespeed.Scale(10.0f);
	movespeed.y += 5.0f;
	charactercontroller.SetMoveSpeed(movespeed);
	charactercontroller.Execute();
	nockbackflg = true;
}

void Enemy::NockBack2()
{
	CVector3 distance;
	distance.Subtract(player->hitbox_position, position);
	if (distance.Length() > 5.0f)
	{
		return;
	}
	nockbackflg = true;
	CMatrix matrix = model.GetWorldMatrix();
	CVector3 movespeed;
	movespeed.x = -matrix.m[2][0];
	movespeed.z = -matrix.m[2][2];
	movespeed.Normalize();
	movespeed.Scale(2.0f);
	charactercontroller.SetMoveSpeed(CVector3::Zero);
}

