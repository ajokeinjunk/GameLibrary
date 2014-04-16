#include "Actor.h"
#include "ActorComponent.h"
#include <assert.h>

namespace Klibrary{
	Actor::Actor(ActorID ID){
		m_ID = ID;
		m_Type = "unknwon";
	}

	bool Actor::Initialize(const ActorType& type){
		//仮データ直打ちで設定
		if (type == "human"){
			m_Type = type;
			return true;
		}

		return false;
	}

	void Actor::Update(const jUInt32 deltaMs){
		auto end = m_ActorComponents.end();
		for (auto it = m_ActorComponents.begin(); it != end; ++it){
			it->second->VUpdate(deltaMs);
		}
	}

	void Actor::AddComponent(const ActorCompoSharedPtr& component){
		//仮実装
		bool success = m_ActorComponents.insert(std::make_pair(component->VGetType(), component)).second;

		//本来の実装
		//bool success = m_ActorComponents.insert(std::make_pair(component->VGetID(), component)).second;

#ifdef _DEBUG
		assert(success);
#endif

	}

}