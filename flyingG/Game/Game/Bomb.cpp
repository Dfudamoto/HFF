#include "stdafx.h"
#include "Bomb.h"
#include "GameCamera.h"
#include "Player.h"
#include "time.h"

extern GameCamera *gamecamera;
extern Player *player;
Bomb *bomb;
CRandom random;


Bomb::Bomb()
{
	random.Init((unsigned int)+time(NULL));
	modeldata.LoadModelData("Assets/modelData/testbomb.x", NULL);
	model.Init(&modeldata);
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	position = player->position;
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	CMatrix matrix = player->model.GetWorldMatrix();
	axisx.x = matrix.m[0][0];
	axisx.y = matrix.m[0][1];
	axisx.z = matrix.m[0][2];
	axisx.Normalize();
	move_direction.x = matrix.m[2][0];
	move_direction.y = matrix.m[2][1];
	move_direction.z = matrix.m[2][2];
	move_direction.Scale(0.3f);
	fallspeed = 0.3f;
}

Bomb::~Bomb()
{

}

void Bomb::Update()
{
	float gravity = -0.0108f;
	position.Add(move_direction);
	fallspeed += gravity;
	position.y += fallspeed;

	//���f���̉�]
	CQuaternion multi;
	multi.SetRotation(axisx, CMath::DegToRad(-10));
	rotation.Multiply(multi);

	CollCheck();
	//���f���̍X�V
	model.Update(position, rotation, CVector3::One);
}

void Bomb::CollCheck()
{
	if (position.y < 0.0f)
	{
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
		DeleteGO(this);
	}
}

void Bomb::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

