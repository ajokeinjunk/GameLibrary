#ifndef __H_CONSTRAINT_H__
#define __H_CONSTRAINT_H__

#include "../../../IEX/iextreme.h"

namespace Kmath{
	struct Constraint{
		Vector3 axis;  //�S����
		float jacDiagInv; //�S�����̕���
		float rhs;       //�����S����
		float lowerLimit; //�S���͂̉���
		float upperLimit; //�S���͂̏��
		float accumImpulse; //�~�ς����S����
	};

}/////////  namespace Kmath

#endif