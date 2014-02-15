#ifndef H_KLIB_TEXTURE_H
#define H_KLIB_TEXTURE_H

#pragma warning(disable:4005)

#include <D3DX11.h>
#include "../KJ_System/KJ_System.h"
#include <unordered_map>
#include <string>
#include <memory>
#include "../KJ_Defines/KJ_Defines.h"

namespace Klibrary{

	class BaseTexture;

	typedef std::shared_ptr<BaseTexture> TextureSharedPtr;
	typedef std::shared_ptr<BaseTexture> TextureWeakPtr;


	//class TextureResource{
	//public:
	//	static std::unordered_map<std::string, TextureSharedPtr> m_resources;

	//	static void Release(){
	//		m_resources.clear();
	//	}
	//};

	class BaseTexture{
	protected:
		ID3D11ShaderResourceView* m_pTexture;

	public:
		BaseTexture() :m_pTexture(nullptr){}
		virtual ~BaseTexture(){ SAFE_RELEASE(m_pTexture); }

		bool LoadTexture(char* filename);
		void SendShader(jUInt32 stot);
	};


}

#endif