#pragma once
class HeelingApple
{
public:
	HeelingApple();
	~HeelingApple();
	void Update();
	void Render(CRenderContext& renderContext);
	void Init(const char *, CVector3, CQuaternion);

	CSkinModelData modeldata;
	CSkinModel model;
	CLight light;
	CVector3 position;
	CQuaternion rotation;
};

