#include "stdafx.h"
#include "Title.h"


namespace {
	const CVector2 TitleMaxSize = { 1330.5f, 730.5f };			//タイトルの背景のサイズ
	const CVector2 TitlePos = { -650.0f, 0.0f };				//タイトルの背景のポジション

	const CVector2 TitleLogoMaxSize = { 530.5f, 200.5f };		//タイトルロゴのサイズ
	const CVector2 TitleLogoPos = { -250.0f, 200.0f };			//タイトルロゴのポジション

	const CVector2 ChoicesMaxSize = { 300.0f, 50.0f };			//タイトルメニューのサイズ

	const CVector2 Choices1Pos = { 100.0f, -100.0f };			//タイトルの第1選択肢のポジション
	const CVector2 Choices2Pos = { 100.0f, -200.0f };			//タイトルの第2選択肢のポジション
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
	m_TitleTex.Load("Assets/sprite/TitleBack.png");
	m_Title.Init(&m_TitleTex);
	m_Title.SetSize(TitleMaxSize);
	m_Title.SetPivot({ 0.0f,0.5f });
	m_Title.SetPosition(TitlePos);
	
	//タイトルロゴ
	m_TitleLogoTex.Load("Assets/sprite/TitleName.png");
	m_TitleLogo.Init(&m_TitleLogoTex);
	m_TitleLogo.SetSize(TitleLogoMaxSize);
	m_TitleLogo.SetPivot({ 0.0f,0.5f });
	m_TitleLogo.SetPosition(TitleLogoPos);

	//タイトル選択肢1
	m_Choices1Tex.Load("Assets/sprite/Start.png");
	m_Choices1.Init(&m_Choices1Tex);
	m_Choices1.SetSize(ChoicesMaxSize);
	m_Choices1.SetPivot({ 0.0f,0.5f });
	m_Choices1.SetPosition(Choices1Pos);

	//タイトル選択肢2
	m_Choices2Tex.Load("Assets/sprite/Exit.png");
	m_Choices2.Init(&m_Choices2Tex);
	m_Choices2.SetSize(ChoicesMaxSize);
	m_Choices2.SetPivot({ 0.0f,0.5f });
	m_Choices2.SetPosition(Choices2Pos);

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
	m_TitleLogo.Draw(renderContext);
	m_Choices1.Draw(renderContext);
	m_Choices2.Draw(renderContext);
}