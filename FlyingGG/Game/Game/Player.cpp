#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Bomb.h"
#include "HealingApple.h"
#include "ItemShow.h"
#include "Enemy.h"

extern GameCamera *gamecamera;
extern Bomb *bomb[BOMBNUM];
extern int itemnum;
extern HealingApple *apple[APPLENUM];
extern Enemy *enemy[ENEMYNUM];

Player::Player()
{

	light.SetAmbinetLight(CVector3::One);
	//player_modelresource.Load(player_data, "Assets/modelData/bodyg_alpha.X", &player_animation);
	//player_model.Init(player_data.GetBody());
	//player_model.SetLight(&light);
	//knife_modelresource.Load(knife_data, "Assets/modelData/knife.X", &knife_animation);
	//knife_model.Init(knife_data.GetBody());
	//knife_model.SetLight(&light);
	position = CVector3::Zero;
	position = {0.0f, 3.0f, 0.0f };
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	characterController.Init(0.5f, 0.5f, position);
	radius = 3.0f;
	hp = MAXHP;
	itemnum = 0;
	animenum = 0;
	bombcount = 0;
	applecount = 0;
	nockbackflg = false;
	speedup_flg = false;
	speedup_count = 0.0f;
	attackflg = false;
}

Player::~Player()
{

}

void Player::Init(CVector3 position, CQuaternion rotation)
{ 
	player_modelresource.Load(player_data, "Assets/modelData/bodyg_alpha.X", &player_animation);
	player_model.Init(player_data.GetBody());
	player_model.SetLight(&light);
	knife_modelresource.Load(knife_data, "Assets/modelData/knife.X", &knife_animation);
	knife_model.Init(knife_data.GetBody());
	knife_model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	//�f�t�H���g���C�g��ݒ肵�āB
	player_model.SetLight(&light);
	knife_model.SetLight(&light);
	characterController.Init(0.3f, 0.3f, position);
	characterController.SetMoveSpeed(CVector3::Zero);
	player_model.Update(position, rotation, CVector3::One);
	knife_model.Update(position, rotation, CVector3::One);
	player_animation.SetAnimationLoopFlag(KNIFE, false);
	player_animation.SetAnimationLoopFlag(BOMBTHROW, false);
	knife_animation.SetAnimationLoopFlag(1, false);
	initpos = position;
	initrot = rotation;
}

void Player::Update()
{
	attackflg = false;
	if (Pad(0).IsTrigger(enButtonLB3))
	{
		hp = 0;
	}
	if (Pad(0).IsTrigger(enButtonX))
	{
		switch (itemnum)
		{
		case ItemShow::KNIFE:
			if (player_animation.GetPlayAnimNo() != KNIFE || (player_animation.GetPlayAnimNo() == KNIFE && !player_animation.IsPlay()))
			{
				player_animation.PlayAnimation(KNIFE);
				knife_animation.PlayAnimation(1);
				attackflg = true;
			}
			break;
		case ItemShow::BOMB:
			if (bombcount > 0)
			{
				player_animation.PlayAnimation(BOMBTHROW);
			}
			break;
		}
	}
	if (!characterController.IsJump())
	{
		nockbackflg = false;
	}
	Move();
	Rotation();
	//�L�����N�^�[�R���g���[���[�����s�B
	characterController.Execute();
	//���s���ʂ��󂯎��B
	position = characterController.GetPosition();
	position.y += HEIGHT;
	player_animation.Update(3.0f / 60.0f);
	player_model.Update(position, rotation, CVector3::One);
	knife_animation.Update(3.0f / 60.0f);
	knife_model.Update(position, rotation, CVector3::One);
	if (position.y < -30.0f)
	{
		hp = 0;
	}
}

void Player::Move()
{
	if (nockbackflg)
	{
		return;
	}
	CVector3 move_direction_z;	//���ʂւ̃x�N�g��
	CVector3 move_direction_x;	//�������ւ̃x�N�g��

	//�v���C���[�̑O(���)�����̃x�N�g�����擾
	CMatrix matrix = player_model.GetWorldMatrix();
	float speedscale = 10.0f;
	move_direction_z.x = matrix.m[2][0];
	move_direction_z.z = matrix.m[2][2];
	move_direction_z.y = 0.0f;
	move_direction_z.Normalize();
	hitbox_position = move_direction_z;
	move_direction_z.Scale(speedscale);
	move_direction_z.Scale(Pad(0).GetLStickYF());
	if (speedup_flg)
	{
		move_direction_z.Scale(2.0f);
		speedup_count += 1.0f;
		if (speedup_count >= 300.0f)
		{
			speedup_flg = false;
		}
	}
	
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
	hitbox_position.Scale(0.3f);
	hitbox_position.Add(position);
}

void Player::Rotation()
{
	//�v���C���[�̉�]�p�x�Ɖ�]���x
	float anglespeed = 5.0f;
	static float anglex = 0.0f;
	static float angley = 0.0f;

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

void Player::Delete()
{
	player_model.SetShadowCasterFlag(false);
	characterController.RemoveRigidBoby();
	DeleteGO(this);
}

void Player::NockBack()
{
	characterController.Jump();
	CMatrix matrix = player_model.GetWorldMatrix();
	CVector3 movespeed;
	movespeed.x = -matrix.m[2][0];
	movespeed.y = 0.0f;
	movespeed.z = -matrix.m[2][2];
	movespeed.Normalize();
	movespeed.Scale(10.0f);
	movespeed.y += 5.0f;
	characterController.SetMoveSpeed(movespeed);
	characterController.Execute();
	nockbackflg = true;
}

void Player::ReInit()
{
	hp = MAXHP;
	position = initpos;
	rotation = initrot;
}
