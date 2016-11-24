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
	CSprite	 m_Title;				//タイトル
	CSprite	 m_TitleLogo;			//タイトルロゴ
	CSprite  m_Choices1;			//選択肢1
	CSprite  m_Choices2;			//選択肢2
	CTexture m_TitleTex;			//タイトル画面のテクスチャ
	CTexture m_TitleLogoTex;		//タイトルロゴのテクスチャ
	CTexture m_Choices1Tex;			//選択肢1のテクスチャ
	CTexture m_Choices2Tex;			//選択肢2のテクスチャ

};

