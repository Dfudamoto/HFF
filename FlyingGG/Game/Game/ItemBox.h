#pragma once
class ItemBox : public IGameObject
{
public:
	ItemBox();
	~ItemBox();

	void Update();

	void Init(const char*, CVector3&, CQuaternion&);

	void Render(CRenderContext&);

	CSkinModel model;
	CSkinModelData modeldata;
	CLight light;
	CVector3 position;
	CQuaternion rotation;
};

