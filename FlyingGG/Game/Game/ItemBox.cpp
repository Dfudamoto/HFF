#include "stdafx.h"
#include "ItemBox.h"
#include "GameCamera.h"
#include "Player.h"
#include "Bomb.h"
#include "ItemShow.h"

extern int itemnum;
extern GameCamera *gamecamera;
extern Player *player;
Bomb *bomb[BOMBNUM];


ItemBox::ItemBox()
{
	light.SetAmbinetLight(CVector3::One);
}


ItemBox::~ItemBox()
{
}

void ItemBox::Init(const char *modelname, CVector3& position, CQuaternion& rotation)
{
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", modelname);
	//���f���f�[�^�����[�h�B
	modeldata.LoadModelData(filePath, NULL);
	//CSkinModel���������B
	model.Init(&modeldata);
	//�f�t�H���g���C�g��ݒ肵�āB
	model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	//model.SetFogParam(enFogFuncDist, 0.0f, 30.0f);
	model.Update(position, rotation, CVector3::One);
}
void ItemBox::Update()
{
	if (itemnum != ItemShow::KNIFE)
	{
		return;
	}
	//�v���C���[�Ƃ̋����Ƒ���
	CVector3 distance;
	distance.Subtract(position, player->position);
	if (distance.Length() < player->radius && Pad(0).IsTrigger(enButtonX))
	{
		//������̋����Ń{�^���������ꂽ������ă{��������
		DeleteGO(this);
		for (int i = 0;i < BOMBNUM;i++)
		{
			if (bomb[i] == nullptr)
			{
				bomb[i] = NewGO<Bomb>(0);
				bomb[i]->Init(position);
				break;
			}
		}
	}
	model.Update(position, rotation, CVector3::One);
}

void ItemBox::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}