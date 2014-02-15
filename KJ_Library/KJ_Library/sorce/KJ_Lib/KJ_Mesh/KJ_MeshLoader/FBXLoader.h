#ifndef H_KLIB_FBX_LOADER_H
#define H_KLIB_FBX_LOADER_H

#include "../../KJ_System/KJ_System.h"
#include <fbxsdk.h>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "../../KJ_Math/KJ_Math.h"


#pragma comment(lib, "libfbxsdk-mt.lib")
#pragma comment(lib, "libfbxsdk.lib")

#pragma warning(disable:4996)


namespace Klibrary{

	class KJ_HardenedMesh;
	class AnimationCamera;
	class Camera;

	typedef std::shared_ptr<Camera> CameraSharedPtr;
	typedef std::vector<FbxNode*> FBXNodeList;

	enum FPS_MODE{
		FPS_60,
		FPS_30,
	};

	//�����J�b�g�݂̂ɑΉ��B


	class FBXAnimationData;
	typedef std::shared_ptr<FBXAnimationData> FBXAnimSharedPtr;
	typedef std::weak_ptr<FBXAnimationData> FBXAnimWeakPtr;

	//========--------========--------========--------========--------========
	//
	//			FBXAnimationData�N���X
	//
	//========--------========--------========--------========--------========

	struct MotionKeyFrameData{
		unsigned int m_keyFrame;
		Vector3      m_pos;
		Vector3      m_target;
		Vector3      m_upDirection;
	};

	typedef std::shared_ptr<MotionKeyFrameData> KeyFrameDataSharedPtr;
	typedef std::vector<KeyFrameDataSharedPtr> MotionDataList;
	typedef std::shared_ptr<MotionDataList> MotionListSharedPtr;

	//�L�[�̓��[�V�������A�f�[�^�̓��[�V�������̑S�L�[�t���[���f�[�^�B
	struct FBXCameraMotionData{
		std::unordered_map<std::string, MotionListSharedPtr> m_motion;
	};
	
	class FBXAnimationData{
	private:
		//FbxString* m_animatioName;  //���̃A�j���[�V�����̖��O

		unsigned int m_startFrame;  //�J�n�t���[��
		unsigned int m_endFrame;    //�I���t���[��

		FbxTime m_motionStartTime;  //���[�V�����̊J�n����
		FbxTime m_motionEndTime;    //���[�V�����̏I������
		FbxTime m_deltaTime;        //1�t���[���̍�������
		
		FbxArray<FbxString*>  m_motionNameArray; //���[�V�������i�[�p�z��

		FBXCameraMotionData m_cameraAnimationData; //lol ��芸�����Ƃ��Ƃƃf�[�^����ė������̂ł����ɂ����B

		bool TakeAnimationStartEnd(FPS_MODE fpsMode, FbxScene* pScene);
		bool TakeCameraAnimation(const FbxCamera* pCamera, FbxScene* pScene);
		bool TakeCameraKeyFrameData(FBXCameraMotionData& outData, FbxNode* pNode, FbxScene* pScene);

		//�{�[�����A�j���[�V�����f�[�^�������Ŏ󂯎��悤�ɂ���B
	public:
		FBXAnimationData() : m_startFrame(0), m_endFrame(0){
			m_deltaTime.SetTime(0, 0, 0, 1, 0, FbxTime::EMode::eFrames60);
		}

		~FBXAnimationData(){}

		bool CreateAnimationData(FPS_MODE fpsMode, FbxScene* pScene, const FBXNodeList& nodeList);
		bool CreateCameraAnimationData(FPS_MODE fpsMode, FbxScene* pScene, FbxNode* pNode);
		//bool CreateAnimationData(FbxString* m_animatioName, FPS_MODE fpsMode, FbxScene* pScene);

	};


	////FBXLoader�̒��Ŏg���B
	//class FBXAnimationLoader{
	//private:
	//	int m_numMotion;
	//	FBXAnimationList m_animationList;
	//	FbxArray<FbxString*>  m_motionNameArray; //���[�V�������i�[�p�z��

	//public:
	//	FBXAnimationLoader() :m_numMotion(0){}

	//	bool LoadAnimation(FPS_MODE fpsMode, FbxScene* pScene, const FBXNodeList& nodeList);
	//};

	//========--------========--------========--------========--------========
	//
	//			FBXLoader�N���X
	//
	//========--------========--------========--------========--------========
	class FBXLoader{

		FbxManager* m_pManager;
		FbxMesh*    m_pFbxMesh;
		FbxScene*   m_pFbxScene;

		FbxNode*    m_pFbxRootNode;
		FBXNodeList m_nodeList;

		void AllNodeConvertToTriangle(FbxScene& fbxScene);

		void SearchChildNode(FbxNode* parentNode, FBXNodeList& chileNodeList);
		FbxCamera* SearchCamera(FBXNodeList&  nodeList);
		FbxNode* SearchCameraNode(FBXNodeList&  nodeList);



	public:
		FBXLoader() :m_pManager(nullptr), m_pFbxScene(nullptr), m_pFbxMesh(nullptr), m_pFbxRootNode(nullptr){

		}

		~FBXLoader(){
			Release();
		}

		//�����܂ňꎞ�I�Ȓ��ǂ݂悤�B
		void InitializeLoader();
		bool LoadScene(const char* fileName);
		bool LoadMesh(char* fileName, KJ_HardenedMesh& outMesh);
		bool LoadAnimationMesh( KJ_HardenedMesh& outMesh);
		bool LoadCameraAnimation(AnimationCamera& outCamMotionData);
		bool LoadCamera(CameraSharedPtr& camera);


		void Release(){
			m_nodeList.clear();
			FBXNodeList temp;
			m_nodeList.swap(temp);

			if (m_pManager){
				m_pManager->Destroy();
				m_pManager = nullptr;
			}
		}
	};

	inline void SetFBXVector4ToVector3(Vector3& out, const FbxVector4& in){
		out.x = (float)in[0];
		out.y = (float)in[1];
		out.z = (float)in[2];
	}
}

#endif