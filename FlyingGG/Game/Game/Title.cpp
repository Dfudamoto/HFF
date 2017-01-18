#include "stdafx.h"
#include "Title.h"


namespace
{
	const CVector2 TitleMaxSize = { 1330.5f, 730.5f };			//タイトルの背景のサイズ
	const CVector2 TitlePos = { -650.0f, 0.0f };				//タイトルの背景のポジション
}

Title::Title()
{
}


Title::~Title()
{
}

void Title::Start()
{
	//タイトル背景
	m_TitleTex.Load("Assets/sprite/title.png");
	m_Title.Init(&m_TitleTex);
	m_Title.SetSize(TitleMaxSize);
	m_Title.SetPivot({ 0.0f,0.5f });
	m_Title.SetPosition(TitlePos);

	CSoundSource *m_TitleSound = NewGO<CSoundSource>(0);
	//タイトル画面のBGM
	m_TitleSound->Init("Assets/sound/SE/BGM/タイトル/musicbox.wav");
	m_TitleSound->Play(true);
	//m_TitleSound.InitStreaming("Assets / sound / musicbox.wav");
	


}

void Title::Update()
{
	
}

void Title::PostRender(CRenderContext& renderContext)
{
	m_Title.Draw(renderContext);
}