#include "../KJ_Math.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Frustumクラス
	//
	//========--------========--------========--------========--------========
	Frustum::Frustum(){

	}

	bool Frustum::IsInside()const{
		return true;
	}

	bool Frustum::IsInside(const Vector3 &point, const float radius)const{
		return true;
	}

	void Frustum::DebugRender(){

	}


	//========--------========--------========--------========--------========
	//
	//			AABBMinMaxクラス
	//
	//========--------========--------========--------========--------========
	bool AABBMinMax::Collide(const AABBMinMax& p1, const AABBMinMax& p2){
		if (p1.maxPoint.x < p2.minPoint.x || p2.maxPoint.x < p1.minPoint.x)return false;
		if (p1.maxPoint.y < p2.minPoint.y || p2.maxPoint.y < p1.minPoint.y)return false;
		if (p1.maxPoint.z < p2.minPoint.z || p2.maxPoint.z < p1.minPoint.z)return false;

		return true;
	}

	//========--------========--------========--------========--------========
	//
	//			AABBCenterHalfクラス
	//
	//========--------========--------========--------========--------========
	bool AABBCenterHalf::Collide(const AABBCenterHalf& p1, const AABBCenterHalf& p2){
		if (p1.center.x + p1.half.x < p2.center.x - p2.half.x || p2.center.x + p2.half.x < p1.center.x - p1.half.x)return false;
		if (p1.center.y + p1.half.y < p2.center.y - p2.half.y || p2.center.y + p2.half.y < p1.center.y - p1.half.y)return false;
		if (p1.center.z + p1.half.z < p2.center.z - p2.half.z || p2.center.z + p2.half.z < p1.center.z - p1.half.z)return false;

		return true;
	}
}