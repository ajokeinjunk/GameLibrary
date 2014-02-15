#ifndef __H_JOINT_H__
#define __H_JOINT_H__
#include "../../../IEX/iextreme.h"
#include "Constraint.h"

namespace Kmath{
	struct BallJoint{
		float bias;    //�S���̋��x
		unsigned int rigidBodyA;  //����A�Ƃ̃����N
		unsigned int rigidBodyB;  //����B�Ƃ̃����N
		Vector3 anchorA; //����A�̃��[�J�����W�n�ł̐ڑ��_
		Vector3 anchorB; //����B�̃��[�J�����W�n�ł̐ڑ��_
		Constraint constraint; //�S��
	};
}//////// namespace Kmath

#endif