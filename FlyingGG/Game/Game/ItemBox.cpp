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
extern CLight darklight;


ItemBox::ItemBox()
{
	light.SetAmbinetLight({0.01f, 0.01f,0.01f});
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
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
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModel���������B
	model.Init(modeldata.GetBody());
	//�f�t�H���g���C�g��ݒ肵�āB
	model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	//model.SetFogParam(enFogFuncDist, 0.0f, 30.0f);
	model.Update(position, rotation, CVector3::One);
	model.SetShadowCasterFlag(true);
	model.SetShadowReceiverFlag(true);
	//���b�V���R���C�_�[�̍쐬�B
	meshcollider.CreateFromSkinModel(&model, modeldata.GetBody()->GetRootBoneWorldMatrix());
	//���̂̍쐬�B
	RigidBodyInfo rbInfo;
	//���̂̃R���C�_�[��n���B
	rbInfo.collider = &meshcollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidbody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	PhysicsWorld().AddRigidBody(&rigidbody);
}
void ItemBox::Update()
{
	BombCreate();
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	distance.Scale(0.2f);

	direction.Normalize();
	float lightscale = 1.0f / distance.Length();
	if (distance.Length() > 1.0f)
	{
		direction.Scale(lightscale);

	}
	light.SetDiffuseLightDirection(0, direction);
	model.Update(position, rotation, CVector3::One);
}

void ItemBox::BombCreate()
{
	if (itemnum != ItemShow::KNIFE)
	{
		return;
	}
	//�v���C���[�Ƃ̋����Ƒ���
	CVector3 distance;
	distance.Subtract(position, player->hitbox_position);
	if (distance.Length() < player->radius && Pad(0).IsTrigger(enButtonX))
	{
		//������̋����Ń{�^���������ꂽ������ă{��������
		Delete();
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
}

void ItemBox::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void ItemBox::Delete()
{
	model.SetShadowCasterFlag(false);
	PhysicsWorld().RemoveRigidBody(&rigidbody);
	rigidbody.Release();
	DeleteGO(this);
}