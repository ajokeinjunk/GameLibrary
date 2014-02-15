#ifndef H_KLIB_FILE_H
#define H_KLIB_FILE_H

#include "../TextLoader/textLoader.h"

namespace Klibrary{
	class KJ_File{
	public:
		static bool CopyFileExtention(char out[],const char* inFileName);
	};
}

#endif