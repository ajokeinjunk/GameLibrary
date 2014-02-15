#include "KJ_File.h"
#include <string.h>
#include "../KJ_Defines/KJ_Defines.h"

#pragma warning(disable : 4996)


namespace Klibrary{
	bool KJ_File::CopyFileExtention(char out[], const char* inFileName){
		char dir[256];
		strcpy(dir, inFileName);

		jUInt8 i = -1;
		jUInt8 j = 0;
		
		while (dir[j] != '\0'){
			if (dir[j] == '.'){
				i = j+1;
			}
			j++;
		}
		if (i == -1)return false;
		//i~j‚Ì”ÍˆÍ‚Ì•¶š—ñ‚ğ”²‚«æ‚èƒRƒs[
		char extention[10];
		for (jUInt8 k = 0; i <= j; i++){
			if (k > 9)return false;
			extention[k] = dir[i];
			k++;
		}

		strcpy(out, extention);

		return true;
	}
}