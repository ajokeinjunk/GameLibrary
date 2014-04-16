#pragma once 

#include <unordered_map>

namespace Klibrary{
	
	/**
	* @brief 派生を生成して基底にアップキャストして渡す関数
	*/
	template<class Base, class Sub>
	Base* CreateGenericObject(){ return new Sub; }

	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class GenericObjectFactory
	@brief mapに基底が共通するオブジェクトをユニークIDを参照して生成するクラス。\n
	 正規に登録手順を踏んだオブジェクトしか生成しないようにできる。\n
	 中身が削除されることは想定されていないが、\n
	 格納するものが関数ポインタであり、かつIDが32Byteのサイズなので\n
	 IDを使い切る前にリセットされることを念頭に置くものとする。
	 */
	/*========--------========--------========--------========--------========--------========--------*/
	template <class Base,  class ID>
	class GenericObjectFactory{
	private:
		//関数ポインタ
		typedef Base* (*CreateObjectFunction)();
		std::unordered_map<ID, CreateObjectFunction> m_CreateFunctions;

	public:

		template <class Sub>
		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief IDを参照して生成した関数ポインタを登録する関数
		 @param[in] id mapのキーにとなるID
	    @return 新たに登録した場合はtrueを返す。\n
	    すでに登録されていた場合はfalseを返し終了する。
		*/
		/*========--------========--------========--------========--------========--------========--------*/
		bool Register(ID id){
			auto it = m_CreateFunctions.find(id);
			if (it == m_CreateFunctions.end()){
				//関数ポインタを格納
				m_CreateFunctions[id] = &CreateGenericObject<Base, Sub>;
				return true;
			}

			return false;
		}

		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief IDを参照して新たな派生オブジェクトを関数ポイ
		 @param[in] id mapのキーにとなるID
		 @return 新たに登録した場合はtrueを返す。\n
		 すでに登録されていた場合はfalseを返し終了する。
		*/
		/*========--------========--------========--------========--------========--------========--------*/

		Base* Create(ID id){
			auto it = m_CreateFunctions.find(id);
			if (it != m_CreateFunctions.end()){
				CreateObjectFunction pFunction = it->second;
				return pFunction();
			}
			return nullptr;
		}
	};
}