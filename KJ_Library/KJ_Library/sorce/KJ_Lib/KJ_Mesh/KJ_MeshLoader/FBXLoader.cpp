#include "FBXLoader.h"
#include "../../KJ_Camera/KJ_Camera.h"
#include  <assert.h>

namespace Klibrary{

	//外身はFBX読込じゃなくても、独自ファイルをリアルタイムで読み込むときに
	//使えるように意識する。

	using namespace std;

	//========--------========--------========--------========--------========
	//
	//			FBXLoaderクラス
	//
	//========--------========--------========--------========--------========
	void FBXLoader::InitializeLoader(){
		m_pManager = FbxManager::Create();

		//ファイルから読み込んだ構成ノードをすべて含んだシーンデータを保存するクラス
		m_pFbxScene = FbxScene::Create(m_pManager, "scene");
	}

	//そのシーンを構成するオブジェクトを全て取得する。
	//MESH || LIGHT || CAMERA || SKELETON
	bool FBXLoader::LoadScene(const char* fileName){
		std::string pass = "C:\\Users\\worker\\Desktop\\Library\\KJ_Library7(DX)\\KJ_Library\\DATA\\";
		std::string file = fileName;
		pass += fileName;

		int length = pass.length();
		char* fullPass = new char[length + 1];
		memcpy(fullPass, pass.c_str(), length + 1);

		//ファイルから読み込み作成
		FbxImporter* pImporter = FbxImporter::Create(m_pManager, "importer");

		bool importerSuccess = pImporter->Initialize(fullPass);

		if (!importerSuccess){
			FbxString errorStr = pImporter->GetStatus().GetErrorString();
			std::string str = errorStr;
			int length = str.length();
			char* temp = new char[length + 1];
			memcpy(temp, str.c_str(), length + 1);

#ifdef _DEBUG
			MessageBox(NULL, TEXT(temp), TEXT(fileName), MB_OK | MB_ICONWARNING);
#endif
			delete[] temp;

			if (pImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion){
				int SDKMajor, SDKMinor, SDKRevision;
				int FileMajor, FileMinor, FileRevision;

				FbxManager::GetFileFormatVersion(SDKMajor, SDKMinor, SDKRevision);
				pImporter->GetFileVersion(FileMajor, FileMinor, FileRevision);

				str = "File Format Version For This SDK Do Not Correspond with This File.\n";
				FBXSDK_printf("FBX File Format Version For This FBX SDK Is %d.%d.%d\n", SDKMajor, SDKMinor, SDKRevision);
				FBXSDK_printf("FBX File Format Version For File(%s) Is %d.%d.%d\n\n", fileName, FileMajor, FileMinor, FileRevision);
			}
			return false;
		}

		importerSuccess = pImporter->Import(m_pFbxScene);
		if (importerSuccess == false || m_pFbxScene == nullptr){
			FBXSDK_printf("Filed  FbxImporter::Import()");
			return false;
		}

		m_pFbxRootNode = m_pFbxScene->GetRootNode();
		SearchChildNode(m_pFbxRootNode, m_nodeList);

		pImporter->Destroy();

		return true;
	}


	bool FBXLoader::LoadMesh(char* fileName, KJ_HardenedMesh& outMesh){

		return true;
	}

	bool FBXLoader::LoadCameraAnimation(AnimationCamera& outCamMotionData){
		FbxNode* pFbxNode = SearchCameraNode(m_nodeList);
		if (pFbxNode == nullptr)return false;

		FBXAnimationData animation;
		animation.CreateCameraAnimationData(FPS_60, m_pFbxScene, pFbxNode);





		return true;
	}


	//カメラの位置とか基本的なデータを取得
	bool FBXLoader::LoadCamera(CameraSharedPtr& camera){
		FbxNode* pNode = SearchCameraNode(m_nodeList);

		std::unordered_map<int, int> keyFrameMap;
		FbxAnimStack* pAnimStack;
		FbxAnimLayer* pAnimLayer;
		FbxAnimCurve* pAnimCurve;
		int numAnimationLayer = 0;
		int numKeys = 0;

		int numAnimation = m_pFbxScene->GetSrcObjectCount<FbxAnimStack>();
		int j, k;
		int time;
		j = k = time = 0;

		std::unordered_map<int, int> keyFreamMap;

		for (int i = 0; i < numAnimation; i++){
			pAnimStack = m_pFbxScene->GetSrcObject<FbxAnimStack>(i);


			numAnimationLayer = pAnimStack->GetMemberCount<FbxAnimLayer>();

			for (j = 0; j < numAnimationLayer; j++){
				pAnimLayer = pAnimStack->GetMember<FbxAnimLayer>(j);
				pAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
				pAnimCurve = pAnimCurve;
			}

		}



		FbxCamera* pFbxCamera = SearchCamera(m_nodeList);
		if (pFbxCamera == nullptr){
#ifdef _DEBUG
			MessageBox(NULL, TEXT("カメラ読み込み失敗"), TEXT("camera"), MB_OK | MB_ICONWARNING);
#endif
			return false;
		}

		camera->SetProjectionValue((float)(pFbxCamera->FieldOfView.Get()), (float)pFbxCamera->GetSqueezeRatio(),
			(float)pFbxCamera->NearPlane.Get(), (float)pFbxCamera->FarPlane.Get());

		Vector3 pos;

		FbxVector4 val = pFbxCamera->EvaluatePosition();
		pos.x = (float)val[0];
		pos.y = (float)val[1];
		pos.z = (float)val[2];
		camera->SetPosition(pos);

		val = pFbxCamera->EvaluateLookAtPosition();
		pos.x = (float)val[0];
		pos.y = (float)val[1];
		pos.z = (float)val[2];
		camera->SetTarget(pos);


		return true;
	}


