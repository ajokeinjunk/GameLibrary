#pragma once

#include "../KJ_Interface/KJ_Interface.h"
#include <memory>

namespace Klibrary{

	//���f�[�^
	enum ActorCompoType{
		AComp_UnDefined = 0,
		AComp_TransformComponent
	};

	class ActorComponent{
		friend class ActorFactory;

	protected:
		ActorSharedPtr m_Owner;
		//!< @brief �t�����h�N���X�ł���ActorFactory����̂ݐݒ�ł���B
		void SetOwner(const ActorSharedPtr& owener){ m_Owner = owener;}


	public:
		ActorComponent(){}
		virtual ~ActorComponent(){}

		virtual bool VInitialize() = 0;
		virtual void VUpdate(const jUInt32 deltaMs){}

		//�Q�b�^�[
		//virtual const char* VGetName() const = 0;
		//virtual ActorComponentID VGetID()const = 0;

		virtual ActorCompoType VGetType() const = 0;
	};

	typedef std::shared_ptr<ActorComponent> ActorCompoSharedPtr;
	typedef std::shared_ptr<ActorComponent> ActorCompoWeakPtr;

}