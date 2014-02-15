#ifndef __H_CONTACT_H__
#define __H_CONTACT_H__

#include "../../../IEX/iextreme.h"
#include "Constraint.h"

namespace Kmath{

	//�Փ˓_
	struct ContactPoint{
		float distance; //�ђʐ[�x
		Vector3 pointA; //�Փ˓_(����A�̃��[�J�����W�n)
		Vector3 pointB; //�Փ˓_(����B�̃��[�J�����W�n)
		Vector3 normal; //�Փ˓_�̖@��
		Constraint constraints[3];
		
		void Initialize(){
			constraints[0].accumImpulse = 0.0f;
			constraints[1].accumImpulse = 0.0f;
			constraints[2].accumImpulse = 0.0f;
		}
	};

#define  NUM_CONTACS 4   //�P�x�Ɏ��Ă�Փ˓_��

	//�Փˏ��
	struct ContactData{
		unsigned int m_numContacts;  //�Փ˕��̐�
		float m_friction;  //���C
		ContactPoint m_contactPoints[NUM_CONTACS];  //�Փ˓_�z��
	};
} //////// namespace Kmath

#endif