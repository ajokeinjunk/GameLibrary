#include "Light.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Light�N���X
	//			
	//========--------========--------========--------========--------========
	//========--------========--------========--------========--------========
	//			�V�F�[�_�[�ɐݒu
	//========--------========--------========--------========--------========
	void DirectionalLight::VLocate(){
		m_direction.Normalize();
		Renderer->SetDirectionalLight(m_color, m_direction);
	}
}