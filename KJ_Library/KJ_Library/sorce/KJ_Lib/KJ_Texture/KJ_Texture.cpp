#include "KJ_Texture.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"

namespace Klibrary{
	bool BaseTexture::LoadTexture(char* filename){
		//リソースフォルダから取得
		//unmap使う。
		HRESULT result;
		result = D3DX11CreateShaderResourceViewFromFile(Renderer->m_pDevice, filename, nullptr, nullptr, &m_pTexture, nullptr);
		if (FAILED(result)){
			result = D3DX11CreateShaderResourceViewFromFile(Renderer->m_pDevice, "DATA\\NoTex.png", nullptr, nullptr, &m_pTexture, nullptr);

		}
		return true;
	}

	void BaseTexture::SendShader(jUInt32 slot){
		if (m_pTexture != nullptr){
			Renderer->m_pDeviceContext->PSSetShaderResources(slot, 1, &m_pTexture);
		}
	}
}