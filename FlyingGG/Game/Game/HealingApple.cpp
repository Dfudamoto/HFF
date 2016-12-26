#include "stdafx.h"
#include "HealingApple.h"
#include "GameCamera.h"
#include "Player.h"


extern Player* player;
extern GameCamera* gamecamera;
HealingApple *apple[APPLENUM];

HealingApple::HealingApple()
{	
	//light.SetAmbinetLight({ 100.0f, 100.0f, 100.0f });
	//light.SetAmbinetLight(CVector3::One);
	light.SetAmbinetLight({ 0.01f,0.01f,0.01f });
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	harves = false;
	deleteflg = false;
	charactercontroller.SetPickUp(false);
}

HealingApple::~HealingApple()
{

}

void HealingApple::Init(const char *modelname, CVector3 position, CQuaternion rotation)
{
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", modelname);
	//���f���f�[�^�����[�h�B
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModel���������B
	model.Init(modeldata.GetBody());
	//�f�t�H���g���C�g��ݒ肵�āB
	model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	CVector3 movespeed = { 0.0f, 0.0f, 0.0 };
	charactercontroller.SetMoveSpeed(movespeed);
	charactercontroller.Init(0.3f, 0.3f, position);
	model.Update(position, rotation, CVector3::One);
}

void HealingApple::Update() 
{
	float scale = 0.01f;
	Delete();
	PickUp();
	Move();
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	distance.Scale(scale);

	direction.Normalize();
	float lightscale = 1.0f / distance.Length();
	if (lightscale < 1.0f)
	{
		direction.Scale(lightscale);
	}
	light.SetDiffuseLightDirection(0, direction);

	model.Update(position, rotation, CVector3::One);
}

void HealingApple::Move()
{
	//�v���C���[�Ƃ̋������v�Z
	CVector3 distance;
	distance.Subtract(position, player->position);
	if (Pad(0).IsTrigger(enButtonX) && distance.Length() < 10.0f)
	{
		harves = true;
	}
	if (!harves)
	{
		return;
	}
	//�ړ��i�����j����
	charactercontroller.Execute();
	CVector3 movespeed = charactercontroller.GetMoveSpeed();
	charactercontroller.SetMoveSpeed(movespeed);
	position = charactercontroller.GetPosition();


}

void HealingApple::Render(CRenderContext& renderContext) 
{

	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}

void HealingApple::PickUp()
{
	//�؂��痎���ĂȂ���΃��^�[��
	if (!harves)
	{
		return;
	}
	CVector3 distance;
	distance.Subtract(player->position, position);
	if (distance.Length() < player->radius && Pad(0).IsTrigger(enButtonX))
	{
		charactercontroller.SetPickUp(true);
	}
	//�E���ĂȂ������烊�^�[��
	if (!charactercontroller.IsPickUp())
	{
		return;
	}
	position = player->position;
	position.y += 100.0f;
	charactercontroller.SetGravity(0.0f);
	charactercontroller.SetPosition(position);
	if (Pad(0).IsTrigger(enButtonA))
	{
		for (int i = 0;i < APPLENUM;i++)
		{
			if (apple[i] != nullptr && apple[i]->deleteflg)
			{
				return;
			}
		}
		deleteflg = true;
	}
}

void HealingApple::Delete()
{
	if (!deleteflg)
	{
		return;
	}
	for (int i = 0;i < APPLENUM;i++)
	{
		if (apple[i] != nullptr && apple[i]->deleteflg)
		{
			apple[i] = nullptr;
		}
	}
	if (player->hp < MAXHP)
	{
		player->hp += 10;
	}
	charactercontroller.RemoveRigidBoby();
	DeleteGO(this);
}
