#include "ActorFactory.h"
#include "KJ_ActorComponents\TransformComponent.h"

namespace Klibrary{
	ActorFactory::ActorFactory(){
		m_LastCalledActor = INVALID_ACTOR_ID;
		m_ActorComponentFactory.Register<TransformComponent>(TransformComponent::g_Type);
	}

	ActorSharedPtr ActorFactory::CreateActor(const ActorType& type){
		//�e�L�X�g�ǂݍ��݂��������A
		//����܂ł͓K����
		ActorSharedPtr actor;

		if (m_LastCalledActor == INVALID_ACTOR_ID){
			m_LastCalledActor = GetNextActorID();
		}

		//actor = std::make_shared<Actor>(m_LastCalledActor)
		actor = std::make_shared<Actor>(m_LastCalledActor);
		bool success = actor->Initialize(type);
		if (success == false){
			assert(0 && "actor���������s\n");
		}

		return actor;
	}

	ActorCompoSharedPtr ActorFactory::CreateComponent(const ActorComponentType& type){
		ActorCompoSharedPtr actorComponent;
		//string����n�b�V�������܂��Ĉ�ӂ�ID���쐬���A
		//������Q�Ƃ��ăR���|�[�l���g�����B

		ActorCompoSharedPtr actorCompo;

		//���͒��ō쐬����B
		if (type == "TranslateComponent"){
			actorCompo = std::make_shared<TransformComponent>();
		}

		return actorComponent;
	}

}