#ifndef H_KLIB_INTERFACE_H
#define H_KLIB_INTERFACE_H

#include "../KJ_Defines/KJ_Defines.h"
#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Defines/KJ_Defines.h"
#include <string>

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//		   �A�v���P�[�V�����N���X
	//
	//========--------========--------========--------========--------========
	class IApplication{
	public:

	};

	//========--------========--------========--------========--------========
	//
	//		   �Q�[�����Ŏg����e����
	//
	//========--------========--------========--------========--------========
	class IGameObject{
	private:

	public:

	};

	//========--------========--------========--------========--------========
	//
	//		   �Q�[�����\������e�v�f
	//        IGameObject�Ƃ̖��m�ȈႢ�͎��ʂł���_�ł���B
	//        IGameObject�Ƃ��č��ꂽ���̂�IGameNode�Ƃ��Ċ���U���Ă����B
	//
	//========--------========--------========--------========--------========
	class IGameNode{

	};

	//========--------========--------========--------========--------========
	//
	//		   �Q�[���Ƃ��Ă̒��g�����肷��
	//
	//========--------========--------========--------========--------========
	class IGameLogic{
	public:
		virtual void Initialize(const char* filename) = 0;
		virtual void Load() = 0;
		virtual void Update() = 0;

		virtual void Release() = 0;
	};

	//========--------========--------========--------========--------========
	//
	//			UI����2D�f�ނ̊��ƂȂ�N���X
	//
	//========--------========--------========--------========--------========
	class IScreenObject{
	public:
		virtual ~IScreenObject(){}

		virtual void VInitialize() = 0;
		virtual void VUpdate() = 0;
		virtual void VRender() = 0;

		virtual void VRestor() = 0;

	};

	//========--------========--------========--------========--------========
	//
	//			�g���q������t�@�C���̂̃��[�_�[�̊��
	//
	//========--------========--------========--------========--------========

	//========--------========--------========--------========--------========
	//
	//		   ���̓f�o�C�X�N���X
	//        //���̕����͂����܂ŃV�X�e�����瑀����󂯎��@�\�Ƃ��Ď�������B
	//========--------========--------========--------========--------========
	//�h���b�O��_�u���N���b�N�͊e�X�Ŏ�������B
	class IMouseHandler{
	public:
		virtual bool  VMouseMove(const Point2L &pos, jUInt32 radius) = 0;
		virtual bool  VMouseButtonUp(const Point2L &pos, jUInt32 radius, const std::string && buttonName) = 0;
		virtual bool  VMouseButtonDown(const Point2L &pos, jUInt32 radius, const std::string && buttonName) = 0;
	};

	class IKeyBoardHandler{
	public:
		virtual bool VKeyDown(jUInt8 key) = 0;
		virtual bool VKeyUp(jUInt8 key) = 0;
		virtual bool VKeyKeepDown(jUInt8 key) = 0;
	};

	class IGamePadHandler{
	public:
		virtual bool VTrigger(const std::string &triggerName, float const pressure) = 0;
		virtual bool VOnButtonDown(const std::string &buttonName, int const pressure) = 0;
		virtual bool VOnButtonUp(const std::string &buttonName) = 0;
		virtual bool VOnDirectionalPad(const std::string &direction) = 0;
		virtual bool VStickMove(const std::string &stickName, float x, float y) = 0;
	};


	//========--------========--------========--------========--------========
	//
	//		   ���C�g�N���X
	//
	//========--------========--------========--------========--------========
	class ILight{
	protected:

	public:
		virtual void VLocate() = 0;

	};


}

#endif