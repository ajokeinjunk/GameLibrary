#include "CameraManager.h"
#include <memory>

namespace Klibrary{
	CameraList      CameraManager::m_cameraList;
	CameraSharedPtr CameraManager::m_activeCamera;
	Matrix4	        CameraManager::m_viewMatrix;
	Matrix4	        CameraManager::m_projectionMatrix;

	using namespace std;

	void CameraManager::Initialize(){
		//ResetDefaultViewport();
		m_cameraList.reserve(20);

		CameraSharedPtr ptr = make_shared<Camera>();  //デフォカメラ
		m_activeCamera = ptr;
	}

	void CameraManager::Update(const jUInt32 deltaMs){
		if (m_activeCamera.get() == nullptr){ return; }
		m_activeCamera->Update(deltaMs);
	}

	void CameraManager::Activate(){
		if (m_activeCamera.get() == nullptr){ return; }

		m_activeCamera->Activate(m_viewMatrix, m_projectionMatrix);
	}

	void CameraManager::AddCamera(CameraSharedPtr camera){
		m_cameraList.push_back(camera);
	}

	void CameraManager::RemoveCamera(jUInt32 ID){
		jUInt32 size = m_cameraList.size();
		for (jUInt32 i = 0; i < size; i++){
			if (m_cameraList[i]->GetCameraInfoID() == ID){
				m_cameraList.erase(m_cameraList.begin() + i);
			}
		}
	}

	void CameraManager::RemoveAllCamera(){
		m_cameraList.clear();
	}

	void CameraManager::ClearTargetView(){
		m_activeCamera->ClearTargetView();
	}


	void CameraManager::ClearTargetView(ColorI color){
		m_activeCamera->ClearTargetView(color);
	}

	void CameraManager::ClearDepthStencilView(){
		m_activeCamera->ClearDepthStencilView();
	}


	void CameraManager::Release(){
		m_cameraList.clear();
		CameraList temp;
		m_cameraList.swap(temp);
	}
}