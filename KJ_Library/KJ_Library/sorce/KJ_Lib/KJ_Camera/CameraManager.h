#ifndef H_KLIB_CAMERA_MANAGER_H
#define H_KLIB_CAMERA_MANAGER_H

#include "../KJ_Defines/KJ_Defines.h"
#include "../KJ_Math/KJ_Math.h"
#include "KJ_Camera.h"
#include "../KJ_Windows/KJ_WindowSystem.h"
#include <vector>

namespace Klibrary{
	typedef std::vector<CameraSharedPtr> CameraList;

	class CameraManager{
	private:
		static CameraList m_CameraList;
		static CameraSharedPtr m_ActiveCamera;

		static Matrix4	m_ViewMatrix;
		static Matrix4	m_ProjectionMatrix;

		static D3D11_VIEWPORT m_Viewport;

	public:
		static void Initialize();
		static void Update(const jUInt32 deltaMs);
		static void Activate();

		static void Release();

		static void AddCamera(CameraSharedPtr camera);
		static void RemoveCamera(CameraInfoID cameraID);
		static void RemoveAllCamera();

		inline static void ResetDefaultViewport();
		inline static void SetViewport(const Vector2& topLeft, float windowWidth, float windowHeight);
		inline static void SetActiveCamera(CameraInfoID ID);

		inline static const Matrix4& GetViewMatrix(){ return m_ViewMatrix; }
		inline static const Matrix4& GetProjectionMatrix(){ return m_ProjectionMatrix; }
		inline static const CameraSharedPtr& GetActiveCamera(){ return m_ActiveCamera; }
		inline static const CameraSharedPtr& SearchCamera(CameraInfoID ID);

		static void ClearTargetView(ColorI color);
		static void ClearTargetView();
		static void ClearDepthStencilView();


	};

	//------------------------------------------------------
	//	ìäâeïΩñ ê›íË
	//------------------------------------------------------
	inline void CameraManager::ResetDefaultViewport(){
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;
		m_Viewport.Width = WindowSystem::windowWidth;
		m_Viewport.Height = WindowSystem::windowHeight;
		m_Viewport.MaxDepth = 1.0f;
		m_Viewport.MinDepth = 0.0f;
	}

	inline void CameraManager::SetViewport(const Vector2& topLeft, float windowWidth, float winodwHeight){
		m_Viewport.TopLeftX = topLeft.x;
		m_Viewport.TopLeftY = topLeft.y;
		if (windowWidth <= 0 || winodwHeight <= 0){
			m_Viewport.Width = WindowSystem::windowWidth;
			m_Viewport.Height = WindowSystem::windowHeight;
		}
		else{
			m_Viewport.Width = windowWidth;
			m_Viewport.Height = winodwHeight;
		}

		m_Viewport.MaxDepth = 1.0f;
		m_Viewport.MinDepth = 0.0f;
	}

	inline void CameraManager::SetActiveCamera(CameraInfoID ID){
		for (jUInt32 i = 0; i < m_CameraList.size(); i++){
			if (m_CameraList[i]->GetCameraInfoID() == ID){
				m_ActiveCamera = m_CameraList[i];
				break;
			}
		}

	}

	inline  const CameraSharedPtr& CameraManager::SearchCamera(CameraInfoID ID){
		for (jUInt32 i = 0; i < m_CameraList.size(); i++){
			if (m_CameraList[i]->GetCameraInfoID() == ID){
				return m_CameraList[i];
			}
		}
	}
}

#endif