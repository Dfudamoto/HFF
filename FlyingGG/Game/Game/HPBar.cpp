#include "stdafx.h"
#include "HPBar.h"


HPBar::HPBar()
{
	hp.Load("Assets/sprite/hp.png");
	hpspr.Init(&hp);
	hpspr.SetPosition({0.0f, 0.0f});
	hpspr.SetPivot({ 0.5f, 0.5f });
}


HPBar::~HPBar()
{
}

void HPBar::Update()
{

}

void HPBar::Render(CRenderContext& rendercontext)
{
	hpspr.Draw(rendercontext);
}