	//========--------========--------========--------========--------========
	//			全メッシュ3角形化
	//========--------========--------========--------========--------========
	void FBXLoader::AllNodeConvertToTriangle(FbxScene& fbxScene){
		FbxGeometryConverter converter(fbxScene.GetFbxManager());
		converter.Triangulate(&fbxScene, true);
	}

	//渡したparentNodeから末端までのすべてのNodeを取得する。
	void FBXLoader::SearchChildNode(FbxNode* parentNode, FBXNodeList& chileNodeList){
		int rootChildNum = parentNode->GetChildCount();
		FbxNode* tempNode = nullptr;
		FbxNodeAttribute* att = nullptr;


		for (int i = 0; i < rootChildNum; i++){
			tempNode = parentNode->GetChild(i);

			//ここでAttributeがnullのやつでも弾いてはいけない。
			//その子がカメラやメッシュだったりするからだ。

			if (tempNode->GetChildCount() == 0){
				chileNodeList.push_back(tempNode);
			}
			else{
				chileNodeList.push_back(tempNode);
				SearchChildNode(tempNode, chileNodeList);
			}
		}
	}

	FbxCamera* FBXLoader::SearchCamera(FBXNodeList& nodeList){
		int size = nodeList.size();
		FbxNodeAttribute* att = nullptr;
		FbxCamera* camera = nullptr;

		for (int i = 0; i < size; i++){
			att = nodeList[i]->GetNodeAttribute();
			if (att == nullptr){ continue; }

			if (att->GetAttributeType() == FbxNodeAttribute::EType::eCamera){
				camera = nodeList[i]->GetCamera();
				break;
			}
		}

		return camera;
	}

	FbxNode* FBXLoader::SearchCameraNode(FBXNodeList&  nodeList){
		int size = nodeList.size();
		FbxNodeAttribute* att = nullptr;
		FbxNode* pNode = nullptr;



		for (int i = 0; i < size; i++){
			att = nodeList[i]->GetNodeAttribute();
			if (att == nullptr){ continue; }

			if (att->GetAttributeType() == FbxNodeAttribute::EType::eCamera){
				pNode = nodeList[i];
				//break;
			}
		}

		return pNode;
	}

	//========--------========--------========--------========--------========
	//
	//			FBXAnimationDataクラス
	//
	//========--------========--------========--------========--------========
	bool FBXAnimationData::CreateAnimationData(FPS_MODE fpsMode, FbxScene* pScene, const FBXNodeList& nodeList){
		bool success = false;
		success = TakeAnimationStartEnd(fpsMode, pScene);

		return true;
	}

	bool FBXAnimationData::CreateCameraAnimationData(FPS_MODE fpsMode, FbxScene* pScene, FbxNode* pNode){
		bool success = false;
		success = TakeAnimationStartEnd(fpsMode, pScene);
		FBXCameraMotionData data;
		success = TakeCameraKeyFrameData(data, pNode, pScene);

#ifdef _DEBUG
		assert(success && "カメラアニメーション作成失敗");
#endif

		return true;
	}


