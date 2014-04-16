#ifndef H_KLIB_INTERFACE_H
#define H_KLIB_INTERFACE_H

#include "../KJ_Defines/KJ_Defines.h"
#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Defines/KJ_Defines.h"
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>

namespace Klibrary{
	class Actor;
	class ActorComponent;
	class IScreenElement;
	class IGameView;
	
	//��Ő��l�͈͂�ύX����ꍇ�A
	//typedef���Ă����ƕ֗��B

	typedef jUInt32 ActorID;
	typedef jUInt32 ActorComponentID;
	typedef jUInt32 GameViewID;
	typedef jUInt8  MouseButtonType;

	const ActorID    INVALID_ACTOR_ID = 0;
	const GameViewID INVALID_GAME_VIEW_ID = 0xffffffff;

	typedef std::string ActorType;
	typedef std::string ActorComponentType;

	typedef std::shared_ptr<Actor> ActorSharedPtr;
	typedef std::weak_ptr<Actor> ActorWeakPtr;
	typedef std::unordered_map<ActorID, ActorSharedPtr> ActorMap;
	
	typedef std::shared_ptr<IGameView> GameViewSharedPtr;
	typedef std::weak_ptr<IGameView> GameViewWeakPtr;
	typedef std::list<GameViewSharedPtr> GameViewList;

	typedef std::shared_ptr<IScreenElement>   ScreenElementSharedPtr;
	typedef std::list<ScreenElementSharedPtr> ScreenElementList;

	enum MouseButton{
		MOUSE_L_BUTTON = 0,
		MOUSE_M_BUTTON,
		MOUSE_R_BUTTON,
		MOUSE_NUM_NUTTON
	};
	//========--------========--------========--------========--------========
	//
	//		   �A�v���P�[�V�����N���X
	//
	//========--------========--------========--------========--------========
	class IApplication{
	public:

	};

	/** ===================================================================================
	* @class ISceneNode
	* @brief SceneGraph�̒��Ɋe�m�[�h���g�ݍ��܂�Ă���B
	* Scene2DGraph�Ȃ�Scene2DNode�̃I�u�W�F�N�g�ō\������Ă���B
	==================================================================================== */
	class ISceneNode{
	public:
		virtual ~ISceneNode(){}

		/**
		* @brief �X�V
		* @param[in] deltaMs �t���[���Ԃ̎��ԁB�P�ʂ̓~���b�B
		*/
		virtual void VUpdate(const jUInt32 deltaMs) = 0;
		/**
		* @brief �`��
		*/
		virtual void VRender() = 0;

	};

	typedef std::vector<std::shared_ptr<ISceneNode>> SceneNodeList;

	/** ===================================================================================
	* @class IGameLogic
	* @brief �Q�[���Ƃ��Ă̒��g�����肷��B
	* ���ڊ��ł���̂͏�w�Ɉʒu����Framework���B
	* �߂�l�͌Œ�ł����Ă������ł�map�̌^���Ⴄ���Ƃ����邽�߁A
	* �S�ď����z�֐��Ƃ���B
	==================================================================================== */
	class IGameLogic{
	public:
		/**
		* @brief ������
		*/
		virtual void VInitialize() = 0;

		/**
		* @brief �X�V
		* @param[in] currentTime ���݂̎���
		* @param[in] elapsedTime �o�ߎ���
		*/
		virtual void VUpdate(float elapsedTime) = 0;
		/**
		* @brief �`��
		*/
		virtual void VRender() = 0;
		/**
		* @brief �J��
		*/
		virtual void VRelease() = 0;
		/**
		* @brief �Q�[�����ǂݍ���
		*/
		virtual void VLoadGame(const std::string& resourceFile) = 0;
		/**
		* @brief �Q�[���X�e�C�g�ύX
		* @param[in] newState ���̐V�����Q�[���X�e�C�g����͂���B
		*/
		virtual void VChangeGameState(enum BaseGameState newState) = 0;
		/**
		* @brief �A�N�^�[�쐬
		*/
		virtual ActorSharedPtr VCreateActor(const ActorType& type) = 0;
		/**
		* @brief �A�N�^�[�N���A
		*/
		virtual void VDestroyActor(const ActorID actorID) = 0;

		//�Q�b�^�[
		virtual ActorWeakPtr VGetActor(const ActorID actorID) = 0;
	};

	/**
	* @brief GameView�̃^�C�v�񋓌^
	*/
	enum GameViewType
	{
		GameView_Human,
		//GameView_AI,
		//GameView_Other,
		GameViewType_Num
	};

	/** ===================================================================================
	* @class IGameView
	* @brief AI��v���C���[��GameLogic�̏�����K�v�ȕ�������
	* �󂯎��ׂ�View�B
	==================================================================================== */
	class IGameView{
	public:
		virtual ~IGameView(){};

		/**
		* @brief ������
		*/
		virtual void VInitialize() = 0;
		/**
		* @brief �X�V
		* @param[in] deltaMs �t���[���Ԃ̎��ԁB�P�ʂ̓~���b�B
		*/
		virtual void VUpdate(const jUInt32 deltaMs) = 0;
		/**
		* @brief �`��
		*/
		virtual void VRender() = 0;

		/**
		* @brief �A�v��������MsgProc����Ăяo����邱�ƂɂȂ�R�[���o�b�N�֐��B
		*/
		virtual void CALLBACK VMsgProc() = 0;

