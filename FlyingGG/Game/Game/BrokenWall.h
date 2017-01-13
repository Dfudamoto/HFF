#pragma once
class BrokenWall : public IGameObject
{
public:
	BrokenWall();
	~BrokenWall();

	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Break(CVector3&);
	void Delete();

	//ここからメンバ変数。
	CLight				light;			//ライト
	CSkinModel			skinModel;		//スキンモデル。
	CMeshCollider		meshCollider;	//メッシュコライダー。
	CRigidBody			rigidBody;		//剛体。
	CVector3			position;		//場所
	CLight				maplight;		//テスト用
	CSkinModelDataHandle modeldata;
	CSkinModelDataResources modelresource;
};

