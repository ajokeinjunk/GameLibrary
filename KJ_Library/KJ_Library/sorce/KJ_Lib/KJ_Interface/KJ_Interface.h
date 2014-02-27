#ifndef H_KLIB_INTERFACE_H
#define H_KLIB_INTERFACE_H

#include "../KJ_Defines/KJ_Defines.h"
#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Defines/KJ_Defines.h"
#include <string>
#include <memory>

namespace Klibrary{
	class Actor;
	class ActorComponent;

	typedef jUInt32 ActorID;
	typedef jUInt32 ComponentID;

	typedef std::shared_ptr<Actor> ActorSharedPtr;
	typedef std::weak_ptr<Actor> ActorWeakPtr;

	//========--------========--------========--------========--------========
	//
	//		   アプリケーションクラス
	//
	//========--------========--------========--------========--------========
	class IApplication{
	public:

	};

	//========--------========--------========--------========--------========
	//
	//		   ゲーム内で使われる各物体
	//
	//========--------========--------========--------========--------========
	class IGameObject{
	private:

	public:

	};

	//========--------========--------========--------========--------========
	//
	//		   ゲームを構成する各要素
	//        IGameObjectとの明確な違いは識別できる点である。
	//        IGameObjectとして作られた物体をIGameNodeとして割り振っていく。
	//
	//========--------========--------========--------========--------========
	class IGameNode{

	};

	//========--------========--------========--------========--------========
	//
	//		   ゲームとしての中身を決定する
	//
	//========--------========--------========--------========--------========
	//戻り値は固定であっても内部でのmapの型が違うこともあるため、
	//全て純仮想関数とする。

	class IGameLogic{
	public:
		virtual void Initialize(const char* filename) = 0;
		virtual void LoadGame() = 0;
		virtual void Update(float currentTime, float elapsedTime) = 0;
		virtual void Release() = 0;

		virtual void ChangeGameState(enum BaseGameState newState) = 0;
		virtual void CreateActor() = 0;
		virtual void DestroyActor(const ActorID actorID) = 0;

		virtual ActorWeakPtr GetActor(const ActorID actorID) = 0;
	};

	//========--------========--------========--------========--------========
	//
	//			UI等の2D素材の基底となるクラス
	//
	//========--------========--------========--------========--------========
	class IScreenObject{
	public:
		virtual ~IScreenObject(){}

		virtual void VInitialize() = 0;
		virtual void VUpdate() = 0;
		virtual void VRender() = 0;

		virtual void VRestor() = 0;

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
	//ドラッグやダブルクリックは各々で実装する。
	class IMouseHandler{
	public:
		virtual bool  VMouseMove(const Point2L &pos, jUInt32 radius) = 0;
		virtual bool  VMouseButtonUp(const Point2L &pos, jUInt32 radius, const std::string && buttonName) = 0;
		virtual bool  VMouseButtonDown(const Point2L &pos, jUInt32 radius, const std::string && buttonName) = 0;
	};

	class IKeyBoardHandler{
	public:
		virtual bool VKeyDown(jUInt8 key) = 0;
		virtual bool VKeyUp(jUInt8 key) = 0;
		virtual bool VKeyKeepDown(jUInt8 key) = 0;
	};

	class IGamePadHandler{
	public:
		virtual bool VTrigger(const std::string &triggerName, float const pressure) = 0;
		virtual bool VOnButtonDown(const std::string &buttonName, int const pressure) = 0;
		virtual bool VOnButtonUp(const std::string &buttonName) = 0;
		virtual bool VOnDirectionalPad(const std::string &direction) = 0;
		virtual bool VStickMove(const std::string &stickName, float x, float y) = 0;
	};


	//========--------========--------========--------========--------========
	//
	//		   ライトクラス
	//
	//========--------========--------========--------========--------========
	class ILight{
	protected:

	public:
		virtual void VLocate() = 0;

	};


}

#endif