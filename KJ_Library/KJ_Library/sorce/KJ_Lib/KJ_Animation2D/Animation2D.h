#ifndef H_KLIB_ANIMATION_2D_H
#define H_KLIB_ANIMATION_2D_H

#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Defines/KJ_Defines.h"
#include <vector>
#include <memory>
#include <unordered_map>

namespace Klibrary{
	struct RotationKeyFrame{
		std::vector<Vector2> m_Rotation;  //x,y共に中身はラジアン
		std::vector<jUInt32> m_KeyFrame;  //xがz軸回転、yがy軸回転。
	};

	struct ScaleKeyFrame{
		std::vector<Vector2> m_Scale;
		std::vector<jUInt32> m_KeyFrame;
	};

	struct TranslationKeyFrame{
		std::vector<Vector2> m_Translation;
		std::vector<jUInt32> m_KeyFrame;
	};

	struct Motion2D{
		RotationKeyFrame    m_RotationKey;
		ScaleKeyFrame       m_ScaleKey;
		TranslationKeyFrame m_TranslationKey;
		jUInt32             m_MinKeyFrame;
		jUInt32             m_MaxKeyFrame;
		Motion2D() :m_MinKeyFrame(99999), m_MaxKeyFrame(0){}
	};

	typedef std::shared_ptr<Motion2D> Motion2DSharedPtr;
	typedef std::unordered_map<jUInt8, Motion2DSharedPtr> MotionsMap;   //キーはモーションID、データは全キーフレームデータ

	class Animation2D;
	typedef std::shared_ptr<Animation2D> Animation2DSharedPtr;
	typedef std::weak_ptr<Animation2D> Animation2DWeakPtr;

	//全テイクアニメーション情報を格納
	class Animation2D{
	private:
		MotionsMap m_Motions;       //全モーションを格納、キーはモーションID、中身はワンモーションデータ
		
		jUInt8  m_CurrntMotionID;   //現在のモーション
		jUInt32 m_CurrentKeyFrame;  //現在のキーフレーム

		Vector2 m_CurrentScale;     
		Vector2 m_CurrentRotation;
		Vector2 m_CurrentTraslation;

		bool    m_IsAnimation;     //アニメーションを再生するか
		bool    m_IsLoop;          //アニメーションをループするか

	public:
		Animation2D() : m_CurrentKeyFrame(0), m_CurrntMotionID(0), m_IsAnimation(true), m_IsLoop(false),
			m_CurrentScale(1.0f, 1.0f), m_CurrentRotation(0, 0), m_CurrentTraslation(0, 0){}

		void Initialize();
		void Update(jUInt32 deltaMs);
		void Release(){ m_Motions.clear(); }

		inline void AddMotion(jUInt8 motioniID, Motion2DSharedPtr& keyFrameList){ m_Motions[motioniID] = keyFrameList; }

		void Animation(bool able){ m_IsAnimation = able; }
		void Loop(bool able){ m_IsLoop = able; }
		void ReturnTopKeyFrame(){ m_CurrentKeyFrame = m_Motions[m_CurrntMotionID]->m_MinKeyFrame; }

		inline bool SetCurrentMotion(jInt8 currentMotion);
		inline void SetCurrentKeyFrame(jUInt32 keyFrame);

		const Vector2& GetCurrentTranslation()const{ return m_CurrentTraslation; }
		const Vector2& GetCurrentRotation()const{ return m_CurrentRotation; }
		const Vector2& GetCurrentScale()const{ return m_CurrentScale; }
		const MotionsMap& GetMotionMap()const{ return m_Motions; }
		jUInt32 GetCurrentKeyFrame()const{ return m_CurrentKeyFrame; }

		bool IsAnimation(){ return m_IsAnimation; }
		bool IsLoop(){ return m_IsLoop; }
	};

	void Animation2D::SetCurrentKeyFrame(jUInt32 keyFrame){
		if (keyFrame > m_Motions[m_CurrntMotionID]->m_MaxKeyFrame){ m_CurrentKeyFrame = m_Motions[m_CurrntMotionID]->m_MaxKeyFrame; }
		else if (keyFrame < m_Motions[m_CurrntMotionID]->m_MinKeyFrame){ m_CurrentKeyFrame = m_Motions[m_CurrntMotionID]->m_MinKeyFrame; }
		else{ m_CurrentKeyFrame = keyFrame; }
	}

	bool Animation2D::SetCurrentMotion(jInt8 currentMotionID){
		if (m_Motions.find(currentMotionID) == m_Motions.end()){
			return false;}

		m_CurrntMotionID = currentMotionID;
		m_CurrentKeyFrame = m_Motions[m_CurrntMotionID]->m_MinKeyFrame;
		return true;
	}
}

#endif