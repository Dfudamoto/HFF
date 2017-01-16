#include "stdafx.h"
#include "Bomb.h"
#include "GameCamera.h"
#include "Player.h"
#include "time.h"
#include "ItemShow.h"
#include "BrokenWall.h"

extern GameCamera *gamecamera;
extern Player *player;
CRandom random;
extern CLight darklight;
extern Bomb* bomb[BOMBNUM];
extern int itemnum;
extern BrokenWall *wall[WALLNUM];

Bomb::Bomb()
{
	random.Init((unsigned int)+time(NULL));
	modelresource.Load(modeldata, "Assets/modelData/bomb.X", NULL);
	model.Init(modeldata.GetBody());
	light.SetAmbinetLight(CVector3::Zero);
	light.SetDiffuseLightColor(0, { 1.0f, 1.0f, 1.0f, 1.0f });
	model.SetLight(&light);
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	model.SetShadowCasterFlag(true);
	fallspeed = 0.3f;
	angle = 0;
	deleteflg = false;
}

Bomb::~Bomb()
{

}



void Bomb::Init(CVector3 position)
{
	this->position = position;
	move_speed = CVector3::Zero;
	axisx = CVector3::AxisY;
	charactercontroller.Init(0.5f, 0.5f, this->position);
}

void Bomb::Update()
{
	charactercontroller.SetMoveSpeed(move_speed);
	charactercontroller.Execute();
	position = charactercontroller.GetPosition();
	move_speed = charactercontroller.GetMoveSpeed();
	//モデルの回転
	CQuaternion multi;
	multi.SetRotation(axisx, CMath::DegToRad(-angle));
	rotation.Multiply(multi);
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
	CollCheck();
	Throw();
	
	//モデルの更新
	model.Update(position, rotation, CVector3::One);
}

void Bomb::Throw()
{
	//投げられている状態ならreturnする
	if (throwflg)
	{
		return;
	}
	//ボムの近くでAボタンを押すと拾う
	CVector3 distance;
	distance.Subtract(position, player->position);
	if (distance.Length() < 10.0f && Pad(0).IsTrigger(enButtonA) && !charactercontroller.IsPickUp())
	{
		charactercontroller.SetPickUp(true);
		player->bombcount++;
	}


	if (charactercontroller.IsPickUp())
	{
		position = player->position;
		position.y += 100.0f;
		charactercontroller.SetGravity(0.0f);
		charactercontroller.SetPosition(position);
		//拾った状態でXボタンを押すと投げる
		if (itemnum != ItemShow::BOMB)
		{
			return;
		}
		if (Pad(0).IsTrigger(enButtonX))
		{
			for (int i = 0;i < BOMBNUM;i++)
			{
				//他のボムが投げられていれば投げれない
				if (bomb[i] != nullptr && bomb[i]->throwflg)
				{
					return;
				}
			}
			position = player->position;
			charactercontroller.SetPosition(position);
			throwflg = true;
			charactercontroller.SetGravity(-9.8f);
			CMatrix matrix = player->player_model.GetWorldMatrix();
			//ボム空中にある間の回転軸
			axisx.x = matrix.m[0][0];
			axisx.y = matrix.m[0][1];
			axisx.z = matrix.m[0][2];
			axisx.Normalize();
			//ボムが飛ぶ方向
			move_direction.x = matrix.m[2][0];
			move_direction.y = matrix.m[2][1];
			move_direction.z = matrix.m[2][2];
			move_direction.Normalize();
			CVector3 addpos = move_direction;
			addpos.Scale(0.3f);
			position.Add(addpos);//プレイヤーにもあたるので少し前にずらす
			move_direction.Scale(10.0f);
			move_speed = move_direction;
			move_speed.y += 5.0f;
			angle = 10;
			player->bombcount--;
		}
	}
}

void Bomb::CollCheck()
{
	if (!charactercontroller.IsCollision())
	{
		if(!throwflg)
		{
			move_speed = CVector3::Zero;
			angle = 0;
		}
		return;
	}
	//何かに当たったらパーティクルを出して死亡
	//パーティクルを出す処理
	CParticleEmitter *particle;
	particle = NewGO<CParticleEmitter>(0);
	particle->Init(random, gamecamera->camera,
	{
	"Assets/effect/realExplosion.png",				//!<テクスチャのファイルパス。
	{0.0f, 0.0f, 0.0f},								//!<初速度。
	1.0f,											//!<寿命。単位は秒。
	1.0f,											//!<発生時間。単位は秒。
	5.0f,											//!<パーティクルの幅。
	5.0f,											//!<パーティクルの高さ。
	{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
	{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
	{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
	{
		{ 0.0f, 0.0f, 0.333f, 0.3333f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f }
	},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
	1,												//!<UVテーブルのサイズ。
	{ 0.0f, 0.0f, 0.0f },							//!<重力。
	true,											//!<死ぬときにフェードアウトする？
	0.3f,											//!<フェードする時間。
	1.0f,											//!<初期アルファ値。
	true,											//!<ビルボード？
	0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
	0,												//!<0半透明合成、1加算合成。
	{1.0f, 1.0f, 1.0f},								//!<乗算カラー。
	},
	position);
	deleteflg = true;
	//消すボムの情報をリセット
	for (int i = 0;i < BOMBNUM;i++)
	{
		if (bomb[i] != nullptr && bomb[i]->deleteflg)
		{
			bomb[i] = nullptr;
		}
	}
	for (int i = 0;i < WALLNUM;i++)
	{
		if (wall[i] != nullptr)
		{
			wall[i]->Break(position);
		}
	}
	player->BombDam(position);
	Delete();
}

void Bomb::Render(CRenderContext& rendercontext)
{
	//if (charactercontroller.IsPickUp() && !throwflg)
	//{
	//	return;
	//}
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void Bomb::Delete()
{
	if (this == nullptr)
	{
		return;
	}
	model.SetShadowCasterFlag(false);
	charactercontroller.RemoveRigidBoby();
	DeleteGO(this);
}

