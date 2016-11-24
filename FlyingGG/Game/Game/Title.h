#pragma once
class Title :public IGameObject
{
public:
	Title();
	~Title();
	void Start();
	void Update();
	void PostRender(CRenderContext& renderContext);
private:
	CSprite	 m_Title;				//�^�C�g��
	CSprite	 m_TitleLogo;			//�^�C�g�����S
	CSprite  m_Choices1;			//�I����1
	CSprite  m_Choices2;			//�I����2
	CTexture m_TitleTex;			//�^�C�g����ʂ̃e�N�X�`��
	CTexture m_TitleLogoTex;		//�^�C�g�����S�̃e�N�X�`��
	CTexture m_Choices1Tex;			//�I����1�̃e�N�X�`��
	CTexture m_Choices2Tex;			//�I����2�̃e�N�X�`��

};

