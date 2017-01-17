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

extern ItemBox *itembox[ITEMBOXNUM];


ItemBox::ItemBox()
{
	light.SetAmbinetLight({0.01f, 0.01f,0.01f});
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	deleteflg = false;
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
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModelを初期化。
	model.Init(modeldata.GetBody());
	//デフォルトライトを設定して。
	model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	//model.SetFogParam(enFogFuncDist, 0.0f, 30.0f);
	model.Update(position, rotation, CVector3::One);
	model.SetShadowCasterFlag(true);
	model.SetShadowReceiverFlag(true);
	//メッシュコライダーの作成。
	meshcollider.CreateFromSkinModel(&model, modeldata.GetBody()->GetRootBoneWorldMatrix());
	//剛体の作成。
	RigidBodyInfo rbInfo;
	//剛体のコライダーを渡す。
	rbInfo.collider = &meshcollider;
	//剛体の質量。0.0だと動かないオブジェクト。背景などは0.0にしよう。
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidbody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加する。
	PhysicsWorld().AddRigidBody(&rigidbody);
}
void ItemBox::Update()
{
	BombCreate();
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
	distance.Subtract(position, player->hitbox_position);
	if (distance.Length() < player->radius && Pad(0).IsTrigger(enButtonX))
	{
		//ある一定の距離でボタンが押されたら消えてボムをだす
		Delete();
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

void ItemBox::Delete()
{
	deleteflg = true;
	for (int i = 0;i < ITEMBOXNUM;i++)
	{
		if (itembox[i] != nullptr && itembox[i]->deleteflg)
		{
			itembox[i] = nullptr;
		}
	}
	model.SetShadowCasterFlag(false);
	PhysicsWorld().RemoveRigidBody(&rigidbody);
	rigidbody.Release();
	DeleteGO(this);
}