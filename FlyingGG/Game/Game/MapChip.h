#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class MapChip : public IGameObject
{
public:
	//ここからメンバ関数。
	MapChip();
	~MapChip();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

	//ここからメンバ変数。
	CSkinModel			skinModel;		//スキンモデル。
	CSkinModelData		skinModelData;	//スキンモデルデータ。
	CMeshCollider		meshCollider;	//メッシュコライダー。
	CRigidBody			rigidBody;		//剛体。
};

