#pragma once
#define MAX_ANGLE 89
#define MIN_ANGLE -89

class Player :	public IGameObject
{
public:
	Player();
	~Player();

	//�X�V�֐�
	void Update();

	//�v���C���[�̈ړ�����
	void Move();

	//���_(���f��)�̉�]
	void Rotation();
	
	//�`�揈��
	void Render(CRenderContext&);

	//���e�𓊂��鏈��
	void BombSlow();

	CVector3 position;			//�ꏊ
	CQuaternion rotation;		//�v���C���[�̌���
	CSkinModel model;			//���f��
	CSkinModelData modeldata;	//���f���f�[�^
	CLight light;				//���C�g
	CVector3 move_direction_z;	//���ʂւ̃x�N�g��
	CVector3 move_direction_x;	//�������ւ̃x�N�g��
	int anglex;
};

