#pragma once

//モデルをテスト表示させるクソクラス
class sky : public IGameObject
{
public:
	sky();
	~sky();
	void Update();

	void Render(CRenderContext&);

	CSkinModel model;
	CSkinModelData modeldata;
	CQuaternion rotation;
};

