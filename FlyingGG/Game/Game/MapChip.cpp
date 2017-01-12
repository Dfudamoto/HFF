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
	//maplight.SetAmbinetLight({ 0.01f, 0.01f, 0.01f });
	//maplight.SetAmbinetLight(CVector3::One);
	maplight.SetDiffuseLightColor(0, {0.9f, 0.9f, 0.9f, 1.0f});
}


MapChip::~MapChip()
{
}

void MapChip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	this->position = position;
	this->rotation = rotation;
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModelを初期化。
	skinModel.Init(modeldata.GetBody());

	//デフォルトライトを設定して。
	if (strcmp(modelName, "map") == 0 || strcmp(modelName, "ground") == 0)
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
	meshCollider.CreateFromSkinModel(&skinModel, modeldata.GetBody()->GetRootBoneWorldMatrix());
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

	maplight.SetDiffuseLightDirection(0, {0.0f, -1.0f, 0.0f});
	float light_scale = 1.0f / distance.Length();
	float light_limit = 3.0f;
	if (light_scale > light_limit)
	{
		light_scale = light_limit;
	}
	direction.Scale(light_scale);
	light.SetDiffuseLightDirection(0, direction);
	float pointlightcolor = 4.0f;
	skinModel.Update(position, rotation, CVector3::One);
}
void MapChip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void MapChip::Delete()
{
	if (this == nullptr)
	{
		return;
	}
	skinModel.SetShadowCasterFlag(false);
	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	DeleteGO(this);

}