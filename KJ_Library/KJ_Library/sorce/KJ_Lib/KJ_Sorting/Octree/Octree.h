#ifndef H_KLIB_OCTREE_H
#define H_KLIB_OCTREE_H

#include "../../KJ_Math/KJ_Math.h"
#include "OctreeData.h"


namespace Klibrary{
	class Octree;


	//★ツリーのトラバース
	//  子のノード全てを参照すること。
	//  全てループするか、子のノードを辿って行くなどの方法がある。

	//ルートは最初の開始地点を示す。
	//葉は節ではなく末端であることを示す。
	//ノードは節であり子に葉、もしくはノードがあることを示す。
	//ノードも葉もルートから見れば子である。

	//トラバースするためのCallBack関数
	//typedef void(func)(int);
	//func a;として使える。
	//typedef void(*func)(int); ポインタもできる。

	
	//葉トラバース
	typedef void (LeafTraverseFunc)(
		void*          userData,       //中身のデータ          
		Octree*        tree,           //トラバースする木
		jUInt32        size,           //ノードのサイズ
		const Vector3& minPoint,       //最小点
		jUInt32        leafData);      //葉の種類

	//ノードトラバース
	typedef bool (OctNodeFunc)(
		void*          userData,             
		Octree*        tree,              
		jUInt32        size,
		const Vector3& minPoint);


	class Octree{
	protected:
		jUInt32 m_depthLevel;      //八分木の深さ

	

		NodeIndexData m_nextIndex; //次に存在するノードインデックス
		NodeIndexData m_freeIndex; //次に空のノードインデックス

		NodeIndexData CreateNode();

	public:
		Octree() : m_depthLevel(0) {}
		Octree(jUInt32 depth, jUInt32 leafType);

		~Octree(){}

		bool Initialize();
		void Update();

		void Release();
		bool Restore(jUInt32 depthLevel);
		
		jUInt32 GetDepthLevel(){ return m_depthLevel; }


#ifdef _DEBUG
		void DebugRender();
#endif

	};

}

#endif