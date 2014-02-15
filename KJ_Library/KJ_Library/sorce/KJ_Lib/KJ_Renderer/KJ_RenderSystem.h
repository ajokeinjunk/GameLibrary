#ifndef H_KLIB_RENDER_SYSTEM_H
#define H_KLIB_RENDER_SYSTEM_H
#include "KJ_DirectX\KJ_DirectX3D.h"

namespace Klibrary{
	class RenderSystem{
	private:
		//å„Ç≈KrendererÇ…ïœçX
		static KdirectX3D* m_renderer;

	public:
		static bool Initialize();
		static void Release();

		static KdirectX3D* const GetRenderer(){return m_renderer;}
	};

#define Renderer (RenderSystem::GetRenderer())
}

#endif