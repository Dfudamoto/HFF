#include "stdafx.h"
#include "HeelingApple.h"
#include "GameCamera.h"

extern GameCamera* gamecamera;


HeelingApple::HeelingApple()
{
}


HeelingApple::~HeelingApple()
{
	modelData.LoadModelData("Assets/modelData/P47_0.X", NULL);
	model.Init(&modelData);
	light.SetAmbinetLight({ 1.0f,1.0f,1.0f });
	model.SetLight(&light);
}

void HeelingApple::Init(const char *modelname, CVector3 position, CQuaternion rotation)
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
}

void HeelingApple::Update() 
{

}

void HeelingApple::Render(CRenderContext& renderContext) {
	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}
