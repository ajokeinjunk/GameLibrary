#ifndef H_KLIB_OCTREE_DATA_H
#define H_KLIB_OCTREE_DATA_H

#include "../../KJ_Defines/KJ_Defines.h"

#define KJ_NODE_INVALID 0x7FFFFFFF  //ノード無効
#define KJ_NODE_NONE    0x00000000  //ノード無し
#define KJ_NODE_LEAF    0x80000000  //ノードタイプ葉(末端)    

namespace Klibrary{

	typedef jUInt32 NodeIndexData;  //中身は唯のUInt32だが上位ビットはフラグ情報、下位ビットはインデックスとして使う。

}

#endif