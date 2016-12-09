#pragma once

//モデルをテスト表示させるクソクラス
class sky : public IGameObject
{
public:
	sky();
	~sky();
	void Update();

	void Render(CRenderContext&);

	CSkinModel		model;		//モデル
	CSkinModelData	modeldata;	//モデルのデータ
	CQuaternion		rotation;	//モデルの回転率
};

