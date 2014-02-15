#ifndef __H_K_COLLISION_H__
#define __H_K_COLLISION_H__

#include "iextreme.h"
#include "CollisionData.h"
#include "Joint.h"
#include "pair.h"
#include <assert.h>

namespace Kmath{

	namespace Kcol{
		
		// シミュレーション定義
		const int MAX_RIGID_BODIES = 500;
		const int MAX_JOINTS       = 100;
		const int MAX_PAIRS        = 5000;
		const float TIME_STEP      = 0.016f;   //1FPS 0.016秒*60=1秒
		const float CONTACT_BIAS   = 0.1f;
		const float CONTACT_SLOP   = 0.001f;
		const int ITERATION        = 10;   //反復
		//const Vector3  GRAVITY = Vector3(0.0f, -9.8f, 0.0f);

		struct PhysicsData{

		};

		//剛体シミュはここを介して行う

		class Physics{
		private:

			//剛体
			State m_states[MAX_RIGID_BODIES];
			RigidBody m_bodies[MAX_RIGID_BODIES];
			CollidableMesh m_collidables[MAX_RIGID_BODIES];
			unsigned int m_numRigidBodies;
			
			//ジョイント
			BallJoint m_joints[MAX_JOINTS];
			unsigned int m_numJoints;
			
			//ペア
			unsigned int m_pairSwap;
			Pair m_pairs[2][MAX_PAIRS];
			unsigned int m_numPairs[2];

			static int m_frame;
		
		public:
			bool PhysicsInitialize();
			void PhysicsUpdate();
			void PhysicsRelease();
			
			void StartPhysics();      //物理開始
			void AppyExternalForce(); //外力を与える 
			
			//判定大局段階
			void BroadPhase(
				const State *states,
				const CollidableMesh *collidables,
				unsigned int numRigidBodies,
				const Pair *oldPairs,
				const unsigned int numOldPairs,
				Pair *newPairs,
				unsigned int numNewPairs,
				const unsigned int maxPairs);   //関数内で数値を固定させておくためのconst
			
			void NarrowPhase();       //判定小局段階
			

			//セッター・ゲッター
			int GetNumRigidBodies(){return m_numRigidBodies;}
			void SetNumRigigdBodies(int num){m_numRigidBodies = num;}
		};
	}///////////////namespace Kcol

}///////////////namespace Kmath

#endif