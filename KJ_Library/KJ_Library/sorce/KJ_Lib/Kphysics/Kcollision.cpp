#include "Kcollision.h"

namespace Kmath{
	namespace Kcol{
		
		
		bool  Physics::PhysicsInitialize(){
			m_numRigidBodies = 0;
			m_numJoints = 0;
			m_numPairs[0] = m_numPairs[1] = 0;
			m_pairSwap = 0;

			return true;
		}

		void  Physics::PhysicsUpdate(){

		}

		void  Physics::PhysicsRelease(){

		}
	
		void  Physics::StartPhysics(){
			//�O�͂�������
			AppyExternalForce();
			//��ǔ���
			//BroadPhase();
			//���ǔ���



		}

		void  Physics::AppyExternalForce(){

		}

		//----------------------------------------------------------------------------------------------------------------------------
		//	�@BroadPhase
		//----------------------------------------------------------------------------------------------------------------------------
		void  Physics::BroadPhase(const State *states,
				const CollidableMesh *collidables,
				unsigned int numRigidBodies,
				const Pair *oldPairs,
				const unsigned int numOldPairs,
				Pair *newPairs,
				unsigned int numNewPairs,
				const unsigned int maxPairs){

#ifdef _DEBUG
			assert(m_states);
			assert(m_collidables);
			assert(oldPairs);
			assert(newPairs);
#endif

			//AABB����,�������胋�[�v
			for(unsigned int i=0; i<numRigidBodies; i++){
				for(unsigned int k=i+1; k<numRigidBodies; k++){
					const State &stateA = states[i];

				}
			}
			
		}

		void  Physics::NarrowPhase(){

		}

	
	}//////// namespace Kcol
} //////////namespace Kmath