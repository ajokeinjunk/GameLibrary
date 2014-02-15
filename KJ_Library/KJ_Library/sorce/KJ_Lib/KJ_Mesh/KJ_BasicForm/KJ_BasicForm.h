#ifndef H_KLIB_BASIC_FORM_H
#define H_KLIB_BASIC_FORM_H

#include "../KJ_Mesh.h"
#include "../../KJ_Math/KJ_Math.h"

namespace Klibrary{
	//----------------------------------------------------------------------------------------------------------------------------
	//			” 
	//----------------------------------------------------------------------------------------------------------------------------
	class KJ_BaseFormMesh : public KJ_Mesh{
	private:
	public:
		KJ_BaseFormMesh(){};
		~KJ_BaseFormMesh(){};

		bool MakeBox(float width, float height, float devide);
		bool MakePlane(float w, float h, int numPartition);

	};

}

#endif
