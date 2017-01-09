#pragma once


#define MAX_ANGLE 75
#define MIN_ANGLE -75

class Player :	public IGameObject
{
public:
	Player();
	~Player();

	//�X�V�֐�
	void Update();

	//�v���C���[�̈ړ�����
	void Move();

	//���_�̉�]
	void Rotation();
	
	//�`�揈��
	void Render(CRenderContext&);

	//�{�����߂��Ŕ���������_���[�W�����炤�����B
	void BombDam(CVector3& bombpos);

	int GetHP()
	{
		return hp;
	}

	int							bombcount;
	CVector3					position;			//�ꏊ
	CQuaternion					rotation;			//�v���C���[�̌���
	CSkinModel					model;				//���f��
	CLight						light;				//���C�g
	CCharacterController		characterController;
	float						radius;				//�A�C�e���̂����蔻����Ƃ��̔��a
	CSkinModelDataHandle		modeldata;			//���f���f�[�^
	CSkinModelDataResources		modelresource;		//���f���f�[�^�n���h��������}��
	int							hp;					//�v���C���[�̗̑�
	CAnimation					animation;
	int							animenum;		
};

