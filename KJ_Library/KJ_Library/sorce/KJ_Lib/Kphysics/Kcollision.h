#ifndef __H_K_COLLISION_H__
#define __H_K_COLLISION_H__

#include "iextreme.h"
#include "CollisionData.h"
#include "Joint.h"
#include "pair.h"
#include <assert.h>

namespace Kmath{

	namespace Kcol{
		
		// �V�~�����[�V������`
		const int MAX_RIGID_BODIES = 500;
		const int MAX_JOINTS       = 100;
		const int MAX_PAIRS        = 5000;
		const float TIME_STEP      = 0.016f;   //1FPS 0.016�b*60=1�b
		const float CONTACT_BIAS   = 0.1f;
		const float CONTACT_SLOP   = 0.001f;
		const int ITERATION        = 10;   //����
		//const Vector3  GRAVITY = Vector3(0.0f, -9.8f, 0.0f);

		struct PhysicsData{

		};

		//���̃V�~���͂�������čs��

		class Physics{
		private:

			//����
			State m_states[MAX_RIGID_BODIES];
			RigidBody m_bodies[MAX_RIGID_BODIES];
			CollidableMesh m_collidables[MAX_RIGID_BODIES];
			unsigned int m_numRigidBodies;
			
			//�W���C���g
			BallJoint m_joints[MAX_JOINTS];
			unsigned int m_numJoints;
			
			//�y�A
			unsigned int m_pairSwap;
			Pair m_pairs[2][MAX_PAIRS];
			unsigned int m_numPairs[2];

			static int m_frame;
		
		public:
			bool PhysicsInitialize();
			void PhysicsUpdate();
			void PhysicsRelease();
			
			void StartPhysics();      //�����J�n
			void AppyExternalForce(); //�O�͂�^���� 
			
			//�����ǒi�K
			void BroadPhase(
				const State *states,
				const CollidableMesh *collidables,
				unsigned int numRigidBodies,
				const Pair *oldPairs,
				const unsigned int numOldPairs,
				Pair *newPairs,
				unsigned int numNewPairs,
				const unsigned int maxPairs);   //�֐����Ő��l���Œ肳���Ă������߂�const
			
			void NarrowPhase();       //���菬�ǒi�K
			

			//�Z�b�^�[�E�Q�b�^�[
			int GetNumRigidBodies(){return m_numRigidBodies;}
			void SetNumRigigdBodies(int num){m_numRigidBodies = num;}
		};
	}///////////////namespace Kcol

}///////////////namespace Kmath

#endif