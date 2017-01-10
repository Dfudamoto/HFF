/*!
 * @brief	テクスチャ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkTexture.h"

namespace tkEngine {
	/*!
	 * @brief	テクスチャをロード。
	 */
	bool CTexture::Load(const char* fileName)
	{
		LPDIRECT3DDEVICE9 device = Engine().GetD3DDevice();
		if ( FAILED( D3DXCreateTextureFromFile(
			device,
			fileName,
			&m_tex))) {
			TK_LOG("FailedTextureLoad");
			return false;
		}
		ComputeTexSize();
		return true;
	}

	bool CTexture::ExLoad(const char* filename)
	{
		LPDIRECT3DDEVICE9 device = Engine().GetD3DDevice();
		if (FAILED(D3DXCreateTextureFromFileEx(
			device,
			filename,
			0,
			0,
			0,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_FILTER_NONE,
			0xffffffff,
			NULL,
			NULL,
			&m_tex))) {
			TK_LOG("FailedTextureLoad");
			return false;
		}
		ComputeTexSize();
		return true;

	}
}