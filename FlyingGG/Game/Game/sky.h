#pragma once

//���f�����e�X�g�\��������N�\�N���X
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

