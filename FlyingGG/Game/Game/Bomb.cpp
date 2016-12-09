#include "stdafx.h"
#include "Bomb.h"
#include "GameCamera.h"
#include "Player.h"
#include "time.h"
#include "ItemShow.h"

extern GameCamera *gamecamera;
extern Player *player;
CRandom random;
extern CLight darklight;
extern Bomb* bomb[BOMBNUM];
extern int itemnum;

Bomb::Bomb()
{
	random.Init((unsigned int)+time(NULL));
	modelresource.Load(modeldata, "Assets/modelData/bomb.X", NULL);
	model.Init(modeldata.GetBody());
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	model.SetShadowCasterFlag(true);
	fallspeed = 0.3f;
	angle = 0;
	charactercontroller.SetPickUp(false);
}

Bomb::~Bomb()
{

}



void Bomb::Init(CVector3 position)
{
	//modeldata.LoadModelData("Assets/modelData/bomb.X", NULL);
	//model.Init(&modeldata);
	this->position = position;
	move_speed = CVector3::Zero;
	axisx = CVector3::AxisY;
	charactercontroller.Init(0.5f, 0.5f, this->position);
}

void Bomb::Update()
{
	charactercontroller.SetMoveSpeed(move_speed);
	charactercontroller.Execute();
	position = charactercontroller.GetPosition();
	move_speed = charactercontroller.GetMoveSpeed();
	//���f���̉�]
	CQuaternion multi;
	multi.SetRotation(axisx, CMath::DegToRad(-angle));
	rotation.Multiply(multi);

	CollCheck();
	Throw();
	
	//���f���̍X�V
	model.Update(position, rotation, CVector3::One);
}

void Bomb::Throw()
{
	//�������Ă����ԂȂ�return����
	if (throwflg)
	{
		return;
	}
	//�{���̋߂���X�{�^���������ƏE��
	CVector3 distance;
	distance.Subtract(position, player->position);
	if (distance.Length() < 10.0f && Pad(0).IsTrigger(enButtonX) && !charactercontroller.IsPickUp())
	{
		charactercontroller.SetPickUp(true);
	}


	if (charactercontroller.IsPickUp())
	{
		position = player->position;
		charactercontroller.SetGravity(0.0f);
		charactercontroller.SetPosition(position);
		//�E������Ԃ�A�{�^���������Ɠ�����
		if (itemnum != ItemShow::BOMB)
		{
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			for (int i = 0;i < BOMBNUM;i++)
			{
				//���̃{�����������Ă���Γ�����Ȃ�
				if (bomb[i] != nullptr && bomb[i]->throwflg)
				{
					return;
				}
			}
			throwflg = true;
			charactercontroller.SetGravity(-9.8f);
			CMatrix matrix = player->model.GetWorldMatrix();
			//�{���󒆂ɂ���Ԃ̉�]��
			axisx.x = matrix.m[0][0];
			axisx.y = matrix.m[0][1];
			axisx.z = matrix.m[0][2];
			axisx.Normalize();
			//�{������ԕ���
			move_direction.x = matrix.m[2][0];
			move_direction.y = matrix.m[2][1];
			move_direction.z = matrix.m[2][2];
			move_direction.Normalize();
			CVector3 addpos = move_direction;
			addpos.Scale(0.3f);
			position.Add(addpos);//�v���C���[�ɂ�������̂ŏ����O�ɂ��炷
			move_direction.Scale(10.0f);
			move_speed = move_direction;
			move_speed.y += 5.0f;
			angle = 10;
		}
	}
}

void Bomb::CollCheck()
{
	if (!charactercontroller.IsCollision())
	{
		if(!throwflg)
		{
			move_speed = CVector3::Zero;
			angle = 0;
		}
		return;
	}
	if (itemnum != ItemShow::BOMB)
	{
		return;
	}
	//�����ɓ���������p�[�e�B�N�����o���Ď��S
	//�p�[�e�B�N�����o������
	CParticleEmitter *particle;
	particle = NewGO<CParticleEmitter>(0);
	particle->Init(random, gamecamera->camera,
	{
	"Assets/effect/realExplosion.png",				//!<�e�N�X�`���̃t�@�C���p�X�B
	{0.0f, 0.0f, 0.0f},								//!<�����x�B
	1.0f,											//!<�����B�P�ʂ͕b�B
	1.0f,											//!<�������ԁB�P�ʂ͕b�B
	5.0f,											//!<�p�[�e�B�N���̕��B
	5.0f,											//!<�p�[�e�B�N���̍����B
	{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
	{ 0.0f, 0.0f, 0.0f },							//!<�����x�̃����_�����B
	{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
	{
		{ 0.0f, 0.0f, 0.333f, 0.3333f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f }
	},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
	1,												//!<UV�e�[�u���̃T�C�Y�B
	{ 0.0f, 0.0f, 0.0f },							//!<�d�́B
	true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
	0.3f,											//!<�t�F�[�h���鎞�ԁB
	1.0f,											//!<�����A���t�@�l�B
	true,											//!<�r���{�[�h�H
	0.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	0,												//!<0�����������A1���Z�����B
	{1.0f, 1.0f, 1.0f},								//!<��Z�J���[�B
	},
	position);
	model.SetShadowCasterFlag(false);
	charactercontroller.RemoveRigidBoby();
	//�����{���̏������Z�b�g
	for (int i = 0;i < BOMBNUM;i++)
	{
		if (bomb[i] != nullptr && bomb[i]->charactercontroller.IsDead())
		{
			bomb[i] = nullptr;
		}
	}
	player->BombDam(position);
	DeleteGO(this);
}

void Bomb::Render(CRenderContext& rendercontext)
{
	if (charactercontroller.IsPickUp() && !throwflg)
	{
		return;
	}
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

