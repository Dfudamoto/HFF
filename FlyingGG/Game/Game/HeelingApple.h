#pragma once
class HeelingApple
{
public:
	HeelingApple();
	~HeelingApple();
	CSkinModelData modelData;
	CSkinModel model;
	CLight light;
	void Update();
	void Render(CRenderContext& renderContext);
};

