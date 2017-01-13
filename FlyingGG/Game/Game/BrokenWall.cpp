#include "stdafx.h"
#include "BrokenWall.h"
#include "Player.h"
#include "GameCamera.h"

extern Player *player;
extern GameCamera *gamecamera;


BrokenWall::BrokenWall()
{
	light.SetAmbinetLight(CVector3::One);
}

BrokenWall::~BrokenWall()
{
}


void BrokenWall::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	this->position = position;
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModelを初期化。
	skinModel.Init(modeldata.GetBody());
	//デフォルトライトを設定して。
	skinModel.SetLight(&light);
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
}

void BrokenWall::Update()
{
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	distance.Scale(0.05f);

	direction.Normalize();
	float light_scale = 1.0f / distance.Length();
	float light_limit = 3.0f;
	if (light_scale > light_limit)
	{
		light_scale = light_limit;
	}
	direction.Scale(light_scale);
	//light.SetDiffuseLightDirection(0, direction);
}

void BrokenWall::Break(CVector3& position)
{
	CVector3 distance;
	distance.Subtract(this->position, position);
	if (distance.Length() < 5.0f)
	{
		Delete();
	}
}

void BrokenWall::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void BrokenWall::Delete()
{
	if (this == nullptr)
	{
		return;
	}
	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	DeleteGO(this);
}