	//========--------========--------========--------========--------========
	//			取ってこれるのはあくまでシーンの1アニメーションの最初の最初と最後
	//			取り敢えず60FPSのみで取得。
	//========--------========--------========--------========--------========
	bool FBXAnimationData::TakeAnimationStartEnd(FPS_MODE fpsMode, FbxScene* pScene){
		//モーション名取得
		pScene->FillAnimStackNameArray(m_motionNameArray);

		FbxGlobalSettings& globalTimeSettings = pScene->GetGlobalSettings();
		FbxTime::EMode timeMode = globalTimeSettings.GetTimeMode();

		int numTakes = m_motionNameArray.GetCount();

		//ここを元にデータを60FPSにしなければならない。
		//デザインに60FPSで作るようにしておくか。
		//if (FbxTime::EMode::eFrames30 == timeMode){
		//	numTakes *= 2;
		//}

		if (FbxTime::EMode::eFrames60 != timeMode){
			MessageBox(NULL, TEXT("アニメーション読み込み失敗。\nアニメーションは60FPS以外は対応していません。\n"), TEXT(pScene->GetNameOnly()), MB_OK | MB_ICONWARNING);

			assert(FbxTime::EMode::eFrames60 == timeMode);
		}

		//映画のテイク2とかテイク１とかのあれ。テイク＝ワンカット
		bool isTake = false;
		FbxTakeInfo* pTakeInfo;

		//とりあえずワンカットだけ取得
		//
		for (int i = 0; i < numTakes; i++){
			pTakeInfo = pScene->GetTakeInfo(*(m_motionNameArray[i]));
			if (pTakeInfo){
				m_motionStartTime = pTakeInfo->mLocalTimeSpan.GetStart();
				m_motionEndTime = pTakeInfo->mLocalTimeSpan.GetStop();
				isTake = true;
				break;
			}
		}

		if (isTake == false){
#ifdef _DEBUG
			assert(isTake);
#endif
			return false;
		}

		m_startFrame = (int)(m_motionStartTime.Get() / m_deltaTime.Get());
		m_endFrame = (int)(m_motionEndTime.Get() / m_deltaTime.Get());

		FbxArrayDelete(m_motionNameArray);

		return true;
	}


	//========--------========--------========--------========--------========
	//			カメラのアニメーションデータ取得
	//========--------========--------========--------========--------========
	bool FBXAnimationData::TakeCameraAnimation(const FbxCamera* pCamera, FbxScene* pScene){
		int frameNum = m_endFrame - m_startFrame;

		FbxTime time;

		pCamera->EvaluatePosition();

		return true;
	}

