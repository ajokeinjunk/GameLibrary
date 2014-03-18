#pragma once

#include "Animation2D.h"
#include <string>
#include <vector>
#include <memory>
#include "../KJ_Defines/KJ_Defines.h"

namespace Klibrary{
	struct PosKey{
		jUInt32 keyFrame;
		Vector2 pos;
	};

	struct ScaleKey{
		jUInt32 keyFrame;
		Vector2 scale;
	};

	struct RotateKey{
		jUInt32 keyFrame;
		Vector2 rotate;
	};

	static PosKey LifeBarAnimPos[1] = {
		{ 0,    Vector2(0, 0)  },
	/*	{ 60,  Vector2(100, 0)},
		{ 120, Vector2(0, 100)},
		{ 180, Vector2(0,   0)}*/
	};

	static ScaleKey LifeBarAnimScale[1] = {
		{ 0, Vector2(1, 1) },
		//{ 60, Vector2(0, 0.1f)},
		//{ 120, Vector2(0.9f, 0.9f)},
		//{ 180, Vector2(1.0f, 1.0f)}

	};

	static RotateKey LifeBarAnimRot[4] = {
		{ 0, Vector2(0, 0) },
		{ 60, Vector2(K_2PI, 0) },
		//{ 180, Vector2(0, 0) }
		{ 180, Vector2(-K_2PI, 0) },
		{ 240, Vector2(0, 0) }

	};

	enum AnimtaionType{
		LIFE_BAR_ANIM = 0,
	};

	enum Animation2DType{
		BIGGER = 0,
	};

	inline void SetAnimation2D(Animation2DSharedPtr& animation){
		animation =  std::make_shared<Animation2D>();
		animation->SetCurrentMotion(LIFE_BAR_ANIM);

		Motion2DSharedPtr temp(new Motion2D);

		//lol Reserve不足問題。気を付けて置く。
		temp->m_TranslationKey.m_KeyFrame.reserve(100);
		temp->m_TranslationKey.m_Translation.reserve(100);
		
		temp->m_ScaleKey.m_KeyFrame.reserve(100);
		temp->m_ScaleKey.m_Scale.reserve(100);
		
		temp->m_RotationKey.m_KeyFrame.reserve(100);
		temp->m_RotationKey.m_Rotation.reserve(100);

		for (int i = 0; i < sizeof(LifeBarAnimPos) / sizeof(PosKey); i++){
			if (temp->m_MaxKeyFrame < LifeBarAnimPos[i].keyFrame){ temp->m_MaxKeyFrame = LifeBarAnimPos[i].keyFrame; }
			if (temp->m_MinKeyFrame > LifeBarAnimPos[i].keyFrame){ temp->m_MinKeyFrame = LifeBarAnimPos[i].keyFrame; }
			
			temp->m_TranslationKey.m_KeyFrame.push_back(LifeBarAnimPos[i].keyFrame);
			temp->m_TranslationKey.m_Translation.push_back(LifeBarAnimPos[i].pos);
		}

		for (int i = 0; i < sizeof(LifeBarAnimScale) / sizeof(ScaleKey); i++){
			if (temp->m_MaxKeyFrame < LifeBarAnimScale[i].keyFrame){ temp->m_MaxKeyFrame = LifeBarAnimScale[i].keyFrame; }
			if (temp->m_MinKeyFrame > LifeBarAnimScale[i].keyFrame){ temp->m_MinKeyFrame = LifeBarAnimScale[i].keyFrame; }
			
			temp->m_ScaleKey.m_KeyFrame.push_back(LifeBarAnimScale[i].keyFrame);
			temp->m_ScaleKey.m_Scale.push_back(LifeBarAnimScale[i].scale);
		}

		for (int i = 0; i < sizeof(LifeBarAnimRot) / sizeof(RotateKey); i++){
			if (temp->m_MaxKeyFrame < LifeBarAnimRot[i].keyFrame){ temp->m_MaxKeyFrame = LifeBarAnimRot[i].keyFrame; }
			if (temp->m_MinKeyFrame > LifeBarAnimRot[i].keyFrame){ temp->m_MinKeyFrame = LifeBarAnimRot[i].keyFrame; }

			temp->m_RotationKey.m_KeyFrame.push_back(LifeBarAnimRot[i].keyFrame);
			temp->m_RotationKey.m_Rotation.push_back(LifeBarAnimRot[i].rotate);
		}

		animation->AddMotion(BIGGER, temp);
		animation->SetCurrentMotion(BIGGER);
	}
}

