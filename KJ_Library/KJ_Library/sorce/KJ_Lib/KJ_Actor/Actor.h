#pragma once

#include "../KJ_Interface/KJ_Interface.h"
#include "../KJ_Actor/ActorComponent.h"

#include <string>
#include <memory>

namespace Klibrary{
	
	typedef std::unordered_map<ActorComponentID, ActorCompoSharedPtr> ActorComponents;

	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class Actor
	@brief �Q�[���ɓo�ꂷ�郂�m��\���N���X\n
	ActorComponents�̓A�N�^�[�̋@�\���i��B
	*/
	/*========--------========--------========--------========--------========--------========--------*/
	class Actor{
	private:
		//!< @brief  �A�N�^�[�ŗL��ID
		ActorID m_ID;
		//!< @brief  �A�N�^�[�̎��
		ActorType m_Type;
		//!< @brief  �A�N�^�[�̋@�\�Q
		ActorComponents m_ActorComponents;

	public:
		//explicit�̓R���X�g���N�^�̈������P�̎��A
		//�]�v�Ȑ��l�݂̂̃R���X�g���N�^�������Ȃ��悤�ɂ���B
		//���Ƃ������Y�ꂽ�B

		explicit Actor(ActorID ID);
		~Actor(){
			m_ActorComponents.clear();
		}

		bool Initialize(const ActorType& type);
		void Update(const jUInt32 deltaMs);

		void AddComponent(const ActorCompoSharedPtr& component);

		void Release(){}

		//�Q�b�^�[
		ActorID GetID()const{ return m_ID; }
		const ActorType& GetActorType()const{ return m_Type; }

	};
}