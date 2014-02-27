#include "CameraManager.h"
#include <memory>

namespace Klibrary{
	CameraList      CameraManager::m_CameraList;
	CameraSharedPtr CameraManager::m_ActiveCamera;
	Matrix4	        CameraManager::m_ViewMatrix;
	Matrix4	        CameraManager::m_ProjectionMatrix;
	D3D11_VIEWPORT  CameraManager::m_Viewport;

	using namespace std;

	void CameraManager::Initialize(){
		ResetDefaultViewport();
		m_CameraList.reserve(20);

		CameraSharedPtr ptr = make_shared<Camera>();  //デフォカメラ
		m_ActiveCamera = ptr;
	}

	void CameraManager::Update(const jUInt32 deltaMs){
		if (m_ActiveCamera.get() == nullptr){ return; }
		m_ActiveCamera->Update(deltaMs);
	}

	void CameraManager::Activate(){
		if (m_ActiveCamera.get() == nullptr){ return; }

		m_ActiveCamera->Activate(m_ViewMatrix, m_ProjectionMatrix);
	}

	void CameraManager::AddCamera(CameraSharedPtr camera){
		m_CameraList.push_back(camera);
	}

	void CameraManager::RemoveCamera(jUInt32 ID){
		jUInt32 size = m_CameraList.size();
		for (jUInt32 i = 0; i < size; i++){
			if (m_CameraList[i]->GetCameraInfoID() == ID){
				m_CameraList.erase(m_CameraList.begin() + i);
			}
		}
	}

	void CameraManager::RemoveAllCamera(){
		m_CameraList.clear();
	}

	void CameraManager::ClearTargetView(){
		m_ActiveCamera->ClearTargetView();
	}


	void CameraManager::ClearTargetView(ColorI color){
		m_ActiveCamera->ClearTargetView(color);
	}

	void CameraManager::ClearDepthStencilView(){
		m_ActiveCamera->ClearDepthStencilView();
	}


	void CameraManager::Release(){
		m_CameraList.clear();
		CameraList temp;
		m_CameraList.swap(temp);
	}
}