#ifndef H_KLIB_TEXTURE_H
#define H_KLIB_TEXTURE_H

#pragma warning(disable:4005)

#include <D3DX11.h>
#include "../KJ_System/KJ_System.h"
#include "../KJ_Defines/KJ_Defines.h"
#include <unordered_map>
#include <string>
#include <memory>

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

	//インデックスの割り当て、
	//左上を0として右に向かってインクリメント
	//端まで行ったらまた下段に行く。
	//CulcUで返ってくるのはUV座標上で左上、原点(0,0)
	struct AtrasTexData{
		jUInt16 devideX, devideY;
		jUInt16 numDevide;
		float cellSizeX, cellSizeY;

		AtrasTexData() :devideX(1), devideY(1), cellSizeX(0), cellSizeY(0){}

		void Devide(jUInt16 devide){
			if (devide <= 0 || devide > 512)return;

			this->devideX = this->devideY = devide;
			numDevide = (this->devideX + 1) * (this->devideY + 1);
			cellSizeX = 1.0f / ((float)devideX + 1.0f);
			cellSizeX = 1.0f / ((float)devideX + 1.0f);
		}
		void Devide(jUInt16 devideX, jUInt16 devideY){
			if (devideX > 512 || devideY > 512)return;
			if (devideX <= 0 && devideY <= 0)return;

			this->devideX = devideX;
			this->devideY = devideY;
			numDevide = (this->devideX + 1) * (this->devideY + 1);
		}

		//jFloat CulcU(jUInt16 index){ return devideX + devideY * devideX; }
		//jFloat CulcV(jUInt16 index)
	};

}

#endif