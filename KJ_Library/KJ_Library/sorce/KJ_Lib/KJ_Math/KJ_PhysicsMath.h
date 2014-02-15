#ifndef __H_PHYSICS_MATH_H__
#define __H_PHYSICS_MATH_H__

 #pragma warning(disable:4482)


//----------------------------------------------------------------------------------------------------------------------------
//		AABBƒNƒ‰ƒX
//----------------------------------------------------------------------------------------------------------------------------
namespace Kmath{


class AABB{
public:
	Vector3 m_center;
	Vector3 m_half;
		
	AABB(){}
	AABB(Vector3 center, Vector3 half);
	void MakeAABB(iexMesh* lpMesh);
	void SetAABB(Vector3& pos);
};

	

void IdentityMatrix(Matrix& m);
void MakeQuaternion(Quaternion &out, const Vector3& axis, float angle);
void TransQuaternionToRotationMatrix(Matrix &out,const Quaternion& q);
void TransCoord(Vector3& out, const Vector3& v, const Matrix& m);
void MatrixRotateZ3d(Matrix& out, float roll);
void MatrixInverse(Matrix& out, const Matrix& mat);
void ViewMatrix(Matrix& out, const Matrix& cPoseMat);
bool CheckCollision();

} /////////namespace Kmath
#endif