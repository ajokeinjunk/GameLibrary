#ifndef H_KLIB_ALL_RESOURCE_MANAGER_H
#define H_KLIB_ALL_RESOURCE_MANAGER_H

#include <memory>

namespace Klibrary{
	//lol����V�[���̏������ł��Ȃ艽�Ȃ�Ƃ��ׂ��B
	//Manager��������������list�Ɋi�[���ĉ񂷁B
	class AllResManager{
	public:

		AllResManager(){}
		~AllResManager(){}

		static void Initialize();
		static void Release();
	};
}

#endif
