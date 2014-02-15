#include "Light.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Lightクラス
	//			
	//========--------========--------========--------========--------========
	//========--------========--------========--------========--------========
	//			シェーダーに設置
	//========--------========--------========--------========--------========
	void DirectionalLight::VLocate(){
		m_direction.Normalize();
		Renderer->SetDirectionalLight(m_color, m_direction);
	}
}