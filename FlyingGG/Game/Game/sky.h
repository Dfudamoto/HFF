#pragma once
class sky : public IGameObject
{
public:
	sky();
	~sky();
	void Update();

	void Render(CRenderContext&);

	CSkinModel		model;		//���f��
	CSkinModelData	modeldata;	//���f���̃f�[�^
	CQuaternion		rotation;	//���f���̉�]��
};

