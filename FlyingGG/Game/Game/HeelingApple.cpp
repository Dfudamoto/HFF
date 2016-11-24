#include "stdafx.h"
#include "HeelingApple.h"
#include "GameCamera.h"

extern GameCamera* gamecamera;


HeelingApple::HeelingApple()
{
}


HeelingApple::~HeelingApple()
{
	modeldata.LoadModelData("Assets/modelData/P47_0.X", NULL);
	model.Init(&modeldata);
	light.SetAmbinetLight({ 1.0f,1.0f,1.0f });
	model.SetLight(&light);
}

void HeelingApple::Init(const char *modelname, CVector3 position, CQuaternion rotation)
{
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", modelname);
	//モデルデータをロード。
	modeldata.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	model.Init(&modeldata);
	//デフォルトライトを設定して。
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
