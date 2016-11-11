#pragma once

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

	CVector3 position;			//�ꏊ
	CQuaternion rotation;		//�v���C���[�̌���
	CSkinModel model;			//���f��
	CSkinModelData modeldata;	//���f���f�[�^
	CLight light;				//���C�g
	CVector3 move_direction_z;	//���ʂւ̃x�N�g��
	CVector3 move_direction_x;	//�������ւ̃x�N�g��
};