	//各ボーンのアニメーションデータなり、
	//
	bool FBXAnimationData::TakeCameraKeyFrameData(FBXCameraMotionData& outData, FbxNode* pNode, FbxScene* pScene){
		std::unordered_map<int, int> keyFrameMap;
		std::vector<int> lastTimeList;   //最終キーフレーム格納用
		std::vector<std::string> nameList;

		FbxAnimStack* pAnimStack;
		FbxAnimLayer* pAnimLayer;
		FbxAnimCurve* pAnimCurve;
		int numAnimationLayer = 0;
		int numKeys = 0;

		int numAnimation = pScene->GetSrcObjectCount<FbxAnimStack>();
		int j, k;
		int time;
		j = k = time = 0;
		int lastTime = 0;

		//ここからアニメーション操作されたキーフレームだけを抽出。
		//移動、もしくは回転が操作されたキーフレームが保存され、
		//添え字がキーフレームの中身もキーのmapが出来上がる。


		//アニメーション数分ループ
		for (int i = 0; i < numAnimation; i++){
			pAnimStack = pScene->GetSrcObject<FbxAnimStack>(i);
			numAnimationLayer = pAnimStack->GetMemberCount<FbxAnimLayer>();
			lastTime = 0;
			nameList.push_back(pAnimStack->GetName());
			//レイヤー毎のループ
			for (j = 0; j < numAnimationLayer; j++){
				pAnimLayer = pAnimStack->GetMember<FbxAnimLayer>(j);

				//移動キーフレーム格納
				pAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
				if (pAnimCurve){
					numKeys = pAnimCurve->KeyGetCount();
					//キーフレーム分ループ
					for (k = 0; k < numKeys; k++)
					{
						time = (int)(pAnimCurve->KeyGetTime(k).Get() / m_deltaTime.Get());  //どこにキーがあるかは取れるが位置は？
						keyFrameMap[time] = time;
						if (time > lastTime){ lastTime = time; }
					}
				}

				pAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);
				if (pAnimCurve){
					numKeys = pAnimCurve->KeyGetCount();
					for (k = 0; k < numKeys; k++)
					{
						time = (int)(pAnimCurve->KeyGetTime(k).Get() / m_deltaTime.Get());
						keyFrameMap[time] = time;
						if (time > lastTime){ lastTime = time; }

					}
				}

				pAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z);
				if (pAnimCurve){
					numKeys = pAnimCurve->KeyGetCount();
					for (k = 0; k < numKeys; k++)
					{
						time = (int)(pAnimCurve->KeyGetTime(k).Get() / m_deltaTime.Get());
						keyFrameMap[time] = time;
						if (time > lastTime){ lastTime = time; }

					}
				}

				//回転キーフレーム
				pAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
				if (pAnimCurve){
					numKeys = pAnimCurve->KeyGetCount();
					for (k = 0; k <numKeys; k++)
					{
						time = (int)(pAnimCurve->KeyGetTime(k).Get() / m_deltaTime.Get());
						keyFrameMap[time] = time;
						if (time > lastTime){ lastTime = time; }

					}
				}

				pAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);
				if (pAnimCurve){
					numKeys = pAnimCurve->KeyGetCount();
					for (k = 0; k < numKeys; k++)
					{
						time = (int)(pAnimCurve->KeyGetTime(k).Get() / m_deltaTime.Get());
						keyFrameMap[time] = time;
						if (time > lastTime){ lastTime = time; }

					}
				}
				pAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z);
				if (pAnimCurve){
					numKeys = pAnimCurve->KeyGetCount();

					for (k = 0; k < numKeys; k++)
					{
						time = (int)(pAnimCurve->KeyGetTime(k).Get() / m_deltaTime.Get());
						keyFrameMap[time] = time;
						if (time > lastTime){ lastTime = time; }



					}
				}
			}
			lastTimeList.push_back(lastTime);
		}

		FbxCamera* pCamera = pNode->GetCamera();
		if (pCamera == nullptr){ return false; }

		MotionListSharedPtr oneMotionList = make_shared<MotionDataList>();
		
		KeyFrameDataSharedPtr motionData = make_shared<MotionKeyFrameData>();
		FbxTime fbxTime = 0;
		int currentAnimation = 0;

		//motionData->m_keyFrame = 0;
		FbxVector4 fbxPos;// = pCamera->EvaluatePosition(fbxTime);
		FbxVector4 fbxTarget;// = pCamera->EvaluateLookAtPosition(fbxTime);
		FbxVector4 fbxUpDirection;// = pCamera->EvaluateUpDirection(fbxPos, fbxTarget, fbxTime);

		//SetFBXVector4ToVector3(motionData->m_pos, fbxPos);
		//SetFBXVector4ToVector3(motionData->m_target, fbxTarget);
		//SetFBXVector4ToVector3(motionData->m_upDirection, fbxUpDirection);
		//
		//oneMotionList->push_back(motionData);


		auto endIte = keyFrameMap.end();
		int keyFrame = 0;
		for (auto ite = keyFrameMap.begin(); ite != endIte; ++ite){
			keyFrame = (*ite).second;
			
			if (keyFrame > lastTimeList[currentAnimation]){  //そのモーションの最終フレームが終われば次のアニメーションを保存。
				m_cameraAnimationData.m_motion[nameList[currentAnimation]] = oneMotionList;
				currentAnimation++;
				oneMotionList = make_shared<MotionDataList>();
			}


			motionData = make_shared<MotionKeyFrameData>();
			fbxTime = m_deltaTime * keyFrame;
			motionData->m_keyFrame = keyFrame;
			
			fbxPos = pCamera->EvaluatePosition(fbxTime);
			fbxTarget = pCamera->EvaluateLookAtPosition(fbxTime);
			fbxUpDirection = pCamera->EvaluateUpDirection(fbxPos, fbxTarget, fbxTime);

			SetFBXVector4ToVector3(motionData->m_pos, fbxPos);
			SetFBXVector4ToVector3(motionData->m_target, fbxTarget);
			SetFBXVector4ToVector3(motionData->m_upDirection, fbxUpDirection);

			FbxVector4 ve = pNode->EvaluateLocalTranslation(fbxTime);
			oneMotionList->push_back(motionData);
		}

		m_cameraAnimationData.m_motion[nameList[currentAnimation]] = oneMotionList;



		
		return true;
	}


	//========--------========--------========--------========--------========
	//
	//		   FBXAnimationLoaderクラス
	//        FBXAnimationData統括クラス
	//        作ったデータを格納する。
	//========--------========--------========--------========--------========
	//bool FBXAnimationLoader::LoadAnimation(FbxScene* pScene){
	//	//モーション名取得
	//	pScene->FillAnimStackNameArray(m_motionNameArray);

	//	FbxGlobalSettings& globalTimeSettings = pScene->GetGlobalSettings();
	//	FbxTime::EMode timeMode = globalTimeSettings.GetTimeMode();

	//	int numTakes = m_motionNameArray.GetCount();

	//	if (FbxTime::EMode::eFrames30 == timeMode){
	//		numTakes *= 2;
	//	}


	//	//映画のテイク2とかテイク１とかのあれ。テイク＝ワンカット
	//	bool isTake = false;
	//	FbxTakeInfo* pTakeInfo;

	//	//とりあえずワンカットだけ取得
	//	for (int i = 0; i < numTakes; i++){
	//		pTakeInfo = pScene->GetTakeInfo(*(m_motionNameArray[i]));
	//		if (pTakeInfo){
	//			m_motionStartTime = pTakeInfo->mLocalTimeSpan.GetStart();
	//			m_motionEndTime = pTakeInfo->mLocalTimeSpan.GetStop();
	//			isTake = true;
	//			break;
	//		}
	//	}
	//}
}
