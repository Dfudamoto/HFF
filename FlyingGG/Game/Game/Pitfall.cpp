#include "stdafx.h"
#include "Pitfall.h"
#include "GameCamera.h"
#include "Player.h"

extern Player* player;
extern GameCamera* gamecamera;


Pitfall::Pitfall()
{
}


Pitfall::~Pitfall()
{
}

void Pitfall::Init(const char *modelname, CVector3 position, CQuaternion rotation)
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
	model.Update(position, rotation, CVector3::One);
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

void Pitfall::Update()
{
	if (player->position.y - position.y > HEIGHT + 0.3f)
	{
		return;
	}
	CVector3 distance;
	distance.Subtract(position, player->position);
	distance.y = 0;
	if (distance.Length() < 5.0f)
	{
		PhysicsWorld().RemoveRigidBody(&rigidbody);
		rigidbody.Release();
		DeleteGO(this);
	}
}

void Pitfall::Render(CRenderContext& renderContext) {
	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}