#include "stdafx.h"
#include "HealingApple.h"
#include "GameCamera.h"
#include "Player.h"
#include "ItemShow.h"


extern Player* player;
extern GameCamera* gamecamera;
HealingApple *apple[APPLENUM];
extern int itemnum;

HealingApple::HealingApple()
{	
	//light.SetAmbinetLight({ 100.0f, 100.0f, 100.0f });
	//light.SetAmbinetLight(CVector3::One);
	light.SetAmbinetLight({ 0.01f,0.01f,0.01f });
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	harves = false;
	deleteflg = false;
}

HealingApple::~HealingApple()
{

}

void HealingApple::Init(const char *modelname, CVector3 position, CQuaternion rotation)
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
	CVector3 movespeed = { 0.0f, 0.0f, 0.0 };
	charactercontroller.SetMoveSpeed(movespeed);
	charactercontroller.Init(0.3f, 0.3f, position);
	model.Update(position, rotation, CVector3::One);
}

void HealingApple::Update() 
{
	float scale = 0.01f;
	Eatable();
	PickUp();
	Move();
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	distance.Scale(scale);
	direction.Normalize();
	float lightscale = 1.0f / distance.Length();
	if (lightscale < 1.0f)
	{
		direction.Scale(lightscale);
	}
	light.SetDiffuseLightDirection(0, direction);

	model.Update(position, rotation, CVector3::One);
}

void HealingApple::Move()
{
	//プレイヤーとの距離を計算
	CVector3 distance;
	distance.Subtract(position, player->hitbox_position);
	if (Pad(0).IsTrigger(enButtonX) && distance.Length() < 10.0f)
	{
		harves = true;
	}
	if (!harves)
	{
		return;
	}
	//移動（落下）処理
	charactercontroller.Execute();
	CVector3 movespeed = charactercontroller.GetMoveSpeed();
	charactercontroller.SetMoveSpeed(movespeed);
	position = charactercontroller.GetPosition();


}

void HealingApple::Render(CRenderContext& renderContext) 
{

	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}

void HealingApple::PickUp()
{
	//木から落ちてなければリターン
	if (!harves)
	{
		return;
	}
	CVector3 distance;
	distance.Subtract(position, player->hitbox_position);
	if (distance.Length() < player->radius && Pad(0).IsTrigger(enButtonA))
	{
		charactercontroller.SetPickUp(true);
		player->applecount++;
	}
	//拾われてなかったらリターン
	if (!charactercontroller.IsPickUp())
	{
		return;
	}
	position = player->position;
	position.y += 100.0f;
	charactercontroller.SetGravity(0.0f);
	charactercontroller.SetPosition(position);
	if (Pad(0).IsTrigger(enButtonX))
	{
		for (int i = 0;i < APPLENUM;i++)
		{
			if (apple[i] != nullptr && apple[i]->deleteflg)
			{
				return;
			}
		}
		deleteflg = true;
	}
}

void HealingApple::Eatable()
{
	if (!deleteflg)
	{
		return;
	}
	if (itemnum != ItemShow::APPLE)
	{
		return;
	}
	for (int i = 0;i < APPLENUM;i++)
	{
		if (apple[i] != nullptr && apple[i]->deleteflg)
		{
			apple[i] = nullptr;
		}
	}
	if (player->hp < MAXHP)
	{
		player->hp += 10;
	}
	Delete();
	player->applecount--;
}

void HealingApple::Delete()
{
	charactercontroller.RemoveRigidBoby();
	DeleteGO(this);
}
