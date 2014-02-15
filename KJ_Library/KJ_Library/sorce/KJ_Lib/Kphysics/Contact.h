#ifndef __H_CONTACT_H__
#define __H_CONTACT_H__

#include "../../../IEX/iextreme.h"
#include "Constraint.h"

namespace Kmath{

	//衝突点
	struct ContactPoint{
		float distance; //貫通深度
		Vector3 pointA; //衝突点(剛体Aのローカル座標系)
		Vector3 pointB; //衝突点(剛体Bのローカル座標系)
		Vector3 normal; //衝突点の法線
		Constraint constraints[3];
		
		void Initialize(){
			constraints[0].accumImpulse = 0.0f;
			constraints[1].accumImpulse = 0.0f;
			constraints[2].accumImpulse = 0.0f;
		}
	};

#define  NUM_CONTACS 4   //１度に持てる衝突点数

	//衝突情報
	struct ContactData{
		unsigned int m_numContacts;  //衝突物の数
		float m_friction;  //摩擦
		ContactPoint m_contactPoints[NUM_CONTACS];  //衝突点配列
	};
} //////// namespace Kmath

#endif