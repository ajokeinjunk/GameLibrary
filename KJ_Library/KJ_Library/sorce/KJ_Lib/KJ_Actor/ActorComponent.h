#pragma once

#include "../KJ_Interface/KJ_Interface.h"
#include <memory>

namespace Klibrary{

	//仮データ
	enum ActorCompoType{
		AComp_UnDefined = 0,
		AComp_TransformComponent
	};

	class ActorComponent{
		friend class ActorFactory;

	protected:
		ActorSharedPtr m_Owner;
		//!< @brief フレンドクラスであるActorFactoryからのみ設定できる。
		void SetOwner(const ActorSharedPtr& owener){ m_Owner = owener;}


	public:
		ActorComponent(){}
		virtual ~ActorComponent(){}

		virtual bool VInitialize() = 0;
		virtual void VUpdate(const jUInt32 deltaMs){}

		//ゲッター
		//virtual const char* VGetName() const = 0;
		//virtual ActorComponentID VGetID()const = 0;

		virtual ActorCompoType VGetType() const = 0;
	};

	typedef std::shared_ptr<ActorComponent> ActorCompoSharedPtr;
	typedef std::shared_ptr<ActorComponent> ActorCompoWeakPtr;

}