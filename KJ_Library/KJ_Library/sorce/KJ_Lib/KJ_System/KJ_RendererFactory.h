#ifndef H_K_FACTORY_H
#define H_K_FACTORY_H
#include "../KJ_Renderer/KJ_DirectX/KJ_DirectX3D.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			REndererFactoryƒNƒ‰ƒX
	//
	//========--------========--------========--------========--------========
	enum KrendererType{
		DirectX11 = 0,
		OpenGL4_3 = 1,
	};
	
	class KrendererFactory{
	private:
	public:
		KrendererFactory(){}
		~KrendererFactory(){}

		static Krenderer* CreateRenderer(KrendererType rendererType){
				
			
			switch (rendererType){
				
			case DirectX11:
				return new KdirectX3D();

			case OpenGL4_3:
				return nullptr;

			default:
				return nullptr;
			}
		}
	};

}//namespace

#endif