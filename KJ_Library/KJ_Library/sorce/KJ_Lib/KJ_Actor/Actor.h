#pragma once

#include "../KJ_Interface/KJ_Interface.h"
#include <string>

namespace Klibrary{
	typedef std::string ActorType;

	class Actor{
	private:
		ActorID m_ID;
		ActorType m_Type;

	public:
		//explicitはコンストラクタの引数が１つの時、
		//余計な数値のみのコンストラクタをさせないようにする。
		//何というか忘れた。

		explicit Actor(ActorID ID);
		~Actor();
	};
}