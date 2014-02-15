#include "KJ_PhysicsMath.h"

namespace Kmath{
//----------------------------------------------------------------------------------------------------------------------------
//		AABB
//----------------------------------------------------------------------------------------------------------------------------
	AABB::AABB(Vector3 center, Vector3 half){
		m_center.x = center.x;
		m_center.y = center.y;
		m_center.z = center.z;

		m_half.x = half.x;
		m_half.y = half.y;
		m_half.z = half.z;
	}
	
	void AABB::MakeAABB(iexMesh* lpMesh){

	//	情報取得	
	u32 fvf = lpMesh->GetMesh()->GetFVF();
	
	//	頂点サイズ計算
	int VertexSize = D3DXGetFVFVertexSize(fvf) / sizeof(float);

	//	バッファロック
	float	*pVertices;
	lpMesh->GetMesh()->LockVertexBuffer( D3DLOCK_READONLY, (void**)&pVertices );
	

	Vector pos;
	int a;
	Vector3 localmax(0,0,0);
	Vector3 localmin(0,0,0);

	for(unsigned int i=0; i<lpMesh->GetMesh()->GetNumVertices(); i++){
		a = i*3;
		pos.x = pVertices[a];
		pos.y = pVertices[a+1];
		pos.z = pVertices[a+2];

		if(pos.x > localmax.x) localmax.x = pos.x;
		if(pos.x < localmin.x) localmin.x = pos.x;

		if(pos.y > localmax.y) localmax.y = pos.y;
		if(pos.y < localmin.y) localmin.y = pos.y;

		if(pos.z > localmax.z) localmax.z = pos.z;
		if(pos.z < localmin.z) localmin.z = pos.z;
	}

	//Matrix mat = lpMesh->TransMatrix;
	//D3DXMatrixInverse( &mat, NULL, &mat );
	//Vector3 local_min,local_max;

	//m_max = Matrix3CrossMatrix4(m_max, mat);
	//m_min = Matrix3CrossMatrix4(m_min, mat);

	m_center.x = (localmax.x+localmin.x)*0.5f;
	m_center.y = (localmax.y+localmin.y)*0.5f;
	m_center.z = (localmax.y+localmin.y)*0.5f;

	m_half.x = (localmax.x - m_half.x) + 0.1f;
	m_half.y = (localmax.y - m_half.y) + 0.1f;
	m_half.z = (localmax.z - m_half.z) + 0.1f;

	lpMesh->GetMesh()->UnlockVertexBuffer();
	}


//=================================================================================
//
//		汎用巻数
//
//=================================================================================
void IdentityMatrix(Matrix& m){
	m._11 = 1.0f; m._12 = 0;    m._13 = 0;    m._14 = 0;
	m._21 = 0;    m._22 = 1.0f; m._23 = 0;    m._24 = 0;
	m._31 = 0;    m._32 = 0;    m._33 = 1.0f; m._34 = 0;
	m._41 = 0;	  m._42 = 0;    m._43 = 0;    m._44 = 1.0f;
}

void MakeQuaternion(Quaternion &out, const Vector3& axis, float angle){
	Vector3 v = axis;
	v.Normalize();
	out.x = sinf(angle*0.5f)*v.x;
	out.y = sinf(angle*0.5f)*v.y;
	out.z = sinf(angle*0.5f)*v.z;
	out.w = cosf(angle*0.5f);

}

void TransQuaternionToRotationMatrix(Matrix &out,const Quaternion& q){
	float xy,xz,xw,yz,yw,zw;
	xy = q.x*q.y; xz = q.x*q.z; xw = q.x*q.w; yz = q.y*q.z; yw = q.y*q.w; zw = q.z*q.w;
	float xx,yy,zz;
	xx = q.x*q.x; yy = q.y*q.y; zz = q.z*q.z;

		out._11 = 1.0f-2.0f*(yy+zz);  out._12 = 2.0f*(xy + zw);      out._13 = 2.0f*(xz - yw);      out._14 = 0;
		out._21 = 2.0f*(xy - zw);     out._22 = 1.0f-2.0f*(xx+zz);   out._23 = 2.0f*(yz + xw);      out._24 = 0;
		out._31 = 2.0f*(xz + yw);     out._32 = 2.0f*(yz - xw);      out._33 = 1.0f-2.0f*(xx+yy);   out._34 = 0;
		out._41 = 0;                  out._42 = 0;                   out._43 = 0;                   out._44 = 1.0f;
}

void TransCoord(Vector3& out, const Vector3& v, const Matrix& m){
	out.x = v.x*m._11 + v.y*m._21 + v.z*m._31 + m._41;
	out.y = v.x*m._12 + v.y*m._22 + v.z*m._32 + m._42;
	out.z = v.x*m._13 + v.y*m._23 + v.z*m._33 + m._43;
}

void MatrixRotateZ3d(Matrix& out, float roll){
	out._11 = cosf(roll);  out._12 = sinf(roll); out._13 = 0;    out._14 = 0;
	out._21 = -sinf(roll); out._22 = cosf(roll); out._23 = 0;    out._24 = 0;
	out._31 = 0;           out._32 = 0;          out._33 = 1.0f; out._34 = 0;
	out._41 = 0;           out._42 = 0;          out._43 = 0;    out._44 = 1.0f;
}

void Kmath::MatrixInverse(Matrix& out, const Matrix& mat){
	
}

void ViewMatrix(Matrix& out, const Matrix& cPoseMat){
	out._11 = cPoseMat._11; out._12 = cPoseMat._21; out._13 = cPoseMat._31; out._14 = cPoseMat._41;
}

bool CheckCollision(){
	return true;
}

} //namespace Kmath