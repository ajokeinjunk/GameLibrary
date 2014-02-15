#include  "KJ_HardenedMesh.h"
#include  "../../TextLoader/textLoader.h"
#include <stdio.h>

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			HardenedMeshƒNƒ‰ƒX
	//
	//========--------========--------========--------========--------========

	void KJ_HardenedMesh::LoadHardenedMesh(char* filename){
		m_meshInfo->LoadMesh(filename);
	}


}//namespace