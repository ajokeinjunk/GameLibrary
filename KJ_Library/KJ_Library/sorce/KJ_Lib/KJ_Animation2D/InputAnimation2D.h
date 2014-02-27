#ifndef H_KLIB_INPUT_ANIMATION_2D_H
#define H_KLIB_INPUT_ANIMATION_2D_H
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

	//試しに横長で始まったあと、
	//縦に伸びるアニメーションを作ってみる。
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

	//inline void SetAnimation2D(Animation2DSharedPtr& animation){
	//	animation =  std::make_shared<Animation2D>();
	//	animation->SetAnimationID(LIFE_BAR_ANIM);

	//	Motion2DSharedPtr temp(new Motion2D);

	//	//lol Reserve不足問題。気を付けて置く。
	//	temp->m_posKey.m_keyFrame.reserve(100);
	//	temp->m_posKey.m_position.reserve(100);
	//	
	//	temp->m_scaleKey.m_keyFrame.reserve(100);
	//	temp->m_scaleKey.m_scale.reserve(100);
	//	
	//	temp->m_rotateKey.m_keyFrame.reserve(100);
	//	temp->m_rotateKey.m_rotation.reserve(100);

	//	for (int i = 0; i < sizeof(LifeBarAnimPos) / sizeof(PosKey); i++){
	//		if (temp->m_maxKeyFrame < LifeBarAnimPos[i].keyFrame){ temp->m_maxKeyFrame = LifeBarAnimPos[i].keyFrame; }
	//		if (temp->m_minKeyFrame > LifeBarAnimPos[i].keyFrame){ temp->m_minKeyFrame = LifeBarAnimPos[i].keyFrame; }
	//		
	//		temp->m_posKey.m_keyFrame.push_back(LifeBarAnimPos[i].keyFrame);
	//		temp->m_posKey.m_position.push_back(LifeBarAnimPos[i].pos);
	//	}

	//	for (int i = 0; i < sizeof(LifeBarAnimScale) / sizeof(ScaleKey); i++){
	//		if (temp->m_maxKeyFrame < LifeBarAnimScale[i].keyFrame){ temp->m_maxKeyFrame = LifeBarAnimScale[i].keyFrame; }
	//		if (temp->m_minKeyFrame > LifeBarAnimScale[i].keyFrame){ temp->m_minKeyFrame = LifeBarAnimScale[i].keyFrame; }
	//		
	//		temp->m_scaleKey.m_keyFrame.push_back(LifeBarAnimScale[i].keyFrame);
	//		temp->m_scaleKey.m_scale.push_back(LifeBarAnimScale[i].scale);
	//	}

	//	for (int i = 0; i < sizeof(LifeBarAnimRot) / sizeof(RotateKey); i++){
	//		if (temp->m_maxKeyFrame < LifeBarAnimRot[i].keyFrame){ temp->m_maxKeyFrame = LifeBarAnimRot[i].keyFrame; }
	//		if (temp->m_minKeyFrame > LifeBarAnimRot[i].keyFrame){ temp->m_minKeyFrame = LifeBarAnimRot[i].keyFrame; }

	//		temp->m_rotateKey.m_keyFrame.push_back(LifeBarAnimRot[i].keyFrame);
	//		temp->m_rotateKey.m_rotation.push_back(LifeBarAnimRot[i].rotate);
	//	}

	//	animation->AddMotion(BIGGER, temp);
	//	animation->SetCurrentMotion(BIGGER);
	//}
}

#endif