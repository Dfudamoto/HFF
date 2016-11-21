#include "stdafx.h"
#include "HeelingApple.h"
#include "GameCamera.h"

extern GameCamera* gameCamera;


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

void HeelingApple::Update() {

}

void HeelingApple::Render(CRenderContext& renderContext) {
	model.Draw(renderContext,
		gameCamera->camera.GetViewMatrix(),
		gameCamera->camera.GetProjectionMatrix()
	);
}
