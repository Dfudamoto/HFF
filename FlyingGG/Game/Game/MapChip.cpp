#include "stdafx.h"
#include "MapChip.h"
#include "GameCamera.h"
#include "Player.h"

extern GameCamera *gamecamera;
extern CLight defaultlight;
extern Player *player;

MapChip::MapChip()
{
	light.SetAmbinetLight({ 0.01f, 0.01f, 0.01f });
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	maplight.SetAmbinetLight({ 0.01f, 0.01f, 0.01f });
	maplight.SetAmbinetLight(CVector3::One);
}


MapChip::~MapChip()
{
}

void MapChip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	this->position = position;
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	skinModel.Init(&skinModelData);
	//デフォルトライトを設定して。
	if (strcmp(modelName, "map") == 0)
	{
		skinModel.SetLight(&maplight);
	}
	else
	{
		skinModel.SetLight(&light);
	}
	//ワールド行列を更新する。
	//このオブジェクトは動かないので、初期化で一回だけワールド行列を作成すればおｋ。
	skinModel.Update(position, rotation, CVector3::One);
	//skinModel.SetFogParam(enFogFuncDist, 0.0f, 30.0f);

	//メッシュコライダーの作成。
	meshCollider.CreateFromSkinModel(&skinModel, skinModelData.GetRootBoneWorldMatrix());
	//剛体の作成。
	RigidBodyInfo rbInfo;
	//剛体のコライダーを渡す。
	rbInfo.collider = &meshCollider;
	//剛体の質量。0.0だと動かないオブジェクト。背景などは0.0にしよう。
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加する。
	PhysicsWorld().AddRigidBody(&rigidBody);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
}
void MapChip::Update()
{
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	distance.Scale(0.05f);

	direction.Normalize();
	float lightscale = 1.0f / distance.Length();
	if (distance.Length() > 1.0f)
	{
		direction.Scale(lightscale);
	}
	light.SetDiffuseLightDirection(0, direction);
	maplight.SetPointLightColor({ 4.0f, 4.0f, 4.0f, 1.0f });
	maplight.SetPointLightPosition(player->position);
}
void MapChip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}