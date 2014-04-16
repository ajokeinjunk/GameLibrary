#ifndef H_KLIB_INTERFACE_H
#define H_KLIB_INTERFACE_H

#include "../KJ_Defines/KJ_Defines.h"
#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Defines/KJ_Defines.h"
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>

namespace Klibrary{
	class Actor;
	class ActorComponent;
	class IScreenElement;
	class IGameView;
	
	//後で数値範囲を変更する場合、
	//typedefしておくと便利。

	typedef jUInt32 ActorID;
	typedef jUInt32 ActorComponentID;
	typedef jUInt32 GameViewID;
	typedef jUInt8  MouseButtonType;

	const ActorID    INVALID_ACTOR_ID = 0;
	const GameViewID INVALID_GAME_VIEW_ID = 0xffffffff;

	typedef std::string ActorType;
	typedef std::string ActorComponentType;

	typedef std::shared_ptr<Actor> ActorSharedPtr;
	typedef std::weak_ptr<Actor> ActorWeakPtr;
	typedef std::unordered_map<ActorID, ActorSharedPtr> ActorMap;
	
	typedef std::shared_ptr<IGameView> GameViewSharedPtr;
	typedef std::weak_ptr<IGameView> GameViewWeakPtr;
	typedef std::list<GameViewSharedPtr> GameViewList;

	typedef std::shared_ptr<IScreenElement>   ScreenElementSharedPtr;
	typedef std::list<ScreenElementSharedPtr> ScreenElementList;

	enum MouseButton{
		MOUSE_L_BUTTON = 0,
		MOUSE_M_BUTTON,
		MOUSE_R_BUTTON,
		MOUSE_NUM_NUTTON
	};
	//========--------========--------========--------========--------========
	//
	//		   アプリケーションクラス
	//
	//========--------========--------========--------========--------========
	class IApplication{
	public:

	};

	/** ===================================================================================
	* @class ISceneNode
	* @brief SceneGraphの中に各ノードが組み込まれている。
	* Scene2DGraphならScene2DNodeのオブジェクトで構成されている。
	==================================================================================== */
	class ISceneNode{
	public:
		virtual ~ISceneNode(){}

		/**
		* @brief 更新
		* @param[in] deltaMs フレーム間の時間。単位はミリ秒。
		*/
		virtual void VUpdate(const jUInt32 deltaMs) = 0;
		/**
		* @brief 描画
		*/
		virtual void VRender() = 0;

	};

	typedef std::vector<std::shared_ptr<ISceneNode>> SceneNodeList;

	/** ===================================================================================
	* @class IGameLogic
	* @brief ゲームとしての中身を決定する。
	* 直接干渉できるのは上層に位置するFrameworkだ。
	* 戻り値は固定であっても内部でのmapの型が違うこともあるため、
	* 全て純仮想関数とする。
	==================================================================================== */
	class IGameLogic{
	public:
		/**
		* @brief 初期化
		*/
		virtual void VInitialize() = 0;

		/**
		* @brief 更新
		* @param[in] currentTime 現在の時間
		* @param[in] elapsedTime 経過時間
		*/
		virtual void VUpdate(float elapsedTime) = 0;
		/**
		* @brief 描画
		*/
		virtual void VRender() = 0;
		/**
		* @brief 開放
		*/
		virtual void VRelease() = 0;
		/**
		* @brief ゲーム情報読み込み
		*/
		virtual void VLoadGame(const std::string& resourceFile) = 0;
		/**
		* @brief ゲームステイト変更
		* @param[in] newState 次の新しいゲームステイトを入力する。
		*/
		virtual void VChangeGameState(enum BaseGameState newState) = 0;
		/**
		* @brief アクター作成
		*/
		virtual ActorSharedPtr VCreateActor(const ActorType& type) = 0;
		/**
		* @brief アクタークリア
		*/
		virtual void VDestroyActor(const ActorID actorID) = 0;

		//ゲッター
		virtual ActorWeakPtr VGetActor(const ActorID actorID) = 0;
	};

	/**
	* @brief GameViewのタイプ列挙型
	*/
	enum GameViewType
	{
		GameView_Human,
		//GameView_AI,
		//GameView_Other,
		GameViewType_Num
	};

	/** ===================================================================================
	* @class IGameView
	* @brief AIやプレイヤーがGameLogicの処理を必要な部分だけ
	* 受け取る為のView。
	==================================================================================== */
	class IGameView{
	public:
		virtual ~IGameView(){};

		/**
		* @brief 初期化
		*/
		virtual void VInitialize() = 0;
		/**
		* @brief 更新
		* @param[in] deltaMs フレーム間の時間。単位はミリ秒。
		*/
		virtual void VUpdate(const jUInt32 deltaMs) = 0;
		/**
		* @brief 描画
		*/
		virtual void VRender() = 0;

		/**
		* @brief アプリ直下のMsgProcから呼び出されることになるコールバック関数。
		*/
		virtual void CALLBACK VMsgProc() = 0;

