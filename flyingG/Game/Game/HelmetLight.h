#pragma once
class HelmetLight : public IGameObject
{
public:
	HelmetLight();
	~HelmetLight();

	void Update();

	void Render(CRenderContext&);

	CSkinModelData modeldata;
	CSkinModel model;
	CVector3 position;
	CQuaternion rotation;
	CLight light;
};

