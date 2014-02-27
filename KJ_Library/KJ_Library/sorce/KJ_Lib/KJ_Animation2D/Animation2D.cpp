#include "Animation2D.h"

namespace Klibrary{

	//========--------========--------========--------========--------========
	//			
	//		   Animation2Dクラス
	//  
	//========--------========--------========--------========--------========
	void Animation2D::Initialize(){
		m_CurrentKeyFrame = 0; 
		m_CurrntMotionID  = 0;
		
		m_IsAnimation = true;
		m_IsLoop = false;
			
		m_CurrentScale.x = 1.0f;   m_CurrentScale.y = 1.0f;
		m_CurrentRotation.x = 0;   m_CurrentRotation.y = 0;
		m_CurrentTraslation.x = 0; m_CurrentTraslation.y = 0;
	}

	void Animation2D::Update(jUInt32 deltaMs){
		if (m_CurrntMotionID < 0)return;
		else if (m_IsAnimation == false)return;
		else if (m_Motions.find(m_CurrntMotionID) == m_Motions.end()){
			return;
		}

		const Motion2DSharedPtr keyFrame = m_Motions.at(m_CurrntMotionID);
		jFloat deltaTime = (jFloat)deltaMs / 1000.0f;

		if (m_CurrentKeyFrame == 0){
			m_CurrentTraslation = keyFrame->m_TranslationKey.m_Translation[0];
			m_CurrentRotation   = keyFrame->m_RotationKey.m_Rotation[0];
			m_CurrentScale      = keyFrame->m_ScaleKey.m_Scale[0];
		}
		else{

			jFloat t = 0;
			jUInt32 i = 0;
			jUInt32 size = 0;

			const RotationKeyFrame*    pRot =   &keyFrame->m_RotationKey;
			const TranslationKeyFrame* pTrans =   &keyFrame->m_TranslationKey;
			const ScaleKeyFrame*       pScale = &keyFrame->m_ScaleKey;


			//回転補間
			size = pRot->m_KeyFrame.size() - 1;
			for (i = 0; i < size; i++){
				if ((m_CurrentKeyFrame >= pRot->m_KeyFrame[i]) && (m_CurrentKeyFrame < pRot->m_KeyFrame[i + 1])){
					t = (jFloat)(m_CurrentKeyFrame - pRot->m_KeyFrame[i]) / (jFloat)(pRot->m_KeyFrame[i + 1] - pRot->m_KeyFrame[i]);
					m_CurrentRotation = pRot->m_Rotation[i] + ((pRot->m_Rotation[i + 1] - pRot->m_Rotation[i]) * t);
					break;
				}
			}
			if (i == size)m_CurrentRotation = pRot->m_Rotation[size];


			//位置補間
			size = pTrans->m_KeyFrame.size() - 1;
			for (i = 0; i < size; i++){
				if ((m_CurrentKeyFrame >= pTrans->m_KeyFrame[i]) && (m_CurrentKeyFrame < pTrans->m_KeyFrame[i + 1])){
					t = (jFloat)(m_CurrentKeyFrame - pTrans->m_KeyFrame[i]) / (jFloat)(pTrans->m_KeyFrame[i + 1] - pTrans->m_KeyFrame[i]);
					m_CurrentTraslation = pTrans->m_Translation[i] + ((pTrans->m_Translation[i + 1] - pTrans->m_Translation[i]) * t);
					break;
				}
			}
			if (i == size)m_CurrentTraslation = pTrans->m_Translation[size];


			//スケール補間
			size = pScale->m_KeyFrame.size() - 1;
			for (i = 0; i < size; i++){
				if ((m_CurrentKeyFrame >= pScale->m_KeyFrame[i]) && (m_CurrentKeyFrame < pScale->m_KeyFrame[i + 1])){
					t = (jFloat)(m_CurrentKeyFrame - pScale->m_KeyFrame[i]) / (jFloat)(pScale->m_KeyFrame[i + 1] - pScale->m_KeyFrame[i]);
					m_CurrentScale = pScale->m_Scale[i] + ((pScale->m_Scale[i + 1] - pScale->m_Scale[i]) * t);
					break;
				}
			}
			if (i == size)m_CurrentScale = pScale->m_Scale[size];
		}

		m_CurrentKeyFrame++;
		if (m_CurrentKeyFrame > keyFrame->m_MaxKeyFrame){
			if (m_IsLoop == true){
				m_CurrentKeyFrame = keyFrame->m_MinKeyFrame;
			}
			else{
				m_CurrentKeyFrame = keyFrame->m_MaxKeyFrame;
			}
		}
	}

}