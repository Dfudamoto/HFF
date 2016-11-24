#include "stdafx.h"
#include "Bomb.h"
#include "GameCamera.h"
#include "Player.h"
#include "time.h"

extern GameCamera *gamecamera;
extern Player *player;
Bomb *bomb;
CRandom random;
extern CLight darklight;

Bomb::Bomb()
{
	random.Init((unsigned int)+time(NULL));
	//modeldata.LoadModelData("Assets/modelData/car.X", NULL);
	//model.Init(modeldata);
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	model.SetShadowCasterFlag(true);
	fallspeed = 0.3f;
	start = true;
	angle = 0;
}

Bomb::~Bomb()
{

}

void Bomb::Init(CSkinModelData* modeldata)
{
	model.Init(modeldata);
	position = player->position;
	position.y += 0.7f; //プレイヤーの位置が低いための補正
	CMatrix matrix = player->model.GetWorldMatrix();
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
	CVector3 direction = move_direction;
	direction.Scale(0.3f);
	position.Add(direction);//プレイヤーにもあたるので少し前にずらす
	move_direction.Scale(10.0f);
	move_speed.y += 5.0f;
	move_speed = move_direction;
	charactercontroller.Init(0.5f, 0.5f, position);
	angle = 10;
}

void Bomb::Init(CVector3 position)
{
	modeldata.LoadModelData("Assets/modelData/bomb.X", NULL);
	model.Init(&modeldata);
	this->position = position;
	move_speed = CVector3::Zero;
	axisx = CVector3::AxisY;
	charactercontroller.Init(0.5f, 0.5f, this->position);
}

void Bomb::Update()
{
	//プレイヤー
	charactercontroller.SetMoveSpeed(move_speed);
	charactercontroller.Execute();
	position = charactercontroller.GetPosition();
	move_speed = charactercontroller.GetMoveSpeed();
	//モデルの回転
	CQuaternion multi;
	multi.SetRotation(axisx, CMath::DegToRad(-angle));
	rotation.Multiply(multi);

	CollCheck();
	//モデルの更新
	model.Update(position, rotation, CVector3::One);
}

void Bomb::CollCheck()
{
	if (!charactercontroller.IsPickup())
	{
		if (charactercontroller.IsCollision())
		{
			move_speed = CVector3::Zero;
			angle = 0;
		}
		//return;
	}
	if (charactercontroller.IsCollision())
	{
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
		model.SetShadowCasterFlag(false);
		charactercontroller.RemoveRigidBoby();
		DeleteGO(this);
	}
}

void Bomb::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

