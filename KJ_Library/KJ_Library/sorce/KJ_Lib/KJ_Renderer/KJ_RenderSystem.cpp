#include "../KJ_Renderer/KJ_RenderSystem.h"
#include "../KJ_System/KJ_System.h"

namespace Klibrary{
	RendererSharedPtr RenderSystem::m_renderer = nullptr;

	//========--------========--------========--------========--------========
	//
	//			RenderSystemƒNƒ‰ƒX
	//
	//========--------========--------========--------========--------========
	bool RenderSystem::Initialize(){
		m_renderer = std::make_shared<KdirectX3D>();
		return true;
	}

	void RenderSystem::Release(){
		m_renderer->Release();
	}
}