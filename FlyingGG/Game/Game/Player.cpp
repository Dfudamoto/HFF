#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Bomb.h"
#include "HealingApple.h"

extern GameCamera *gamecamera;
extern Bomb *bomb[BOMBNUM];
extern int itemnum;
extern HealingApple *apple[APPLENUM];

Player::Player()
{
	modelresource.Load(player_data, "Assets/modelData/bodyg_alpha.X", &player_animation);
	modelresource.Load(knife_data, "Assets/modelData/knife.X", &knife_animation);
	//���f���̏�����
	player_model.Init(player_data.GetBody());
	knife_model.Init(knife_data.GetBody());
	light.SetAmbinetLight(CVector3::One);
	player_model.SetLight(&light);
	knife_model.SetLight(&light);
	position = CVector3::Zero;
	position = {0.0f, 3.0f, 0.0f };
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	characterController.Init(0.5f, 1.0f, position);
	radius = 3.0f;


	hp = MAXHP;
	itemnum = 0;
	animenum = 0;
	//player_animation.SetAnimationLoopFlag(0, false);	
	knife_animation.SetAnimationLoopFlag(0, false);
}

Player::~Player()
{

}

void Player::Update()
{
	if (Pad(0).IsTrigger(enButtonA))
	{
		player_animation.PlayAnimation(animenum);
		if (animenum == KNIFE)
		{
			knife_animation.PlayAnimation(0);
		}
	}
	if (Pad(0).IsTrigger(enButtonLB1) && 0 < animenum)
	{
		animenum--;
	}
	if (Pad(0).IsTrigger(enButtonRB1) && animenum < ANIMATIONNUM - 1)
	{
		animenum++;
	}
	Move();
	Rotation();
	player_animation.Update(3.0f / 60.0f);
	knife_animation.Update(3.0f / 60.0f);
	player_model.Update(position, rotation, CVector3::One);
	knife_model.Update(position, rotation, CVector3::One);
}

void Player::Move()
{
	CVector3 move_direction_z;	//���ʂւ̃x�N�g��
	CVector3 move_direction_x;	//�������ւ̃x�N�g��

	//�v���C���[�̑O(���)�����̃x�N�g�����擾
	CMatrix matrix = player_model.GetWorldMatrix();
	float speedscale = 10.0f;
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
	position.y += HEIGHT;
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
		anglex += -Pad(0).GetRStickYF() * anglespeed;
	}

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(angley));
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisX, CMath::DegToRad(anglex));
	rotation.Multiply(multi);
}

void Player::Render(CRenderContext& rendercontext)
{
	player_model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
	knife_model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void Player::BombDam(CVector3& bombpos)
{
	CVector3 distance;
	distance.Subtract(position, bombpos);
	if (distance.Length() < 20.0f)
	{
		hp -= 10;
	}
}
