#include "../KJ_Renderer/KJ_RenderSystem.h"
#include "../KJ_System/KJ_System.h"

namespace Klibrary{
	KdirectX3D* RenderSystem::m_renderer = nullptr;

	bool RenderSystem::Initialize(){
		SAFE_DELETE(m_renderer);
		m_renderer = new KdirectX3D();
		return true;
	}

	void RenderSystem::Release(){
		SAFE_DELETE(m_renderer);
	}
}