#include "stdafx.h"
#include "DebuffItem.h"
#include "GameCamera.h"
#include "Player.h"
#include "ItemShow.h"

extern int itemnum;
extern Player *player;
extern GameCamera *gamecamera;
extern DebuffItem *debuffitem[DEBUFFNUM];

DebuffItem::DebuffItem()
{
	light.SetAmbinetLight(CVector3::One);
	//light.SetAmbinetLight({0.01f, 0.01f, 0.01f});
	//light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	harves = false;
	deleteflg = false;
}

DebuffItem::~DebuffItem()
{
}

void DebuffItem::Init(const char *modelname, CVector3 position, CQuaternion rotation)
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
	charactercontroller.Init(0.3f, 0.3f, position);
	charactercontroller.SetMoveSpeed(CVector3::Zero);
	model.Update(position, rotation, CVector3::One);
}

void DebuffItem::Update()
{
	CVector3 distance;
	distance.Subtract(position, player->position);
	Eatable();
	PickUp();
	Move();
	distance.Normalize();
	light.SetDiffuseLightDirection(0, distance);
	model.Update(position, rotation, CVector3::One);
}

void DebuffItem::Render(CRenderContext& renderContext) {
	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}
void DebuffItem::Move()
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


void DebuffItem::PickUp()
{
	//�؂��痎���ĂȂ���΃��^�[��
	if (!harves)
	{
		return;
	}
	CVector3 distance;
	distance.Subtract(player->position, position);
	if (distance.Length() < player->radius && Pad(0).IsTrigger(enButtonA))
	{
		charactercontroller.SetPickUp(true);
		player->debuffcount++;
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
	if (Pad(0).IsTrigger(enButtonX))
	{
		for (int i = 0;i < APPLENUM;i++)
		{
			if (debuffitem[i] != nullptr && debuffitem[i]->deleteflg)
			{
				return;
			}
		}
		deleteflg = true;
	}
}

void DebuffItem ::Eatable()
{
	if (!deleteflg)
	{
		return;
	}
	if (itemnum != ItemShow::DEBUFFITEM)
	{
		return;
	}
	for (int i = 0;i < APPLENUM;i++)
	{
		if (debuffitem[i] != nullptr && debuffitem[i]->deleteflg)
		{
			debuffitem[i] = nullptr;
		}
	}
	player->debuffcount--;
	player->speedup_flg = true;
	player->speedup_count = 0.0f;
	Delete();
}

void DebuffItem::Delete()
{
	if (this == nullptr)
	{
		//return;
	}
	charactercontroller.RemoveRigidBoby();
	DeleteGO(this);
}
