#include "stdafx.h"
#include "ItemBox.h"
#include "GameCamera.h"
#include "Player.h"

extern GameCamera *gamecamera;
extern Player *player;

ItemBox::ItemBox()
{
	light.SetAmbinetLight(CVector3::One);
}


ItemBox::~ItemBox()
{
}

void ItemBox::Init(const char *modelname, CVector3& position, CQuaternion& rotation)
{
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelname);
	//モデルデータをロード。
	modeldata.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	model.Init(&modeldata);

	//デフォルトライトを設定して。
	model.SetLight(&light);
}
void ItemBox::Update()
{

	CVector3 distance;
	distance.Subtract(position, player->position);
	if (distance.Length() < player->radius && Pad(0).IsTrigger(enButtonB))
	{
		DeleteGO(this);
	}
	model.Update(position, rotation, CVector3::One);
}

void ItemBox::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}