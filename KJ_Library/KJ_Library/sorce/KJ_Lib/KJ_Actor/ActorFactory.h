#pragma once 

#include "Actor.h"
#include "ActorComponent.h"
#include "../KJ_GenericPrg/KJ_Template.h"

namespace Klibrary{
	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class ActorFactory
	    @brief �B�ꖳ���Actor�I�u�W�F�N�g�𐶐�����t�@�N�g���[�N���X\n
		Map���g�p���邽��ActorComponent����ID���t�Q�Ƃ��邱�Ƃ��\�ł���B
	*/
	/*========--------========--------========--------========--------========--------========--------*/
	class ActorFactory{
	private:
		//!< @brief �Ō�ɐ������ꂽActor��ID
		ActorID m_LastCalledActor;

		ActorID GetNextActorID(){ return ++m_LastCalledActor; }


	protected:
		//!< @brief �A�N�^�[�̋@�\��\��ActorComponent�̃}�b�v
		GenericObjectFactory<ActorComponent, ActorComponentID> m_ActorComponentFactory;

		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief ActorComponent�𐶐�����֐�\n
		�܂����r���Ńe�L�X�g�f�[�^����ǂݍ��߂�悤�ɂ���B
		@param[in] type �ǂ̃A�N�^�[�R���|�[�l���g�𐶐����邩���肷��string�ϐ�
		@return ��������ActorComponent��Ԃ�\n
		*/
		/*========--------========--------========--------========--------========--------========--------*/
		ActorCompoSharedPtr CreateComponent(const ActorComponentType& type);
	public:
		ActorFactory();
		virtual ~ActorFactory(){}

		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief Actor�𐶐�����֐�\n
		�܂����r���Ńe�L�X�g�f�[�^����ǂݍ��߂�悤�ɂ���B
		@param[in] type �ǂ̃A�N�^�[�𐶐����邩���肷��string�ϐ�
		@return ��������Actor��Ԃ�\n
		*/
		/*========--------========--------========--------========--------========--------========--------*/
		ActorSharedPtr CreateActor(const ActorType& type);



		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief Actor�̒��g��ύX�A�C������֐�
		�܂����r���Ńe�L�X�g�f�[�^����ǂݍ��߂�悤�ɂ���B
		@param[in] actor �C������Actor
		@param[in] type  �ǂ�Actor�ɏC�����邩�������ϐ�
		@return �V���ɓo�^�����ꍇ��true��Ԃ��B\n
		���łɓo�^����Ă����ꍇ��false��Ԃ��I������B
		*/
		/*========--------========--------========--------========--------========--------========--------*/
		void ModifyActor(ActorSharedPtr& actor, const ActorType& type);
	};
}