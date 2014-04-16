#pragma once

#include "../KJ_Interface/KJ_Interface.h"
#include "../KJ_Process/ProcessManager.h"

namespace Klibrary{
	const jUInt32 SCREEN_REFRESH_RATE(1000 / 60);

	/** ===================================================================================
	* @class HumanView
	* @brief プレイヤー(操作者)に対して必要なものを用意するViewクラス
	* @note HumanView内で入力ハンドラーがセットされることはない。
	* このクラスを基底とするか、外部から設定されるかの2通りがある。
	* 人の操作でコントローラーも標準機能にしておきたいのなら
	* IJoyPadHandlerも持たせておくこと。
	* Mouse処理とキーボード処理両方を併用したいのなら、
	* ビットフラグを持たせる等、
	* 処理を変えておくこと。
	==================================================================================== */
	class HumanView : public IGameView{
	private:
		//!< @brief Viewに対するマウスハンドラー
		std::shared_ptr<IMouseHandler>    m_MouseHandler;
		//!< @brief マウスポインターの半径
		jInt8 m_PointerRadius;
		//!< @brief Viewに対するキーボードハンドラー
		std::shared_ptr<IKeyBoardHandler> m_KeyBoardHandler;

	protected:
		//!< @brief このViewのID
		GameViewID              m_ID;
		//!< @brief このViewに関連付けられたActorのID
		ActorID                 m_ActorID;
		//!< @brief 
		//std::
		//!< @brief 任意のタイミングで違う要素をフレームに合わせて処理する。
		ProcessManagerSharedPtr m_ProcessManager;
		//!< @brief ScreentElementの画面要素を持つ。ptrじゃなくていい？
		ScreenElementList       m_ScreenElementList;
		//!< @brief  現在の時間
		jUInt32                 m_CurrentTime;
		//!< @brief  最終描画時の時間
		jUInt32                 m_LastDrawTime;

	public:
		HumanView();
		virtual ~HumanView();
		/**
		* @brief 初期化
		*/
		void VInitialize() override;
		/**
		* @brief 更新
		* @param[in] deltaMs フレーム間の時間。単位はミリ秒。
		*/
		void VUpdate(const jUInt32 deltaMs) override;
		/**
		* @brief 描画
		*/
		void VRender() override;
		/**
		* @brief WindowsのMsgprocから呼び出されるコールバック関数
		*/
		virtual void CALLBACK VMsgProc() override;

		/**
		* @brief Viewを追加
		*/
		virtual void AttachActor(GameViewID gamaViewID, ActorID actorID){
			m_ActorID = actorID;
			m_ID = gamaViewID;
		}

		//ゲッター
		virtual GameViewType     GetType()const{ return GameView_Human; }
		GameViewID               GetID()const{ return m_ID; }
		const ScreenElementList& GetScreenElement()const{ return m_ScreenElementList; }

		//セッター
	};
}