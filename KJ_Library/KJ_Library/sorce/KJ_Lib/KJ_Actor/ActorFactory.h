#pragma once 

#include "Actor.h"
#include "ActorComponent.h"
#include "../KJ_GenericPrg/KJ_Template.h"

namespace Klibrary{
	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class ActorFactory
	    @brief 唯一無二のActorオブジェクトを生成するファクトリークラス\n
		Mapを使用するためActorComponentからIDを逆参照することも可能である。
	*/
	/*========--------========--------========--------========--------========--------========--------*/
	class ActorFactory{
	private:
		//!< @brief 最後に生成されたActorのID
		ActorID m_LastCalledActor;

		ActorID GetNextActorID(){ return ++m_LastCalledActor; }


	protected:
		//!< @brief アクターの機能を表すActorComponentのマップ
		GenericObjectFactory<ActorComponent, ActorComponentID> m_ActorComponentFactory;

		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief ActorComponentを生成する関数\n
		まだ作り途中でテキストデータから読み込めるようにする。
		@param[in] type どのアクターコンポーネントを生成するか決定するstring変数
		@return 生成したActorComponentを返す\n
		*/
		/*========--------========--------========--------========--------========--------========--------*/
		ActorCompoSharedPtr CreateComponent(const ActorComponentType& type);
	public:
		ActorFactory();
		virtual ~ActorFactory(){}

		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief Actorを生成する関数\n
		まだ作り途中でテキストデータから読み込めるようにする。
		@param[in] type どのアクターを生成するか決定するstring変数
		@return 生成したActorを返す\n
		*/
		/*========--------========--------========--------========--------========--------========--------*/
		ActorSharedPtr CreateActor(const ActorType& type);



		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief Actorの中身を変更、修正する関数
		まだ作り途中でテキストデータから読み込めるようにする。
		@param[in] actor 修正するActor
		@param[in] type  どのActorに修正するかを示す変数
		@return 新たに登録した場合はtrueを返す。\n
		すでに登録されていた場合はfalseを返し終了する。
		*/
		/*========--------========--------========--------========--------========--------========--------*/
		void ModifyActor(ActorSharedPtr& actor, const ActorType& type);
	};
}