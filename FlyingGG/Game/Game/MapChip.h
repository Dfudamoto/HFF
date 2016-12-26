#pragma once



class MapChip : public IGameObject
{
public:
	//�������烁���o�֐��B
	MapChip();
	~MapChip();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

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