		/**
		* @brief View��ǉ�
		*/
		virtual void AttachActor(GameViewID gamaViewID, ActorID actorID) = 0;

		//�Q�b�^�[
		virtual GameViewID   VGetID() const = 0;
		virtual GameViewType VGetType() const = 0;

	};

	/** ===================================================================================
	* @class IScreenElement
	* @brief ��ʏ�ɕ`�悳�ꂽ3D�I�u�W�F�N�g��UI�Ȃǂ̉�ʗv�f��\���N���X
	==================================================================================== */
	class IScreenElement{
	public:
		virtual ~IScreenElement(){}

		/**
		* @brief ������
		*/
		virtual void VInitialize();
		/**
		* @brief �X�V
		* @param[in] deltaMs �t���[���Ԃ̎��ԁB�P�ʂ̓~���b�B
		*/
		virtual void VUpdate(jUInt32 deltaMs) = 0;
		/**
		* @brief �`��
		*/
		virtual void VRender() = 0;
		/**
		* @brief View��ʂ��ăA�v��������MsgProc����Ăяo����邱�ƂɂȂ�R�[���o�b�N�֐��B
		View���Ō����Ȃ����͏��������Ȃ��A�ƌ��������f���ł���B
		*/
		virtual void CALLBACK VMsgProc() = 0;

		//�Z�b�^�[
		virtual void VSetZOrder(jInt32 ZOrder) = 0;
		virtual void VSetVisible(bool visible) = 0;

		//�Q�b�^�[
		virtual bool    VIsVisible()const = 0;
		virtual jInt32  VGetZOrder()const = 0;
	};

	/** ===================================================================================
	* @class IStateMachine
	* @brief �������ԑJ�ڂɑΉ�������N���X
	==================================================================================== */
	class IStateMachine{

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
	/** ===================================================================================
	* @class IMouseHandler
	* @brief �}�E�X��������������ׂ̊��B
	* �����łǂ��������Q�[���������������邩����������B
	==================================================================================== */
	class IMouseHandler{
	public:
		/**
		* @brief �}�E�X�ړ����̏���
		* @param[in] pos �}�E�X�̈ʒu
		* @param[in] radius �}�E�X�|�C���^�̑傫���̔��a
		*/
		virtual bool  VMouseMove(const Point2L &pos, jUInt8 radius) = 0;
		/**
		* @brief �}�E�X�{�^�����オ�鎞�̏���
		* @param[in] pos �}�E�X�̈ʒu
		* @param[in] radius �}�E�X�|�C���^�̑傫���̔��a
		* @param[in] mouseButton �}�E�X�{�^���̎��
		*/
		virtual bool  VMouseButtonUp(const Point2L &pos, jUInt8 radius, MouseButton mouseButton) = 0;
		/**
		* @brief �}�E�X�{�^���������鎞�̏���
		* @param[in] pos �}�E�X�̈ʒu
		* @param[in] radius �}�E�X�|�C���^�̑傫���̔��a
		* @param[in] mouseButton �}�E�X�{�^���̎��
		*/
		virtual bool  VMouseButtonDown(const Point2L &pos, jUInt8 radius, MouseButton mouseButton) = 0;
	};

	/** ===================================================================================
	* @class IKeyBoardHandler
	* @brief �L�[�{�[�h��������������ׂ̊��B
	* �����łǂ��������Q�[���������������邩����������B
	==================================================================================== */
	class IKeyBoardHandler{
	public:
		/**
		* @brief �L�[�������鎞�̏���
		* @param[in] key WindowsMessage�����uChar�ϊ��ɂ��L�[����
		*/
		virtual bool VKeyDown(jUInt8 key) = 0;
		/**
		* @brief �L�[�����オ�鎞�̏���
		* @param[in] key WindowsMessage�����uChar�ϊ��ɂ��L�[����
		*/
		virtual bool VKeyUp(jUInt8 key) = 0;
	};

	/** ===================================================================================
	* @class IGamePadHandler
	* @brief �Q�[���p�b�h��������������ׂ̊��B
	* �����łǂ��������Q�[���������������邩����������B
	==================================================================================== */
	class IGamePadHandler{
	public:
		virtual bool VTrigger(const std::string &triggerName, float const pressure) = 0;
		virtual bool VButtonDown(const std::string &buttonName, int const pressure) = 0;
		virtual bool VButtonUp(const std::string &buttonName) = 0;
		virtual bool VDirectionalPad(const std::string &direction) = 0;
		virtual bool VStickMove(const std::string &stickName, float x, float y) = 0;
	};

	//========--------========--------========--------========--------========
	//
	//		   �����_�����O�p
	//
	//========--------========--------========--------========--------========
	/**
	* @brief �I�u�W�F�N�g���ɃV�F�[�_�[�ɂ�郌���_�����O�ݒ�����邽�߂̃p�X
	*/
	enum RenderPass
	{
		RenderPass_0 = 0,
		RenderPass_Static = RenderPass_0,
		RenderPass_BackGround,
		RenderPass_NotRendered,
		RenderPass_Last,
	};

	//========--------========--------========--------========--------========
	//
	//		   ���C�g�N���X
	//
	//========--------========--------========--------========--------========
	class ILight{
	protected:

	public:
		virtual void Locate() = 0;

	};


}

#endif