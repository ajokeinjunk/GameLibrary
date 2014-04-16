#include "TransformComponent.h"

namespace Klibrary{
	const ActorCompoType TransformComponent::g_Type = AComp_TransformComponent;

	bool TransformComponent::VInitialize(){


		return true;
	}


	bool TransformComponent::VInitialize(const Vector3& pos){
		m_Tranfrom.Identify();
		m_Tranfrom.SetPosition(pos);

		return true;
	}

	bool TransformComponent::VInitialize(const Vector3& pos, const Vector3& scale, const Vector3 rotation){
		m_Tranfrom.Identify();
		m_Tranfrom.SetPosition(pos);
		return true;
	}
}