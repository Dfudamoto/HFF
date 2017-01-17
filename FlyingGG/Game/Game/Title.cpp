#include "stdafx.h"
#include "Title.h"


namespace
{
	const CVector2 TitleMaxSize = { 1330.5f, 730.5f };			//�^�C�g���̔w�i�̃T�C�Y
	const CVector2 TitlePos = { -650.0f, 0.0f };				//�^�C�g���̔w�i�̃|�W�V����
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
	m_TitleTex.Load("Assets/sprite/title.png");
	m_Title.Init(&m_TitleTex);
	m_Title.SetSize(TitleMaxSize);
	m_Title.SetPivot({ 0.0f,0.5f });
	m_Title.SetPosition(TitlePos);

	//CSoundSource *m_TitleSound = NewGO<CSoundSource>(0);
	//�^�C�g����ʂ�BGM
	//m_TitleSound->Init("Assets/sound/SE/BGM/�^�C�g��/musicbox.wav");
	//m_TitleSound->Play(true);
	//m_TitleSound.InitStreaming("Assets / sound / musicbox.wav");
	


}

void Title::Update()
{
	
}

void Title::PostRender(CRenderContext& renderContext)
{
	m_Title.Draw(renderContext);
}