#ifndef H_KLIB_OCTREE_H
#define H_KLIB_OCTREE_H

#include "../../KJ_Math/KJ_Math.h"
#include "OctreeData.h"


namespace Klibrary{
	class Octree;


	//���c���[�̃g���o�[�X
	//  �q�̃m�[�h�S�Ă��Q�Ƃ��邱�ƁB
	//  �S�ă��[�v���邩�A�q�̃m�[�h��H���čs���Ȃǂ̕��@������B

	//���[�g�͍ŏ��̊J�n�n�_�������B
	//�t�͐߂ł͂Ȃ����[�ł��邱�Ƃ������B
	//�m�[�h�͐߂ł���q�ɗt�A�������̓m�[�h�����邱�Ƃ������B
	//�m�[�h���t�����[�g���猩��Ύq�ł���B

	//�g���o�[�X���邽�߂�CallBack�֐�
	//typedef void(func)(int);
	//func a;�Ƃ��Ďg����B
	//typedef void(*func)(int); �|�C���^���ł���B

	
	//�t�g���o�[�X
	typedef void (LeafTraverseFunc)(
		void*          userData,       //���g�̃f�[�^          
		Octree*        tree,           //�g���o�[�X�����
		jUInt32        size,           //�m�[�h�̃T�C�Y
		const Vector3& minPoint,       //�ŏ��_
		jUInt32        leafData);      //�t�̎��

	//�m�[�h�g���o�[�X
	typedef bool (OctNodeFunc)(
		void*          userData,             
		Octree*        tree,              
		jUInt32        size,
		const Vector3& minPoint);


	class Octree{
	protected:
		jUInt32 m_depthLevel;      //�����؂̐[��

	

		NodeIndexData m_nextIndex; //���ɑ��݂���m�[�h�C���f�b�N�X
		NodeIndexData m_freeIndex; //���ɋ�̃m�[�h�C���f�b�N�X

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