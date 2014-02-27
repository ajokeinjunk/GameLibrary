#ifndef H_K_CAMERA_H
#define H_K_CAMERA_H

#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Renderer\KJ_DirectX\KJ_DirectX3D.h"
#include "../KJ_System/KJ_System.h"
#include "../KJ_Mesh/MeshProperty.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"
#include "../KJ_Defines/KJ_Defines.h"
#include "../KJ_Windows/KJ_WindowSystem.h"
#include "../KJ_Camera/CameraElements.h"


namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Cameraクラス
	//
	//========--------========--------========--------========--------========
	class Camera;
	typedef jUInt32 CameraInfoID;
	typedef std::shared_ptr<Camera> CameraSharedPtr;

	class Camera{
	protected:
		Vector3 m_Pos;
		Vector3 m_Target;

		float m_FieldOfView;
		float m_AspectRatio;
		float m_NearClipping;
		float m_FarClipping;
		
		CameraInfoID m_CameraInfoID;  //カメラ識別ID

	public:
		inline Camera();
		inline Camera(const Vector3& pos, const Vector3& target);
		~Camera(){}

		virtual void Initialize();
		virtual void Update(const jUInt32 deltaMs){}

		inline void ClearTargetView();
		inline void ClearTargetView(float a, float r, float g, float b);
		inline void ClearTargetView(const ColorF& color);
		inline void ClearTargetView(const ColorI& color);
		inline void ClearDepthStencilView();
		inline void Activate();
		inline void Activate(Matrix4& outViewMatrix, Matrix4& outProjectionMatrix);
		inline void Activate(Matrix4& outViewMatrix, Matrix4& outProjectionMatrix, const D3D11_VIEWPORT& viewport );

		inline void SetTarget(const Vector3& target){ m_Target = target; }
		inline void SetPosition(const Vector3& position){m_Pos = position;}
		inline void SetCulRotation(const Vector3& rotation);
		inline void SetCamera(const Vector3& position, const Vector3& target){m_Pos = position; m_Target = target;}
		inline void SetProjectionValue(float fieldOfView, float nearClipping, float farClipping, float windowHeight, float windowWidth);
		inline void SetProjectionValue(float fieldOfView, float aspectRatio, float nearClipping, float farClipping);
		inline void SetAspectRation(float aspectRation){ m_AspectRatio = aspectRation; }
		inline void SetFoV(float  fieldOfView){ m_FieldOfView = fieldOfView; }
		inline void SetCameraInfoID(CameraInfoID infoID){ m_CameraInfoID = infoID; }

		inline const Vector3& GetTarget()const{return m_Target;}
		inline const Vector3& GetPosition()const{return m_Pos;}
		inline CameraInfoID   GetCameraInfoID()const{ return m_CameraInfoID; }

	};

	inline Camera::Camera(){
		m_Pos.x = 0;
		m_Pos.y = 10.0f;
		m_Pos.z = -10.0f;

		m_Target.x = 0;
		m_Target.y = 3.0f;
		m_Target.z = 1.0f;

		SetProjectionValue(K_45_DEGREE, WindowSystem::GetScreenAspectRatio(), 0.1f, 1000.0f);
	}
	
	inline Camera::Camera(const Vector3& pos, const Vector3& target){
		m_Pos = pos;
		m_Target = target;
		SetProjectionValue(K_45_DEGREE, WindowSystem::GetScreenAspectRatio(), 0.1f, 1000.0f);
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

		Mat4MakeViewMatrixLH(outViewMatrix, m_Pos, m_Target, Vector3(0, 1.0f, 0));
		Mat4MakeProjectionMatrixLH(outProjectionMatrix, m_FieldOfView, m_AspectRatio, m_NearClipping, m_FarClipping);

		RenderSystem::GetRenderer()->SetViewMatrix(outViewMatrix);
		RenderSystem::GetRenderer()->SetProjectionMatrix(outProjectionMatrix);
	}

	inline void Camera::Activate(Matrix4& outViewMatrix, Matrix4& outProjectionMatrix){

		Mat4MakeViewMatrixLH(outViewMatrix, m_Pos, m_Target, Vector3(0, 1.0f, 0));
		Mat4MakeProjectionMatrixLH(outProjectionMatrix, m_FieldOfView, m_AspectRatio, m_NearClipping, m_FarClipping);

		RenderSystem::GetRenderer()->SetViewMatrix(outViewMatrix);
		RenderSystem::GetRenderer()->SetProjectionMatrix(outProjectionMatrix);
	}

	inline void Camera::Activate(Matrix4& outViewMatrix, Matrix4& outProjectionMatrix, const D3D11_VIEWPORT& viewport){

		Mat4MakeViewMatrixLH(outViewMatrix, m_Pos, m_Target, Vector3(0, 1.0f, 0));
		Mat4MakeProjectionMatrixLH(outProjectionMatrix, m_FieldOfView, m_AspectRatio, m_NearClipping, m_FarClipping);

		RenderSystem::GetRenderer()->SetViewMatrix(outViewMatrix);
		RenderSystem::GetRenderer()->SetProjectionMatrix(outProjectionMatrix);
		RenderSystem::GetRenderer()->SetViewport(viewport);
	}



	inline void Camera::SetProjectionValue(float fieldOfView, float nearClipping, float farClipping, float windowHeight, float windowWidth){
		m_FieldOfView = fieldOfView;
		m_NearClipping = nearClipping;
		m_FarClipping = farClipping;
		m_AspectRatio = windowWidth / windowHeight;
	}

	inline void Camera::SetProjectionValue(float fieldOfView, float aspectRatio, float nearClipping, float farClipping){
		m_FieldOfView = fieldOfView;
		m_NearClipping = nearClipping;
		m_FarClipping = farClipping;
		m_AspectRatio = aspectRatio;
	}

	inline void Camera::SetCulRotation(const Vector3& rotation){
		float sx = sinf(rotation.x);
		float sy = sinf(rotation.y);
		float cx = cosf(rotation.x);
		float cy = cosf(rotation.y);

		m_Target.x = m_Pos.x + (cx*cy);
		m_Target.y = m_Pos.y - sx;
		m_Target.z = m_Pos.z + (cx*cy);
	}

	//=================================================================================
	//
	//		球回転カメラクラス(2軸)
	//
	//=================================================================================
