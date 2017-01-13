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

	//�������烁���o�ϐ��B
	CLight				light;			//���C�g
	CSkinModel			skinModel;		//�X�L�����f���B
	CMeshCollider		meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			rigidBody;		//���́B
	CVector3			position;		//�ꏊ
	CLight				maplight;		//�e�X�g�p
	CSkinModelDataHandle modeldata;
	CSkinModelDataResources modelresource;
};