		/**
		* @brief Viewを追加
		*/
		virtual void AttachActor(GameViewID gamaViewID, ActorID actorID) = 0;

		//ゲッター
		virtual GameViewID   VGetID() const = 0;
		virtual GameViewType VGetType() const = 0;

	};

	/** ===================================================================================
	* @class IScreenElement
	* @brief 画面上に描画された3DオブジェクトやUIなどの画面要素を表すクラス
	==================================================================================== */
	class IScreenElement{
	public:
		virtual ~IScreenElement(){}

		/**
		* @brief 初期化
		*/
		virtual void VInitialize();
		/**
		* @brief 更新
		* @param[in] deltaMs フレーム間の時間。単位はミリ秒。
		*/
		virtual void VUpdate(jUInt32 deltaMs) = 0;
		/**
		* @brief 描画
		*/
		virtual void VRender() = 0;
		/**
		* @brief Viewを通ってアプリ直下のMsgProcから呼び出されることになるコールバック関数。
		View側で見えない時は処理させない、と言った判断ができる。
		*/
		virtual void CALLBACK VMsgProc() = 0;

		//セッター
		virtual void VSetZOrder(jInt32 ZOrder) = 0;
		virtual void VSetVisible(bool visible) = 0;

		//ゲッター
		virtual bool    VIsVisible()const = 0;
		virtual jInt32  VGetZOrder()const = 0;
	};

	/** ===================================================================================
	* @class IStateMachine
	* @brief あらゆる状態遷移に対応する基底クラス
	==================================================================================== */
	class IStateMachine{

	};
	//========--------========--------========--------========--------========
	//
	//			拡張子があるファイルののローダーの基底
	//
	//========--------========--------========--------========--------========


	//========--------========--------========--------========--------========
	//
	//		   入力デバイスクラス
	//        //この部分はあくまでシステムから操作を受け取る機能として実装する。
	//========--------========--------========--------========--------========
	/** ===================================================================================
	* @class IMouseHandler
	* @brief マウス処理を実装する為の基底。
	* 内部でどういったゲーム内処理をさせるかを実装する。
	==================================================================================== */
	class IMouseHandler{
	public:
		/**
		* @brief マウス移動時の処理
		* @param[in] pos マウスの位置
		* @param[in] radius マウスポインタの大きさの半径
		*/
		virtual bool  VMouseMove(const Point2L &pos, jUInt8 radius) = 0;
		/**
		* @brief マウスボタンが上がる時の処理
		* @param[in] pos マウスの位置
		* @param[in] radius マウスポインタの大きさの半径
		* @param[in] mouseButton マウスボタンの種類
		*/
		virtual bool  VMouseButtonUp(const Point2L &pos, jUInt8 radius, MouseButton mouseButton) = 0;
		/**
		* @brief マウスボタンが下がる時の処理
		* @param[in] pos マウスの位置
		* @param[in] radius マウスポインタの大きさの半径
		* @param[in] mouseButton マウスボタンの種類
		*/
		virtual bool  VMouseButtonDown(const Point2L &pos, jUInt8 radius, MouseButton mouseButton) = 0;
	};

	/** ===================================================================================
	* @class IKeyBoardHandler
	* @brief キーボード処理を実装する為の基底。
	* 内部でどういったゲーム内処理をさせるかを実装する。
	==================================================================================== */
	class IKeyBoardHandler{
	public:
		/**
		* @brief キーが下がる時の処理
		* @param[in] key WindowsMessageからのuChar変換によるキー入力
		*/
		virtual bool VKeyDown(jUInt8 key) = 0;
		/**
		* @brief キーが下上がる時の処理
		* @param[in] key WindowsMessageからのuChar変換によるキー入力
		*/
		virtual bool VKeyUp(jUInt8 key) = 0;
	};

	/** ===================================================================================
	* @class IGamePadHandler
	* @brief ゲームパッド処理を実装する為の基底。
	* 内部でどういったゲーム内処理をさせるかを実装する。
	==================================================================================== */
	class IGamePadHandler{
	public:
		virtual bool VTrigger(const std::string &triggerName, float const pressure) = 0;
		virtual bool VButtonDown(const std::string &buttonName, int const pressure) = 0;
		virtual bool VButtonUp(const std::string &buttonName) = 0;
		virtual bool VDirectionalPad(const std::string &direction) = 0;
		virtual bool VStickMove(const std::string &stickName, float x, float y) = 0;
	};

	//========--------========--------========--------========--------========
	//
	//		   レンダリング用
	//
	//========--------========--------========--------========--------========
	/**
	* @brief オブジェクト毎にシェーダーによるレンダリング設定をするためのパス
	*/
	enum RenderPass
	{
		RenderPass_0 = 0,
		RenderPass_Static = RenderPass_0,
		RenderPass_BackGround,
		RenderPass_NotRendered,
		RenderPass_Last,
	};

	//========--------========--------========--------========--------========
	//
	//		   ライトクラス
	//
	//========--------========--------========--------========--------========
	class ILight{
	protected:

	public:
		virtual void Locate() = 0;

	};


}

#endif