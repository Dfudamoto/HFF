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

	CSkinModelData				bombdata;			//�{���̃��f���f�[�^
	CVector3					position;			//�ꏊ
	CQuaternion					rotation;			//�v���C���[�̌���
	CSkinModel					model;				//���f��
	CSkinModelData				modeldata;			//���f���f�[�^
	CLight						light;				//���C�g
	CCharacterController		characterController;
	float						radius;				//�A�C�e���̂����蔻����Ƃ��̔��a
};

