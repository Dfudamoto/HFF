#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "HelmetLight.h"
#include "sky.h"
#include "Map.h"
#include "Title.h"
#include "HPBar.h"
#include "ItemShow.h"
#include "Scene.h"
#include "Enemy.h"

GameCamera *gamecamera;
Player *player;
Scene *scene;
extern Enemy *enemy[ENEMYNUM];

/*!
 * @brief	tkEngineの初期化。
 */
void InitTkEngine( HINSTANCE hInst )
{
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//コマンドバッファのサイズのテーブル。
	int commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//レンダリングコンテキストは一本
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	initParam.frameBufferHeight = 720;
	initParam.frameBufferWidth = 1280;
	//Bloom
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.Init();
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 2048;
	initParam.graphicsConfig.shadowRenderConfig.numShadowMap = 1;
	
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = false;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;
	//DOF
	//initParam.graphicsConfig.dofConfig.isEnable = true;
	//AA
	initParam.graphicsConfig.aaConfig.isEnable = true;

	Engine().Init(initParam);	//初期化。
	
	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(1000.0f);
	
}

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	//tkEngineの初期化。
	InitTkEngine( hInst );
	scene = nullptr;
	//NewGO<HelmetLight>(0);
	//NewGO<Map>(0);
	//NewGO<HPBar>(1);
	//NewGO<ItemShow>(1);
	//enemy[0] = NewGO<Enemy>(0);
	//NewGO<sky>(1);//モデルをテスト表示
	//NewGO<Title>(0);
	scene = NewGO<Scene>(0);
	Engine().RunGameLoop();		//ゲームループを実行。

	return 0;
}