#include "stdafx.h"
#include "ItemBox.h"
#include "GameCamera.h"
#include "Player.h"
#include "Bomb.h"
#include "ItemShow.h"

extern int itemnum;
extern GameCamera *gamecamera;
extern Player *player;
Bomb *bomb[BOMBNUM];
extern CLight darklight;


ItemBox::ItemBox()
{

	light.SetAmbinetLight(CVector3::One);

	light.SetAmbinetLight({0.01f, 0.01f,0.01f});
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
}


ItemBox::~ItemBox()
{
}

void ItemBox::Init(const char *modelname, CVector3& position, CQuaternion& rotation)
{
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", modelname);
	//モデルデータをロード。
	modeldata.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	model.Init(&modeldata);
	//デフォルトライトを設定して。
	model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	//model.SetFogParam(enFogFuncDist, 0.0f, 30.0f);
	model.Update(position, rotation, CVector3::One);
	model.SetShadowCasterFlag(true);
	model.SetShadowReceiverFlag(true);
}
void ItemBox::Update()
{
	BombCreate();
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	distance.Scale(0.2f);

	direction.Normalize();
	float lightscale = 1.0f / distance.Length();
	if (distance.Length() > 1.0f)
	{
		direction.Scale(lightscale);

	}
	light.SetDiffuseLightDirection(0, direction);
	//maplight.SetPointLightColor({ 4.0f, 4.0f, 4.0f, 1.0f });
	//maplight.SetPointLightPosition(player->position);
	model.Update(position, rotation, CVector3::One);
}

void ItemBox::BombCreate()
{
	if (itemnum != ItemShow::KNIFE)
	{
		return;
	}
	//プレイヤーとの距離と測る
	CVector3 distance;
	distance.Subtract(position, player->position);
	if (distance.Length() < player->radius && Pad(0).IsTrigger(enButtonX))
	{
		model.SetShadowCasterFlag(false);
		//ある一定の距離でボタンが押されたら消えてボムをだす
		DeleteGO(this);
		for (int i = 0;i < BOMBNUM;i++)
		{
			if (bomb[i] == nullptr)
			{
				bomb[i] = NewGO<Bomb>(0);
				bomb[i]->Init(position);
				break;
			}
		}
	}
}

void ItemBox::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}