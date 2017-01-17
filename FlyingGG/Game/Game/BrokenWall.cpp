#include "stdafx.h"
#include "BrokenWall.h"
#include "Player.h"
#include "GameCamera.h"

extern Player *player;
extern GameCamera *gamecamera;


BrokenWall::BrokenWall()
{
	light.SetAmbinetLight(CVector3::Zero);
	light.SetDiffuseLightColor(0, { 1.0f, 1.0f, 1.0f, 1.0f });
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
	float pointlightcolor = 0.0f;
	CVector3 distance;
	distance.Subtract(player->position, position);
	pointlightcolor = distance.Length();
	if (distance.Length() > 4.0f)
	{
		pointlightcolor *= 4.0f;
	}
	else
	{
		pointlightcolor *= distance.Length();
	}
	light.SetPointLightPosition(player->position);
	light.SetPointLightColor({ pointlightcolor, pointlightcolor, pointlightcolor, 1.0f });
}

void BrokenWall::Break(CVector3& position)
{
	CVector3 distance;
	distance.Subtract(this->position, position);
	if (distance.Length() < 7.0f)
	{
		Delete();
		CSoundSource *sound;
		sound = NewGO<CSoundSource>(0);
		sound->Init("Assets/SE/wallbreak.wav");
		sound->Play(false);
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