#ifndef H_KLIB_OCTREE_DATA_H
#define H_KLIB_OCTREE_DATA_H

#include "../../KJ_Defines/KJ_Defines.h"

#define KJ_NODE_INVALID 0x7FFFFFFF  //�m�[�h����
#define KJ_NODE_NONE    0x00000000  //�m�[�h����
#define KJ_NODE_LEAF    0x80000000  //�m�[�h�^�C�v�t(���[)    

namespace Klibrary{

	typedef jUInt32 NodeIndexData;  //���g�͗B��UInt32������ʃr�b�g�̓t���O���A���ʃr�b�g�̓C���f�b�N�X�Ƃ��Ďg���B

}

#endif