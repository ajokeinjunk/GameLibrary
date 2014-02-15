#ifndef H_KJ_HARDENED_MESH_H
#define H_KJ_HARDENED_MESH_H

#include "../KJ_Mesh.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			HardenedMeshƒNƒ‰ƒX
	//
	//========--------========--------========--------========--------========
	class KJ_HardenedMesh : public KJ_Mesh{
	protected:

	public:
		void LoadHardenedMesh(char* filename);
	};
}//namespace

#endif