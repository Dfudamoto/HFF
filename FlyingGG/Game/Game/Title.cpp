#include "stdafx.h"
#include "Title.h"


namespace {
	const CVector2 TitleMaxSize = { 1330.5f, 730.5f };			//�^�C�g���̔w�i�̃T�C�Y
	const CVector2 TitlePos = { -650.0f, 0.0f };				//�^�C�g���̔w�i�̃|�W�V����

	const CVector2 TitleLogoMaxSize = { 530.5f, 200.5f };		//�^�C�g�����S�̃T�C�Y
	const CVector2 TitleLogoPos = { -250.0f, 200.0f };			//�^�C�g�����S�̃|�W�V����

	const CVector2 ChoicesMaxSize = { 300.0f, 50.0f };			//�^�C�g�����j���[�̃T�C�Y

	const CVector2 Choices1Pos = { 100.0f, -100.0f };			//�^�C�g���̑�1�I�����̃|�W�V����
	const CVector2 Choices2Pos = { 100.0f, -200.0f };			//�^�C�g���̑�2�I�����̃|�W�V����
}

Title::Title()
{
}


Title::~Title()
{
}

void Title::Start()
{
	//�^�C�g���w�i
	m_TitleTex.Load("Assets/sprite/shoes.png");
	m_Title.Init(&m_TitleTex);
	m_Title.SetSize(TitleMaxSize);
	m_Title.SetPivot({ 0.0f,0.5f });
	m_Title.SetPosition(TitlePos);
	
	//�^�C�g�����S
	m_TitleLogoTex.Load("Assets/sprite/shoes.png");
	m_TitleLogo.Init(&m_TitleLogoTex);
	m_TitleLogo.SetSize(TitleLogoMaxSize);
	m_TitleLogo.SetPivot({ 0.0f,0.5f });
	m_TitleLogo.SetPosition(TitleLogoPos);

	//�^�C�g���I����1
	m_Choices1Tex.Load("Assets/sprite/shoes.png");
	m_Choices1.Init(&m_Choices1Tex);
	m_Choices1.SetSize(ChoicesMaxSize);
	m_Choices1.SetPivot({ 0.0f,0.5f });
	m_Choices1.SetPosition(Choices1Pos);

	//�^�C�g���I����2
	m_Choices2Tex.Load("Assets/sprite/shoes.png");
	m_Choices2.Init(&m_Choices2Tex);
	m_Choices2.SetSize(ChoicesMaxSize);
	m_Choices2.SetPivot({ 0.0f,0.5f });
	m_Choices2.SetPosition(Choices2Pos);

	CSoundSource *m_TitleSound = NewGO<CSoundSource>(0);
	//�^�C�g����ʂ�BGM
	m_TitleSound->Init("Assets/sound/SE/BGM/�^�C�g��/musicbox.wav");
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