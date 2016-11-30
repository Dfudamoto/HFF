#pragma once
class Pitfall : public IGameObject
{
public:
	Pitfall();
	~Pitfall();
	void Update();
	void Render(CRenderContext& renderContext);

	CSkinModelData modeldata;
	CSkinModel model;
};

