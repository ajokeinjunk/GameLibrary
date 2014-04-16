#include "BaseGameLogic.h"
#include <string>

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			BaseGameLogicクラス
	//
	//========--------========--------========--------========--------========
	//========--------========--------========--------========--------========
	//		   コンストラクタ
	//========--------========--------========--------========--------========
	BaseGameLogic::BaseGameLogic() : m_LifeTime(0), m_pActorFactory(nullptr), m_pProcessManager(nullptr){
		m_GameState = BaseGameState_Initializing;
	}
	//========--------========--------========--------========--------========
	//		   初期化
	//========--------========--------========--------========--------========
	void BaseGameLogic::VInitialize(){
		m_pActorFactory = new ActorFactory();
	}

	//========--------========--------========--------========--------========
	//		   更新
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

		//ゲームビュー更新
		auto gameViewEnd = m_GameViewList.end();
		for (auto it = m_GameViewList.begin(); it != gameViewEnd; ++it){
			(*it)->VUpdate(deltaMs);
		}

		//ゲームアクター更新
		auto gameActorEnd = m_Actors.end();
		for (auto it = m_Actors.begin(); it != gameActorEnd; ++it){
			it->second->Update(deltaMs);
		}
	}

	//========--------========--------========--------========--------========
	//		   描画
	//========--------========--------========--------========--------========
	void BaseGameLogic::VRender(){
		auto end = m_GameViewList.end();
		for (auto it = m_GameViewList.begin(); it != end; ++it){
			(*it)->VRender();
		}
	}
	//========--------========--------========--------========--------========
	//		   ゲームを読み込み
	//========--------========--------========--------========--------========
	void BaseGameLogic::VLoadGame(const std::string& resourceFile){
		//リソースからゲームデータを取得する機能を追加しておく
		//今は生のデータを設定していく。
		VCreateActor("human");
	}

	//========--------========--------========--------========--------========
	//		   ゲームビュー追加
	//========--------========--------========--------========--------========
	void BaseGameLogic::AddView(shared_ptr<IGameView> view, ActorID actorID){
		jInt32 viewID = static_cast<jInt32>(m_GameViewList.size());
		m_GameViewList.push_back(view);
		view->AttachActor(viewID, actorID);
		view->VInitialize();
	}

	//========--------========--------========--------========--------========
	//		   ゲームビュー除外
	//========--------========--------========--------========--------========
	void BaseGameLogic::RemoveView(shared_ptr<IGameView> view){
		m_GameViewList.remove(view);
	}
	//========--------========--------========--------========--------========
	//		   アクター作成
	//========--------========--------========--------========--------========
	ActorSharedPtr BaseGameLogic::VCreateActor(const ActorType& type){
		ActorSharedPtr actor = m_pActorFactory->CreateActor(type);
		if (actor){
			m_Actors.insert(std::make_pair(actor->GetID(), actor));
		}
#ifdef _DEBUG
		assert(actor.get() && "Actor作成失敗\n");
#endif

		return actor;
	}

	//========--------========--------========--------========--------========
	//		   アクター破棄
	//========--------========--------========--------========--------========
	void BaseGameLogic::VDestroyActor(const ActorID actorID){
		auto it = m_Actors.find(actorID);
		if (it != m_Actors.end()){
			it->second->Release();
			m_Actors.erase(it);
		}
	}

	//========--------========--------========--------========--------========
	//		   ゲーム状態変更
	//========--------========--------========--------========--------========
	void BaseGameLogic::VChangeGameState(enum BaseGameState newState){
		m_GameState = newState;

	}




	//========--------========--------========--------========--------========
	//		   リリース
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
	//		   ゲッター
	//========--------========--------========--------========--------========
	ActorWeakPtr BaseGameLogic::VGetActor(const ActorID actorID){
		ActorMap::iterator it = m_Actors.find(actorID);
		if (it != m_Actors.end()){
			return it->second;
		}
		//空ポインタを返す
		return ActorWeakPtr();
	}


	
}