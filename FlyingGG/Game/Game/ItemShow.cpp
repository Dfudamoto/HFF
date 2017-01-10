#include "stdafx.h"
#include "ItemShow.h"

int itemnum;

ItemShow::ItemShow()
{
	applet.ExLoad("Assets/sprite/apple.png");
	bombt.ExLoad("Assets/sprite/bomb.png");
	knifet.ExLoad("Assets/sprite/knife.png");
	sprite.Init(&applet);
	sprite.SetPivot({ 0.5f, 0.5f });
	sprite.SetSize({100.0f, 100.0f});
	sprite.SetPosition({ -580.0f, -300.0f });
	itemnum = 0;

	sprite.SetTexture(&applet);
}


ItemShow::~ItemShow()
{
}


void ItemShow::Update()
{
	if (Pad(0).IsTrigger(enButtonLB1) && itemnum > 0)
	{
		itemnum--;
	}
	if (Pad(0).IsTrigger(enButtonRB1) && itemnum < ITEMNUM - 1)
	{
		itemnum++;
	}
	switch (itemnum)
	{
	case APPLE:
		sprite.SetTexture(&applet);
		break;
	case BOMB:
		sprite.SetTexture(&bombt);
		break;
	case KNIFE:
		sprite.SetTexture(&knifet);
		break;
	}
}


void ItemShow::Render(CRenderContext& rendercontext)
{
	sprite.Draw(rendercontext);
}