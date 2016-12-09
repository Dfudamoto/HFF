#pragma once
class HelmetLight : public IGameObject
{
public:
	HelmetLight();
	~HelmetLight();

	//�X�V�֐�
	void Update();

	//�`�揈��
	void Render(CRenderContext&);

	//�v���C���[���E�����̃`�F�b�N����
	void Equip();

	CSkinModelData		modeldata;		//���f��
	CSkinModel			model;			//���f���f�[�^
	CVector3			position;		//�ꏊ
	CQuaternion			rotation;		//���f���̌���
	CLight				light;			//���C�g
	bool				pickup;			//�v���C���[���E�������̃t���O
	bool				lightswitch;	//���C�g��ON/OFF
};

