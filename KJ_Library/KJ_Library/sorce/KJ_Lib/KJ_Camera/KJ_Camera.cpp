#include "KJ_Camera.h"


namespace Klibrary{
	void AnimationCamera::Load(char* fileName){
		
	}

	void AnimationCamera::Load(char* fileName, const Vector3& pos){

	}

	void AnimationCamera::Update(const jUInt32 deltaMs){
		if (m_doAnimation){
			UpdateAnimation(deltaMs);
			m_pos = m_currentPos;
			//四元数からカメラ座標に変換。
		}

	}

	void AnimationCamera::UpdateAnimation(const jUInt32 deltaMs){
		if (m_totalKeyFrame == 0){ return; }
		else if (m_totalKeyFrame == 1){
			m_currentPose = m_rotationData[0];
			m_pos = m_posData[0];
			
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
			for (i = 0; i < m_posNum - 1; i++){
				if ((m_currentKeyFrame >= m_posFrame[i]) && (m_currentKeyFrame < m_posFrame[i + 1])){
					t = (float)(m_currentKeyFrame - m_posFrame[i]) / (float)(m_posFrame[i + 1] - m_posFrame[i]);
					m_currentPos = m_posData[i] + ((m_posData[i + 1] - m_posData[i]) * t);
					break;
				}
			}
			if (i == m_posNum - 1)m_currentPos = m_posData[m_posNum - 1];

		}
	}


}//namespace