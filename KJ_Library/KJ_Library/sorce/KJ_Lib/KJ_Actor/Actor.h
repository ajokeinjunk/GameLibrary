#pragma once

#include "../KJ_Interface/KJ_Interface.h"
#include "../KJ_Actor/ActorComponent.h"

#include <string>
#include <memory>

namespace Klibrary{
	
	typedef std::unordered_map<ActorComponentID, ActorCompoSharedPtr> ActorComponents;

	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class Actor
	@brief ゲームに登場するモノを表すクラス\n
	ActorComponentsはアクターの機能を司る。
	*/
	/*========--------========--------========--------========--------========--------========--------*/
	class Actor{
	private:
		//!< @brief  アクター固有のID
		ActorID m_ID;
		//!< @brief  アクターの種類
		ActorType m_Type;
		//!< @brief  アクターの機能群
		ActorComponents m_ActorComponents;

	public:
		//explicitはコンストラクタの引数が１つの時、
		//余計な数値のみのコンストラクタをさせないようにする。
		//何というか忘れた。

		explicit Actor(ActorID ID);
		~Actor(){
			m_ActorComponents.clear();
		}

		bool Initialize(const ActorType& type);
		void Update(const jUInt32 deltaMs);

		void AddComponent(const ActorCompoSharedPtr& component);

		void Release(){}

		//ゲッター
		ActorID GetID()const{ return m_ID; }
		const ActorType& GetActorType()const{ return m_Type; }

	};
}