#include  "KJ_HardenedMesh.h"
#include  "../../TextLoader/textLoader.h"
#include <stdio.h>

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			HardenedMesh�N���X
	//
	//========--------========--------========--------========--------========

	void KJ_HardenedMesh::LoadHardenedMesh(char* filename){
		m_meshInfo->LoadMesh(filename);
	}


}//namespace