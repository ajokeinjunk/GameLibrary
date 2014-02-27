#include "KJ_Camera.h"


namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Cameraクラス
	//
	//========--------========--------========--------========--------========
	void Camera::Initialize(){
		m_Pos.x = 0;
		m_Pos.y = 10.0f;
		m_Pos.z = -10.0f;

		m_Target.x = 0;
		m_Target.y = 3.0f;
		m_Target.z = 10.0f;

		m_CameraInfoID = -1;

		SetProjectionValue(K_45_DEGREE, WindowSystem::GetScreenAspectRatio(),0.1f, 1000.0f);
	}


	//========--------========--------========--------========--------========
	//
	//			AnimationCameraクラス
	//
	//========--------========--------========--------========--------========
	void AnimationCamera::Load(char* fileName){
		
	}

	void AnimationCamera::Load(char* fileName, const Vector3& pos){

	}

	void AnimationCamera::Update(const jUInt32 deltaMs){
		if (m_doAnimation){
			UpdateAnimation(deltaMs);
			m_Pos = m_currentPos;
			//四元数からカメラ座標に変換。
		}
	}

	void AnimationCamera::UpdateAnimation(const jUInt32 deltaMs){
		if (m_totalKeyFrame == 0){ return; }
		else if (m_totalKeyFrame == 1){
			m_currentPose = m_rotationData[0];
			m_Pos = m_PosData[0];
		}
		else{
			float t = 0;
			jUInt32 i = 0;
			//回転補間
			for ( i = 0; i < m_rotationNum - 1; i++){
				if ((m_currentKeyFrame >= m_rotationFrame[i]) && (m_currentKeyFrame < m_rotationFrame[i + 1])){
					t = (float)(m_currentKeyFrame - m_rotationFrame[i]) / (float)(m_rotationFrame[i + 1] - m_rotationFrame[i]);
					QuaternionSlerp(m_currentPose, m_rotationData[i], m_rotationData[i+1], t);
					break;
				}
			}
			if (i == m_rotationNum - 1)m_currentPose = m_rotationData[m_rotationNum - 1];

			//位置補間
			for (i = 0; i < m_PosNum - 1; i++){
				if ((m_currentKeyFrame >= m_PosFrame[i]) && (m_currentKeyFrame < m_PosFrame[i + 1])){
					t = (float)(m_currentKeyFrame - m_PosFrame[i]) / (float)(m_PosFrame[i + 1] - m_PosFrame[i]);
					m_currentPos = m_PosData[i] + ((m_PosData[i + 1] - m_PosData[i]) * t);
					break;
				}
			}
			if (i == m_PosNum - 1)m_currentPos = m_PosData[m_PosNum - 1];

		}
	}


}//namespace