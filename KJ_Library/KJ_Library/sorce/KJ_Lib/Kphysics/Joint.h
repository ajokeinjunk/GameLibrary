#ifndef __H_JOINT_H__
#define __H_JOINT_H__
#include "../../../IEX/iextreme.h"
#include "Constraint.h"

namespace Kmath{
	struct BallJoint{
		float bias;    //拘束の強度
		unsigned int rigidBodyA;  //剛体Aとのリンク
		unsigned int rigidBodyB;  //剛体Bとのリンク
		Vector3 anchorA; //剛体Aのローカル座標系での接続点
		Vector3 anchorB; //剛体Bのローカル座標系での接続点
		Constraint constraint; //拘束
	};
}//////// namespace Kmath

#endif