#define ANGULAR_SPEED_Y 0.01f
#define ANGULAR_SPPED_Y_LIMIT 0.05f

#define ANGULAR_SPEED_X 0.007f
#define ANGULAR_SPEED_X_LIMIT 0.04f

	//後々状態遷移実装
	class AxisCam : public Camera{
	private:
		AxisCameraElements m_cameraData; //基底からの柔軟性があるのは結構なことだが、どこもかしこもアップキャスト祭りになる。どうするか。

	public:
		AxisCam(){}
		~AxisCam(){}

		void Initialize();

		//補正はベクトルによる線形、クォータニオンによる球形補完(slearp)
		//オイラー→クォータニオン?


		inline const AxisCameraElements& GetCameraElements()const{ return m_cameraData; }
	};

	//========--------========--------========--------========--------========
	//
	//			AnimationCameraクラス
	//
	//========--------========--------========--------========--------========
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

		jUInt32     m_PosNum;
		jUInt32*    m_PosFrame;
		Vector3*    m_PosData;

		bool        m_doAnimation;

		void UpdateAnimation(const jUInt32 deltaMs);

	public:
		AnimationCamera() :m_offsetKeyFrame(nullptr), m_currentMotion(-1), m_rotationFrame(nullptr), m_rotationData(nullptr),
			m_PosFrame(nullptr), m_PosData(nullptr), m_doAnimation(true){
		}

		~AnimationCamera(){}

		void Load(char* fileName);
		void Load(char* fileName, const Vector3& pos);

		void Update(const jUInt32 deltaMs);

	};

}//namespace

#endif