#ifndef H_K_CAMERA_H
#define H_K_CAMERA_H

#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Renderer\KJ_DirectX\KJ_DirectX3D.h"
#include "../KJ_System/KJ_System.h"
#include "../KJ_Mesh/MeshProperty.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"
#include "../KJ_Defines/KJ_Defines.h"


//========--------========--------========--------========--------========
//
//			Viewクラス
//
//========--------========--------========--------========--------========
namespace Klibrary{

	class Camera;
	typedef jUInt32 CameraInfoID;
	typedef std::shared_ptr<Camera> CameraSharedPtr;

	class Camera{
	protected:
		float m_fieldOfView;
		float m_aspectRatio;
		float m_nearClipping;
		float m_farClipping;
		
		Vector3 m_pos;
		Vector3 m_target;

		CameraInfoID m_cameraInfoID;  //カメラ識別ID

	public:
		inline Camera();
		inline Camera(const Vector3& pos, const Vector3& target);
		~Camera(){}

		inline virtual void Update(const jUInt32 deltaMs){}

		inline void ClearTargetView();
		inline void ClearTargetView(float a, float r, float g, float b);
		inline void ClearTargetView(const ColorF& color);
		inline void ClearTargetView(const ColorI& color);
		inline void ClearDepthStencilView();
		inline void Activate();
		inline void Activate(Matrix4& outViewMatrix, Matrix4& outProjectionMatrix);
		inline void Activate(Matrix4& outViewMatrix, Matrix4& outProjectionMatrix, const D3D11_VIEWPORT& viewport );

		inline void SetTarget(const Vector3& target){m_target = target;}
		inline void SetPosition(const Vector3& position){m_pos = position;}
		inline void SetCulRotation(const Vector3& rotation);
		inline void SetCamera(const Vector3& position, const Vector3& target){m_pos = position; m_target = target;}
		inline void SetProjectionValue(float fieldOfView, float aspectRatio, float nearClipping, float farClipping);
		inline void SetAspectRation(float aspectRation){ m_aspectRatio = aspectRation; }
		inline void SetFoV(float  fieldOfView){ m_fieldOfView = fieldOfView; }
		inline void SetCameraInfoID(CameraInfoID infoID){ m_cameraInfoID = infoID; }

		inline const Vector3& GetTarget()const{return m_target;}
		inline const Vector3& GetPosition()const{return m_pos;}
		inline CameraInfoID   GetCameraInfoID()const{ return m_cameraInfoID; }

	};

	inline Camera::Camera(){
		m_pos.x = 0;
		m_pos.y = 10.0f;
		m_pos.z = -10.0f;

		m_target.x = 0;
		m_target.y = 3.0f;
		m_target.z = 1.0f;

		m_fieldOfView = K_45_DEGREE;
		m_farClipping = 1000.0f;
		m_nearClipping = 0.01f;
		m_aspectRatio = KwindowSystem::GetScreenAspectRatio();

	}
	
	inline Camera::Camera(const Vector3& pos, const Vector3& target){
		m_pos = pos;
		m_target = target;
		m_fieldOfView = K_45_DEGREE;
		m_farClipping = 1000.0f;
		m_nearClipping = 0.01f;
		m_aspectRatio = KwindowSystem::GetScreenAspectRatio();
		
	}

	inline void Camera::ClearTargetView(){
		RenderSystem::GetRenderer()->ClearTargetView();
	}

	inline void Camera::ClearTargetView(float a, float r, float g, float b){
		RenderSystem::GetRenderer()->ClearTargetView(a, r, g, b);
	}

	inline void Camera::ClearTargetView(const ColorF& color){
		RenderSystem::GetRenderer()->ClearTargetView(color.a, color.r, color.g, color.b);
	}

	inline void Camera::ClearTargetView(const ColorI& color){
		RenderSystem::GetRenderer()->ClearTargetView((float)color.a / COLOR_MAXIMUM, (float)color.r / COLOR_MAXIMUM, (float)color.g / COLOR_MAXIMUM, (float)color.b / COLOR_MAXIMUM);
	}

