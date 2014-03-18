#pragma once

#include "../../KJ_Interface/KJ_Interface.h"
#include "../../KJ_Process/ProcessManager.h"

namespace Klibrary{
	/**
	* @brief BaseGameLogicのステイト列挙型
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

	/** ===================================================================================
	* @class BaseGameLogic
	* @brief 基本的汎用的なGameLogicクラス。
	==================================================================================== */
	class BaseGameLogic : public IGameLogic{
	protected:
		//!< @brief  このゲームが実行されてから経過した時間
		float                   m_LifeTime;   //
		//!< @brief  GameLogicのプロセスマネージャー
		ProcessManagerSharedPtr m_pProcessManager;

	public:
		/**
		* @brief 初期化
		* @param[in] filename ゲームロジックを設定する為のファイルパス
		*/
		void Initialize(const char* filename) override;
		/**
		* @brief 更新
		* @param[in] currentTime 現在の時間
		* @param[in] elapsedTime 今までの経過時間
		*/
		void Update(float currentTime, float elapsedTime) override;
		/**
		* @brief 開放
		*/
		void Release() override;
	};
}

