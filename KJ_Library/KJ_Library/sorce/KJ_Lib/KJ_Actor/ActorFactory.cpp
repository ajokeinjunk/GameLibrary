#include "ActorFactory.h"
#include "KJ_ActorComponents\TransformComponent.h"

namespace Klibrary{
	ActorFactory::ActorFactory(){
		m_LastCalledActor = INVALID_ACTOR_ID;
		m_ActorComponentFactory.Register<TransformComponent>(TransformComponent::g_Type);
	}

	ActorSharedPtr ActorFactory::CreateActor(const ActorType& type){
		//テキスト読み込みしたいが、
		//それまでは適当に
		ActorSharedPtr actor;

		if (m_LastCalledActor == INVALID_ACTOR_ID){
			m_LastCalledActor = GetNextActorID();
		}

		//actor = std::make_shared<Actor>(m_LastCalledActor)
		actor = std::make_shared<Actor>(m_LastCalledActor);
		bool success = actor->Initialize(type);
		if (success == false){
			assert(0 && "actor初期化失敗\n");
		}

		return actor;
	}

	ActorCompoSharedPtr ActorFactory::CreateComponent(const ActorComponentType& type){
		ActorCompoSharedPtr actorComponent;
		//stringからハッシュをかまして一意のIDを作成し、
		//それを参照してコンポーネントを作る。

		ActorCompoSharedPtr actorCompo;

		//今は直で作成する。
		if (type == "TranslateComponent"){
			actorCompo = std::make_shared<TransformComponent>();
		}

		return actorComponent;
	}

}