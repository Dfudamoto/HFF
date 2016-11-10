#pragma once
class HelmetLight : public IGameObject
{
public:
	HelmetLight();
	~HelmetLight();

	//更新関数
	void Update();

	//描画処理
	void Render(CRenderContext&);

	//プレイヤーが拾うかのチェック処理
	void Equip();

	CSkinModelData modeldata;	//モデル
	CSkinModel model;			//モデルデータ
	CVector3 position;			//場所
	CQuaternion rotation;		//モデルの向き
	CLight light;				//ライト
	bool getflg;				//プレイヤーが拾ったかのフラグ
	bool lightswitch;			//ライトのON/OFF
};

