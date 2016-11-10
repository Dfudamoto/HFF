#pragma once
class Bomb : public IGameObject
{
public:
	Bomb();
	~Bomb();

	//�X�V�֐�
	void Update();

	//�`�揈��
	void Render(CRenderContext&);

	//�����ɓ������Ă��邩���肷�鏈��
	void CollCheck();

	CSkinModel model;			//���f��	
	CSkinModelData modeldata;	//���f���f�[�^
	CLight light;				//���C�g
	CVector3 position;			//�ꏊ
	CVector3 move_direction;	//��ԕ���
	CVector3 axisx;				//��]���鎲
	CQuaternion rotation;		//���f���̌���
	float fallspeed;

};
