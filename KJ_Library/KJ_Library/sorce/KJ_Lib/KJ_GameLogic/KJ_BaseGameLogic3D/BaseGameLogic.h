#pragma once

#include "../../KJ_Interface/KJ_Interface.h"
#include "../../KJ_Process/ProcessManager.h"
#include "../../KJ_Windows/KJ_WindowSystem.h"
#include "../../KJ_Actor/ActorFactory.h"

namespace Klibrary{
	/**
	* @brief BaseGameLogicのステイト列挙型
	* ロード中、メインメニュー、開始時プレイヤー待機中、ムービー、等意外と細かい
	*/
	enum BaseGameState
	{
		BaseGameState_Invalid,
		BaseGameState_Initializing,
		//BaseGameState_MainMenu,
		//BaseGameState_WaitingForPlayers,
		//BaseGameState_LoadingGameEnvironment,
		//BaseGameState_WaitingForPlayersToLoadEnvironment,
		//BaseGameState_SpawningPlayersActors,
		BaseGameState_Running
	};

	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class BaseGameLogic
	    @brief 基本的汎用的なGameLogicクラス。*/
	/*========--------========--------========--------========--------========--------========--------*/
	class BaseGameLogic : public IGameLogic{
	protected:
		//!< @brief  このゲームが実行されてから経過した時間
		float                   m_LifeTime;   
		
		//!< @brief  GameLogicのプロセスマネージャー
		ProcessManager* m_pProcessManager;
		//!< @brief  アプリケーション毎に１つのWindowSystem
		WindowSystem2           m_WindowSystem;
		//!< @brief  Actor管理用マップ
		ActorMap                m_Actors;
		//!< @brief  ゲームの状態
		BaseGameState           m_GameState;
		//!< @brief  ゲームビューのリスト
		GameViewList            m_GameViewList;
		//!< @brief  随時アクターを生成するためのファクトリークラス
		ActorFactory*           m_pActorFactory;

	public:
		BaseGameLogic();

		/**
		* @brief 初期化
		*/
		void VInitialize() override;
		/**
		* @brief 更新
		* @param[in] elapsedTime 今までの経過時間
		*/
		void VUpdate(float elapsedTime) override;
		/**
		* @brief 描画
		*/
		void VRender() override;
		/**
		* @brief ゲームを読み込み
		*/
		void VLoadGame(const std::string& resourceFile) override;
		/**
		* @brief ビュー追加
		* @param[in] view 追加するview
		*/
		void AddView(shared_ptr<IGameView> view, ActorID actorID = INVALID_ACTOR_ID);
		/**
		/**
		* @brief ビュー除外
		*/
		void RemoveView(shared_ptr<IGameView> view);
		/**
		* @brief アクター作成
		*/
		ActorSharedPtr VCreateActor(const ActorType& type) override;
		/**
		* @brief アクター廃棄
		*/
		void VDestroyActor(const ActorID actorID) override;
		/**
		* @brief プロセス追加
		*/
		void AttachProcess(ProcessSharedPtr process){if(m_pProcessManager)m_pProcessManager->AttachProcesses(process);}
		/**
		* @brief ゲームステイト変更
		* @param[in] newState 次の新しいゲームステイトを入力する。
		*/
		void VChangeGameState(enum BaseGameState newState);
		/**
		* @brief 開放
		*/
		void VRelease() override;

		//ゲッター
		const WindowSystem2& GetWindowSystem()const{ return m_WindowSystem; }
		ActorWeakPtr VGetActor(const ActorID actorID) override;
	};
}

