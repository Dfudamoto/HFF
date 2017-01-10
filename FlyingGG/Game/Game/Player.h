#pragma once


#define MAX_ANGLE 75
#define MIN_ANGLE -75

class Player :	public IGameObject
{
public:
	Player();
	~Player();

	enum
	{
		WAIT,
		WALK,
		RUN,
		KNIFE,
		BOMBTHROW,
		ANIMATIONNUM
	};
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
	CSkinModel					player_model;		//���f��
	CSkinModel					knife_model;
	CLight						light;				//���C�g
	CCharacterController		characterController;
	float						radius;				//�A�C�e���̂����蔻����Ƃ��̔��a
	CSkinModelDataHandle		player_data;			//���f���f�[�^
	CSkinModelDataResources		modelresource;		//���f���f�[�^�n���h��������}��
	CSkinModelDataHandle		knife_data;			//���f���f�[�^
	int							hp;					//�v���C���[�̗̑�
	CAnimation					player_animation;
	CAnimation					knife_animation;
	int							animenum;		
};

