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

	void Init(CVector3, CQuaternion);
	 
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

	void NockBack();

	void Delete();

	int							bombcount;
	int							applecount;
	int							debuffcount;
	CVector3					position;			//�ꏊ
	CQuaternion					rotation;			//�v���C���[�̌���
	CSkinModel					player_model;		//���f��
	CSkinModel					knife_model;
	CLight						light;				//���C�g
	CCharacterController		characterController;
	float						radius;				//�A�C�e���̂����蔻����Ƃ��̔��a
	CSkinModelDataHandle		player_data;			//���f���f�[�^
	CSkinModelDataResources		player_modelresource;		//���f���f�[�^�n���h��������}��
	CSkinModelDataResources		knife_modelresource;		//���f���f�[�^�n���h��������}��
	CSkinModelDataHandle		knife_data;			//���f���f�[�^
	int							hp;					//�v���C���[�̗̑�
	CAnimation					player_animation;
	CAnimation					knife_animation;
	int							animenum;		
	CVector3					hitbox_position;	//�i�C�t�̃|�W�V����
	bool						nockbackflg;
	bool						speedup_flg;
	float						speedup_count;
};

