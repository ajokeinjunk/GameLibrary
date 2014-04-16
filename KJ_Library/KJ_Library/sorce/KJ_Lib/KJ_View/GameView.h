#pragma once

#include "../KJ_Interface/KJ_Interface.h"
#include "../KJ_Process/ProcessManager.h"

namespace Klibrary{
	const jUInt32 SCREEN_REFRESH_RATE(1000 / 60);

	/** ===================================================================================
	* @class HumanView
	* @brief �v���C���[(�����)�ɑ΂��ĕK�v�Ȃ��̂�p�ӂ���View�N���X
	* @note HumanView���œ��̓n���h���[���Z�b�g����邱�Ƃ͂Ȃ��B
	* ���̃N���X�����Ƃ��邩�A�O������ݒ肳��邩��2�ʂ肪����B
	* �l�̑���ŃR���g���[���[���W���@�\�ɂ��Ă��������̂Ȃ�
	* IJoyPadHandler���������Ă������ƁB
	* Mouse�����ƃL�[�{�[�h���������𕹗p�������̂Ȃ�A
	* �r�b�g�t���O���������铙�A
	* ������ς��Ă������ƁB
	==================================================================================== */
	class HumanView : public IGameView{
	private:
		//!< @brief View�ɑ΂���}�E�X�n���h���[
		std::shared_ptr<IMouseHandler>    m_MouseHandler;
		//!< @brief �}�E�X�|�C���^�[�̔��a
		jInt8 m_PointerRadius;
		//!< @brief View�ɑ΂���L�[�{�[�h�n���h���[
		std::shared_ptr<IKeyBoardHandler> m_KeyBoardHandler;

	protected:
		//!< @brief ����View��ID
		GameViewID              m_ID;
		//!< @brief ����View�Ɋ֘A�t����ꂽActor��ID
		ActorID                 m_ActorID;
		//!< @brief 
		//std::
		//!< @brief �C�ӂ̃^�C�~���O�ňႤ�v�f���t���[���ɍ��킹�ď�������B
		ProcessManagerSharedPtr m_ProcessManager;
		//!< @brief ScreentElement�̉�ʗv�f�����Bptr����Ȃ��Ă����H
		ScreenElementList       m_ScreenElementList;
		//!< @brief  ���݂̎���
		jUInt32                 m_CurrentTime;
		//!< @brief  �ŏI�`�掞�̎���
		jUInt32                 m_LastDrawTime;

	public:
		HumanView();
		virtual ~HumanView();
		/**
		* @brief ������
		*/
		void VInitialize() override;
		/**
		* @brief �X�V
		* @param[in] deltaMs �t���[���Ԃ̎��ԁB�P�ʂ̓~���b�B
		*/
		void VUpdate(const jUInt32 deltaMs) override;
		/**
		* @brief �`��
		*/
		void VRender() override;
		/**
		* @brief Windows��Msgproc����Ăяo�����R�[���o�b�N�֐�
		*/
		virtual void CALLBACK VMsgProc() override;

		/**
		* @brief View��ǉ�
		*/
		virtual void AttachActor(GameViewID gamaViewID, ActorID actorID){
			m_ActorID = actorID;
			m_ID = gamaViewID;
		}

		//�Q�b�^�[
		virtual GameViewType     GetType()const{ return GameView_Human; }
		GameViewID               GetID()const{ return m_ID; }
		const ScreenElementList& GetScreenElement()const{ return m_ScreenElementList; }

		//�Z�b�^�[
	};
}