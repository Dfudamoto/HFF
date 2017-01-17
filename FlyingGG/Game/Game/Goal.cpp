#include "stdafx.h"
#include "Goal.h"
#include "Scene.h"
#include "GameCamera.h"
#include "Player.h"

extern Scene *scene;
extern GameCamera *gamecamera;
extern Player *player;

Goal::Goal()
{
	hp = 3;
	light.SetAmbinetLight(CVector3::Zero);
	light.SetDiffuseLightColor(0, { 1.0f, 1.0f, 1.0f, 1.0f });
}


Goal::~Goal()
{
}

void Goal::Init(const char *modelName, CVector3 position, CQuaternion rotation)
{
	this->position = position;
	this->rotation = rotation;
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModelを初期化。
	model.Init(modeldata.GetBody());
	model.SetLight(&light);

	//ワールド行列を更新する。
	//このオブジェクトは動かないので、初期化で一回だけワールド行列を作成すればおｋ。
	model.Update(position, rotation, CVector3::One);
	//skinModel.SetFogParam(enFogFuncDist, 0.0f, 30.0f);
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

void Goal::Update()
{
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

	if (player->attackflg)
	{
		CVector3 distance;
		distance.Subtract(player->hitbox_position, position);
		if (distance.Length() < 4.0f)
		{
			hp--;
		}
	}
	model.Update(position, rotation, CVector3::One);
}

void Goal::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void Goal::Delete()
{
	model.SetShadowCasterFlag(false);
	PhysicsWorld().RemoveRigidBody(&rigidbody);
	rigidbody.Release();
	DeleteGO(this);
}
