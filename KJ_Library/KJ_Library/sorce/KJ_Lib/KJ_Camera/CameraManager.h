#ifndef H_KLIB_CAMERA_MANAGER_H
#define H_KLIB_CAMERA_MANAGER_H

#include "../KJ_Defines/KJ_Defines.h"
#include "../KJ_Math/KJ_Math.h"
#include "KJ_Camera.h"
#include <vector>

namespace Klibrary{
	typedef std::vector<CameraSharedPtr> CameraList;

	class CameraManager{
	private:
		static CameraList m_cameraList;
		static CameraSharedPtr m_activeCamera;

		static Matrix4	m_viewMatrix;
		static Matrix4	m_projectionMatrix;

		//static D3DVIEWPORT9 m_viewport;

	public:
		static void Initialize();
		static void Update(const jUInt32 deltaMs);
		static void Activate();

		static void Release();

		static void AddCamera(CameraSharedPtr camera);
		static void RemoveCamera(CameraInfoID cameraID);
		static void RemoveAllCamera();

		//inline static void ResetDefaultViewport();
		//inline static void SetViewport(int x, int y, int width, int height);
		inline static void SetActiveCamera(CameraInfoID ID);

		inline static const Matrix4& GetViewMatrix(){ return m_viewMatrix; }
		inline static const Matrix4& GetProjectionMatrix(){ return m_projectionMatrix; }
		inline static const CameraSharedPtr& GetActiveCamera(){ return m_activeCamera; }
		inline static const CameraSharedPtr& SearchCamera(CameraInfoID ID);

		static void ClearTargetView(ColorI color);
		static void ClearTargetView();
		static void ClearDepthStencilView();


	};

	//------------------------------------------------------
	//	ìäâeïΩñ ê›íË
	//------------------------------------------------------
	//inline void CameraManager::ResetDefaultViewport(){
	//	m_viewport.X = 0;
	//	m_viewport.Y = 0;
	//	m_viewport.Width = iexSystem::ScreenWidth;
	//	m_viewport.Height = iexSystem::ScreenHeight;
	//	m_viewport.MaxZ = 1.0f;
	//	m_viewport.MinZ = 0.0f;
	//}

	//inline void CameraManager::SetViewport(int x, int y, int width, int height){
	//	m_viewport.X = x;
	//	m_viewport.Y = y;
	//	if (width <= 0 || height <= 0){
	//		m_viewport.Width = iexSystem::ScreenWidth;
	//		m_viewport.Height = iexSystem::ScreenHeight;
	//	}
	//	else{
	//		m_viewport.Width = width;
	//		m_viewport.Height = height;
	//	}

	//	m_viewport.MaxZ = 1.0f;
	//	m_viewport.MinZ = 0.0f;
	//}

	inline void CameraManager::SetActiveCamera(CameraInfoID ID){
		for (jUInt32 i = 0; i < m_cameraList.size(); i++){
			if (m_cameraList[i]->GetCameraInfoID() == ID){
				m_activeCamera = m_cameraList[i];
				break;
			}
		}

	}

	inline  const CameraSharedPtr& CameraManager::SearchCamera(CameraInfoID ID){
		for (jUInt32 i = 0; i < m_cameraList.size(); i++){
			if (m_cameraList[i]->GetCameraInfoID() == ID){
				return m_cameraList[i];
			}
		}
	}
}

#endif