#pragma once



class MapChip : public IGameObject
{
public:
	//ここからメンバ関数。
	MapChip();
	~MapChip();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Delete();

	//ここからメンバ変数。
	CLight				light;			//ライト
	CSkinModel			skinModel;		//スキンモデル。
	CMeshCollider		meshCollider;	//メッシュコライダー。
	CRigidBody			rigidBody;		//剛体。
	CVector3			position;		//場所
	CLight				maplight;		
	CLight				walllight;
	CSkinModelDataHandle modeldata;
	CSkinModelDataResources modelresource;
	CQuaternion				rotation;
	RigidBodyInfo rbInfo;
	const char *modelname;
};

