#include "BaseGameLogic.h"
#include <string>

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			BaseGameLogic�N���X
	//
	//========--------========--------========--------========--------========
	//========--------========--------========--------========--------========
	//		   �R���X�g���N�^
	//========--------========--------========--------========--------========
	BaseGameLogic::BaseGameLogic() : m_LifeTime(0), m_pActorFactory(nullptr), m_pProcessManager(nullptr){
		m_GameState = BaseGameState_Initializing;
	}
	//========--------========--------========--------========--------========
	//		   ������
	//========--------========--------========--------========--------========
	void BaseGameLogic::VInitialize(){
		m_pActorFactory = new ActorFactory();
	}

	//========--------========--------========--------========--------========
	//		   �X�V
	//========--------========--------========--------========--------========
	void BaseGameLogic::VUpdate(float elapsedTime){
		jInt32 deltaMs = jInt32(elapsedTime * 1000.0f);
		m_LifeTime += elapsedTime;

		switch (m_GameState)
		{
		case BaseGameState_Initializing:
			break;

		case BaseGameState_Running:
			m_pProcessManager->UpdateProcesses(deltaMs);
			break;

		default:
			break;
		}

		//�Q�[���r���[�X�V
		auto gameViewEnd = m_GameViewList.end();
		for (auto it = m_GameViewList.begin(); it != gameViewEnd; ++it){
			(*it)->VUpdate(deltaMs);
		}

		//�Q�[���A�N�^�[�X�V
		auto gameActorEnd = m_Actors.end();
		for (auto it = m_Actors.begin(); it != gameActorEnd; ++it){
			it->second->Update(deltaMs);
		}
	}

	//========--------========--------========--------========--------========
	//		   �`��
	//========--------========--------========--------========--------========
	void BaseGameLogic::VRender(){
		auto end = m_GameViewList.end();
		for (auto it = m_GameViewList.begin(); it != end; ++it){
			(*it)->VRender();
		}
	}
	//========--------========--------========--------========--------========
	//		   �Q�[����ǂݍ���
	//========--------========--------========--------========--------========
	void BaseGameLogic::VLoadGame(const std::string& resourceFile){
		//���\�[�X����Q�[���f�[�^���擾����@�\��ǉ����Ă���
		//���͐��̃f�[�^��ݒ肵�Ă����B
		VCreateActor("human");
	}

	//========--------========--------========--------========--------========
	//		   �Q�[���r���[�ǉ�
	//========--------========--------========--------========--------========
	void BaseGameLogic::AddView(shared_ptr<IGameView> view, ActorID actorID){
		jInt32 viewID = static_cast<jInt32>(m_GameViewList.size());
		m_GameViewList.push_back(view);
		view->AttachActor(viewID, actorID);
		view->VInitialize();
	}

	//========--------========--------========--------========--------========
	//		   �Q�[���r���[���O
	//========--------========--------========--------========--------========
	void BaseGameLogic::RemoveView(shared_ptr<IGameView> view){
		m_GameViewList.remove(view);
	}
	//========--------========--------========--------========--------========
	//		   �A�N�^�[�쐬
	//========--------========--------========--------========--------========
	ActorSharedPtr BaseGameLogic::VCreateActor(const ActorType& type){
		ActorSharedPtr actor = m_pActorFactory->CreateActor(type);
		if (actor){
			m_Actors.insert(std::make_pair(actor->GetID(), actor));
		}
#ifdef _DEBUG
		assert(actor.get() && "Actor�쐬���s\n");
#endif

		return actor;
	}

	//========--------========--------========--------========--------========
	//		   �A�N�^�[�j��
	//========--------========--------========--------========--------========
	void BaseGameLogic::VDestroyActor(const ActorID actorID){
		auto it = m_Actors.find(actorID);
		if (it != m_Actors.end()){
			it->second->Release();
			m_Actors.erase(it);
		}
	}

	//========--------========--------========--------========--------========
	//		   �Q�[����ԕύX
	//========--------========--------========--------========--------========
	void BaseGameLogic::VChangeGameState(enum BaseGameState newState){
		m_GameState = newState;

	}




	//========--------========--------========--------========--------========
	//		   �����[�X
	//========--------========--------========--------========--------========
	void BaseGameLogic::VRelease(){
		while (!m_GameViewList.empty()){
			m_GameViewList.pop_front();
		}

		SAFE_DELETE(m_pActorFactory);
		SAFE_DELETE(m_pProcessManager);

		auto end = m_Actors.end();
		for (auto it = m_Actors.begin(); it != end; ++it){
			it->second->Release();
		}

		m_Actors.clear();
	}

	//========--------========--------========--------========--------========
	//		   �Q�b�^�[
	//========--------========--------========--------========--------========
	ActorWeakPtr BaseGameLogic::VGetActor(const ActorID actorID){
		ActorMap::iterator it = m_Actors.find(actorID);
		if (it != m_Actors.end()){
			return it->second;
		}
		//��|�C���^��Ԃ�
		return ActorWeakPtr();
	}


	
}