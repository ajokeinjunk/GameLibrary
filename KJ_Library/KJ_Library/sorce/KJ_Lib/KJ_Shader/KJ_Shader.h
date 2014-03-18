#pragma once

#include "../KJ_Renderer/KJ_DirectX/KJ_DirectX3D.h"
#include "../KJ_System/KJ_System.h"

namespace Klibrary{
	class Scene3DNode;
	class Scene3DGraph;

	/** ===================================================================================
	* @class DX11_VertexShader
	* @brief DirectX11専用頂点シェーダークラス
	* LayoutやShader,コンスタントバッファーや入力用バッファーを扱う。
	==================================================================================== */
	class DX11_VertexShader{
	protected:
		//!< @brief 頂点シェーダー入力レイアウト
		ID3D11InputLayout*  m_pVertexLayout;
		//!< @brief 頂点シェーダーデータ
		ID3D11VertexShader* m_pVertexShader;
		//!< @brief 行列用コンスタントバッファー
		ID3D11Buffer*       m_pMatrices;

	public:
		DX11_VertexShader() : m_pVertexLayout(nullptr), m_pVertexShader(nullptr), m_pMatrices(nullptr){}
		~DX11_VertexShader(){
			SAFE_RELEASE(m_pVertexLayout);
			SAFE_RELEASE(m_pVertexShader);
			SAFE_RELEASE(m_pMatrices);
		}

		/**
		* @brief valueの絶対値を計算し、結果を返す
		* @param[in] scene ワールド設定の基準となるScene
		* @param[in] node シェーダーを適用したいNode
		* @return セットアップに失敗した場合、falseを返す。
		*/
		bool SetUpRenderer(const Scene3DGraph scene, const Scene3DNode& node);
	};

	/** ===================================================================================
	* @class DX11_PixelShader
	* @brief DirectX11専用ピクセルシェーダークラス
	* LayoutやShader,コンスタントバッファーや入力用バッファーを扱う。
	==================================================================================== */
	class DX11_PixelShader{
	protected:
		//!< @brief Texture名(要追記)
		char*              m_TextureResource;
		//!< @brief ピクセルシェーダーデータ
		ID3D11PixelShader* m_pPixelShader;

	public:
		DX11_PixelShader() : m_pPixelShader(nullptr){}
		~DX11_PixelShader(){
			SAFE_RELEASE(m_pPixelShader);
		}

		/**
		* @brief valueの絶対値を計算し、結果を返す
		* @param[in] scene ワールド設定の基準となるScene
		* @param[in] node シェーダーを適用したいNode
		* @return セットアップに失敗した場合、falseを返す。
		*/
		bool SetUpRenderer(const Scene3DGraph scene, const Scene3DNode& node);
	};
}