	inline void Camera::ClearDepthStencilView(){
		RenderSystem::GetRenderer()->ClearDepthStencilView();
	}

	inline void Camera::Activate(){
		Matrix4 outViewMatrix, outProjectionMatrix;

		Mat4MakeViewMatrixLH(outViewMatrix, m_pos, m_target, Vector3(0, 1.0f, 0));
		Mat4MakeProjectionMatrixLH(outProjectionMatrix, m_fieldOfView, m_aspectRatio, m_nearClipping, m_farClipping);

		RenderSystem::GetRenderer()->SetViewMatrix(outViewMatrix);
		RenderSystem::GetRenderer()->SetProjectionMatrix(outProjectionMatrix);
	}

	inline void Camera::Activate(Matrix4& outViewMatrix, Matrix4& outProjectionMatrix){

		Mat4MakeViewMatrixLH(outViewMatrix, m_pos, m_target, Vector3(0, 1.0f, 0));
		Mat4MakeProjectionMatrixLH(outProjectionMatrix, m_fieldOfView, m_aspectRatio, m_nearClipping, m_farClipping);

		RenderSystem::GetRenderer()->SetViewMatrix(outViewMatrix);
		RenderSystem::GetRenderer()->SetProjectionMatrix(outProjectionMatrix);
	}

	inline void Camera::Activate(Matrix4& outViewMatrix, Matrix4& outProjectionMatrix, const D3D11_VIEWPORT& viewport){

		Mat4MakeViewMatrixLH(outViewMatrix, m_pos, m_target, Vector3(0, 1.0f, 0));
		Mat4MakeProjectionMatrixLH(outProjectionMatrix, m_fieldOfView, m_aspectRatio, m_nearClipping, m_farClipping);

		RenderSystem::GetRenderer()->SetViewMatrix(outViewMatrix);
		RenderSystem::GetRenderer()->SetProjectionMatrix(outProjectionMatrix);
		RenderSystem::GetRenderer()->SetViewport(viewport);
	}



	inline void Camera::SetProjectionValue(float fieldOfView, float aspectRatio, float nearClipping, float farClipping){
		m_fieldOfView = fieldOfView;
		m_aspectRatio = aspectRatio;
		m_nearClipping = nearClipping;
		m_farClipping = farClipping;
	}

	inline void Camera::SetCulRotation(const Vector3& rotation){
		float sx = sinf(rotation.x);
		float sy = sinf(rotation.y);
		float cx = cosf(rotation.x);
		float cy = cosf(rotation.y);

		m_target.x = m_pos.x + (cx*cy);
		m_target.y = m_pos.y - sx;
		m_target.z = m_pos.z + (cx*cy);
	}


	class AnimationCamera : public Camera{
	private:
		jUInt8  m_currentMotion;
		jUInt8  m_motionNum;
		jInt16* m_offsetKeyFrame; //モーション数分用意

		jUInt32 m_currentKeyFrame;
		jUInt32 m_totalKeyFrame;

		Quaternion  m_currentPose;
		Vector3     m_currentPos;

		jUInt32     m_rotationNum;
		jUInt16*    m_rotationFrame;
		Quaternion* m_rotationData;

		jUInt32     m_posNum;
		jUInt32*    m_posFrame;
		Vector3*    m_posData;

		bool        m_doAnimation;

		void UpdateAnimation(const jUInt32 deltaMs);

	public:
		AnimationCamera() :m_offsetKeyFrame(nullptr), m_currentMotion(-1), m_rotationFrame(nullptr), m_rotationData(nullptr),
			m_posFrame(nullptr), m_posData(nullptr), m_doAnimation(true){
		}

		~AnimationCamera(){}

		void Load(char* fileName);
		void Load(char* fileName, const Vector3& pos);

		void Update(const jUInt32 deltaMs);

	};

}//namespace

#endif