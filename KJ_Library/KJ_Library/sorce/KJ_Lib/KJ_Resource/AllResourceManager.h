#ifndef H_KLIB_ALL_RESOURCE_MANAGER_H
#define H_KLIB_ALL_RESOURCE_MANAGER_H

#include <memory>

namespace Klibrary{
	//lol毎回シーンの初期化でやるなり何なりとすべし。
	//Managerが増えすぎたらlistに格納して回す。
	class AllResManager{
	public:

		AllResManager(){}
		~AllResManager(){}

		static void Initialize();
		static void Release();
	};
}

#endif
