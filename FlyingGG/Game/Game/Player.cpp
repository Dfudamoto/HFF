#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Bomb.h"

extern GameCamera *gamecamera;
extern Bomb *bomb[BOMBNUM];

Player::Player()
{
	modelresource.Load(modeldata, "Assets/modelData/bodyg.X", NULL);
	modelresource.Load(bombdata, "Assets/modelData/bomb.X", NULL);
	//���f���̏�����

	model.Init(modeldata.GetBody());
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	position = CVector3::Zero;
	position = {0.0f, 3.0f, 0.0f };
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	characterController.Init(0.5f, 1.0f, position);
	radius = 3.0f;
	bombcount = 1;
	for (int i = 0;i < BOMBNUM;i++)
	{
		bomb[i] = nullptr;
	}
}

Player::~Player()
{

}

void Player::Update()
{
	//�{���𓊂���
	if (Pad(0).IsTrigger(enButtonA) && bombcount > 0)
	{
		//Bomb *bomb;
		//bomb = NewGO<Bomb>(0);
		//bomb->Init();
		//bombcount--;
	}
	Move();
	Rotation();
	model.Update(position, rotation, CVector3::One);
}

void Player::Move()
{

	CVector3 move_direction_z;	//���ʂւ̃x�N�g��
	CVector3 move_direction_x;	//�������ւ̃x�N�g��

	//�v���C���[�̑O(���)�����̃x�N�g�����擾
	CMatrix matrix = model.GetWorldMatrix();
	float speedscale = 30.0f;
	move_direction_z.x = matrix.m[2][0];
	move_direction_z.z = matrix.m[2][2];
	move_direction_z.y = 0.0f;
	move_direction_z.Normalize();
	move_direction_z.Scale(speedscale);
	move_direction_z.Scale(Pad(0).GetLStickYF());
	
	//�v���C���[�̉������ւ̃x�N�g���̎擾
	move_direction_x.x = matrix.m[0][0];
	move_direction_x.z = matrix.m[0][2];
	move_direction_x.y = 0.0f;
	move_direction_x.Normalize();
	move_direction_x.Scale(speedscale);
	move_direction_x.Scale(Pad(0).GetLStickXF());

	CVector3 move = characterController.GetMoveSpeed();
	//�O(���)�Ɖ��̈ړ��ʂ̑����Z
	move.x = 0.0f;
	move.z = 0.0f;
	move.Add(move_direction_x);
	move.Add(move_direction_z);
	//�W�����v����
	if (Pad(0).IsTrigger(enButtonB))
	{
		characterController.Jump();
		move.y = 10.0f;
	}
	//���肵���ړ����x���L�����N�^�R���g���[���[�ɐݒ�B
	characterController.SetMoveSpeed(move);
	//�L�����N�^�[�R���g���[���[�����s�B
	characterController.Execute();
	//���s���ʂ��󂯎��B
	position = characterController.GetPosition();
	position.y += 2.0f;

}

void Player::Rotation()
{
	//�v���C���[�̉�]�p�x�Ɖ�]���x
	float anglespeed = 5.0f;
	static float anglex = 0;
	static float angley = 0;

	angley += Pad(0).GetRStickXF() * anglespeed;
	//�v���C���[�̉�]�ł���p�x�̌��x�`�F�b�N
	if (MIN_ANGLE < anglex && -Pad(0).GetRStickYF() < 0
		|| anglex < MAX_ANGLE && 0 < -Pad(0).GetRStickYF())
	{
		anglex -= Pad(0).GetRStickYF() * anglespeed;
	}

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(angley));
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisX, CMath::DegToRad(anglex));
	rotation.Multiply(multi);
}

void Player::Render(CRenderContext& rendercontext)
{
	//model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

