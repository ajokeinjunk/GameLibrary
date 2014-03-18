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
		//explicit�̓R���X�g���N�^�̈������P�̎��A
		//�]�v�Ȑ��l�݂̂̃R���X�g���N�^�������Ȃ��悤�ɂ���B
		//���Ƃ������Y�ꂽ�B

		explicit Actor(ActorID ID);
		~Actor();
	};
}