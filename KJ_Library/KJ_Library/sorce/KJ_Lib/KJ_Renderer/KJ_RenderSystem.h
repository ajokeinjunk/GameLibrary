#ifndef H_KLIB_RENDER_SYSTEM_H
#define H_KLIB_RENDER_SYSTEM_H
#include "KJ_DirectX\KJ_DirectX3D.h"
#include <memory>

namespace Klibrary{

	/** ===================================================================================
	* @class RenderSystem
	* @brief 描画システムにアクセスするクラス。
	* 現在KdirectX3Dがレンダラーになっているが
	* 本来その基底のKrendererがレンダラーになる。
	==================================================================================== */

	typedef std::shared_ptr<KdirectX3D> RendererSharedPtr;

	class RenderSystem{
	private:
		//!< @brief　レンダラー。アプリに1つしか存在しない。
		static RendererSharedPtr m_renderer;

	public:
		/**
		* @brief 初期化
		* @return false = 失敗。
		*/
		static bool Initialize();
		/**
		* @brief 破棄
		*/
		static void Release();

		//ゲッター
		static const RendererSharedPtr& GetRenderer(){ return m_renderer; }
	};

#define Renderer (RenderSystem::GetRenderer())
}

#endif