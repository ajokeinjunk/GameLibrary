#include "KJ_Shader.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"
#include "../KJ_SceneGraph/SceneGraph.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//			DX11_VertexShaderクラス
	//========--------========--------========--------========--------========
	bool DX11_VertexShader::SetUpRenderer(const Scene3DGraph scene, const Scene3DNode& node){
		bool success = true;
		//ピクセルシェーダセット
		Renderer->m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
		Renderer->m_pDeviceContext->IASetInputLayout(m_pVertexLayout);

		//行列セット

		return success;
	}

	//========--------========--------========--------========--------========
	//			DX11_PixelShaderクラス
	//========--------========--------========--------========--------========
	bool DX11_PixelShader::SetUpRenderer(const Scene3DGraph scene, const Scene3DNode& node){
		bool success = true;
		//ピクセルシェーダセット
		Renderer->m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

		//行列セット

		return success;
	}

}