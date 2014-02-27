#ifndef H_K_MATRIX_H
#define H_K_MATRIX_H

namespace Klibrary{

//========--------========--------========--------========--------========
//
//			Matrix3クラス
//
//========--------========--------========--------========--------========

	//コンストラクタ
	inline Matrix3::Matrix3(){
		m1.x = 0; m1.y = 0; m1.z = 0;
		m2.x = 0; m2.y = 0; m2.z = 0;
		m3.x = 0; m3.y = 0; m3.z = 0;
	}

	inline Matrix3::Matrix3(const Matrix3& m){
		m1.x = m.m1.x; m1.y = m.m1.y; m1.z = m.m1.z;
		m2.x = m.m2.x; m2.y = m.m2.y; m2.z = m.m2.z;
		m3.x = m.m3.x; m3.y = m.m3.y; m3.z = m.m3.z;
	}

	
	inline Matrix3::Matrix3(const Vector3 v1, const Vector3& v2, const Vector3& v3){
		
		m1.x = v1.x; m1.y = v1.y; m1.z = v1.z;
		m2.x = v2.x; m2.y = v2.y; m2.z = v2.z;
		m3.x = v3.x; m3.y = v3.y; m3.z = v3.z;
	}
		

	//オペレーター
	//代入
	inline Matrix3& Matrix3::operator = (const Matrix3& m){
		m1.x = m.m1.x; m1.y = m.m1.y; m1.z = m.m1.z;
		m2.x = m.m2.x; m2.y = m.m2.y; m2.z = m.m2.z;
		m3.x = m.m3.x; m3.y = m.m3.y; m3.z = m.m3.z;
		return *this;
	}


	inline Matrix3& Matrix3::operator +=(const Matrix3& m){
		m1.x += m.m1.x; m1.y += m.m1.y; m1.z += m.m1.z;
		m2.x += m.m2.x; m2.y += m.m2.y; m2.z += m.m2.z;
		m3.x += m.m3.x; m3.y += m.m3.y; m3.z += m.m3.z;
		return *this;
	}

	inline Matrix3& Matrix3::operator -=(const Matrix3& m){
		m1.x -= m.m1.x; m1.y -= m.m1.y; m1.z -= m.m1.z;
		m2.x -= m.m2.x; m2.y -= m.m2.y; m2.z -= m.m2.z;
		m3.x -= m.m3.x; m3.y -= m.m3.y; m3.z -= m.m3.z;
		return *this;
	}
	


	inline Matrix3& Matrix3::operator *=(const Matrix3& mat){
		*this = Matrix3(
			Vector3(m1.x*mat.m1.x + m1.y*mat.m2.x + m1.z*mat.m3.x,
					m1.x*mat.m1.y + m1.y*mat.m2.y + m1.z*mat.m3.y,
					m1.x*mat.m1.z + m1.y*mat.m2.z + m1.z*mat.m3.z),

			Vector3(m2.x*mat.m1.x + m2.y*mat.m2.x + m2.z*mat.m3.x,
					m2.x*mat.m1.y + m2.y*mat.m2.y + m2.z*mat.m3.y,
					m2.x*mat.m1.z + m2.y*mat.m2.z + m2.z*mat.m3.z),

			Vector3(m3.x*mat.m1.x + m3.y*mat.m2.x + m3.z*mat.m3.x,
					m3.x*mat.m1.y + m3.y*mat.m2.y + m3.z*mat.m3.y,
					m3.x*mat.m1.z + m3.y*mat.m2.z + m3.z*mat.m3.z)
		);

		return *this;
	}

	



	//inline Matrix3& Matrix3::operator /=(const Matrix3& m){
	//	return *this;
	//}

	//単項
	/*inline Vector3& Matrix3::operator[](int i){
		return *(&m1+i);
	}
	inline Vector3 Matrix3::operator[](int i)const{
		return *(&m1+i);
	}*/
	
	//inline float Matrix3::operator[](int i)const{
	//	return *(&m1.x+i);
	//}

	//2項
	inline const Matrix3 Matrix3::operator +(const Matrix3& m)const{
		return Matrix3(m1+m.m1, m2+m.m2, m3+m.m3);
	}
	
	inline const Matrix3 Matrix3::operator -(const Matrix3& m)const{
		return Matrix3(m1-m.m1, m2-m.m2, m3-m.m3);
	}

	inline const Matrix3 Matrix3::operator *(const Matrix3& mat)const{
		return Matrix3(
			Vector3(m1.x*mat.m1.x + m1.y*mat.m2.x + m1.z*mat.m3.x, 
			        m1.x*mat.m1.y + m1.y*mat.m2.y + m1.z*mat.m3.y,
			        m1.x*mat.m1.z + m1.y*mat.m2.z + m1.z*mat.m3.z),
			
		    Vector3(m2.x*mat.m1.x + m2.y*mat.m2.x + m2.z*mat.m3.x, 
			        m2.x*mat.m1.y + m2.y*mat.m2.y + m2.z*mat.m3.y,
			        m2.x*mat.m1.z + m2.y*mat.m2.z + m2.z*mat.m3.z),

			Vector3(m3.x*mat.m1.x + m3.y*mat.m2.x + m3.z*mat.m3.x, 
			        m3.x*mat.m1.y + m3.y*mat.m2.y + m3.z*mat.m3.y,
			        m3.x*mat.m1.z + m3.y*mat.m2.z + m3.z*mat.m3.z)
			);
	}

	//inline const Matrix3 Matrix3::operator /(const Matrix3& m)const{
	//	return Matrix3(m1*m.m1, m2*m.m2, m3*m.m3);
	//}

	inline void Matrix3::Identify(){
		m1.x = 1.0f; m1.y = 0;    m1.z = 0;
		m2.x = 0;    m2.y = 1.0f; m2.z = 0;
		m3.x = 0;    m3.y = 0;    m3.z = 1.0f;
	}




//========--------========--------========--------========--------========
//
//			Matrix4クラス
//
//========--------========--------========--------========--------========
	//コンストラクタ
	inline Matrix4::Matrix4(){
		m1.x = 0; m1.y = 0; m1.z = 0; m1.w = 0;
		m2.x = 0; m2.y = 0; m2.z = 0; m2.w = 0;
		m3.x = 0; m3.y = 0; m3.z = 0; m3.w = 0;
		m4.x = 0; m4.y = 0; m4.z = 0; m4.w = 0;
	}

	inline Matrix4::Matrix4(const Matrix4& m){
		m1.x = m.m1.x; m1.y = m.m1.y; m1.z = m.m1.z; m1.w = m.m1.w;
		m2.x = m.m2.x; m2.y = m.m2.y; m2.z = m.m2.z; m2.w = m.m2.w;
		m3.x = m.m3.x; m3.y = m.m3.y; m3.z = m.m3.z; m3.w = m.m3.w;
		m4.x = m.m4.x; m4.y = m.m4.y; m4.z = m.m4.z; m4.w = m.m4.w;
	}

	
	inline Matrix4::Matrix4(const Vector4 v1, const Vector4& v2, const Vector4& v3, const Vector4& v4){
		m1.x = v1.x; m1.y = v1.y; m1.z = v1.z; m1.w = v1.w;
		m2.x = v2.x; m2.y = v2.y; m2.z = v2.z; m2.w = v2.w;
		m3.x = v3.x; m3.y = v3.y; m3.z = v3.z; m3.w = v3.w;
		m4.x = v4.x; m4.y = v4.y; m4.z = v4.z; m4.w = v4.w;
	}
		

	//オペレーター
	//代入
	inline Matrix4& Matrix4::operator = (const Matrix4& mat){
		m1.x = mat.m1.x; m1.y = mat.m1.y; m1.z = mat.m1.z; m1.w = mat.m1.w;
		m2.x = mat.m2.x; m2.y = mat.m2.y; m2.z = mat.m2.z; m2.w = mat.m2.w;
		m3.x = mat.m3.x; m3.y = mat.m3.y; m3.z = mat.m3.z; m3.w = mat.m3.w;
		m4.x = mat.m4.x; m4.y = mat.m4.y; m4.z = mat.m4.z; m4.w = mat.m4.w;

		return *this;
	}


	inline Matrix4& Matrix4::operator +=(const Matrix4& mat){
		m1.x += mat.m1.x; m1.y += mat.m1.y; m1.z += mat.m1.z; m1.w += mat.m1.w;
		m2.x += mat.m2.x; m2.y += mat.m2.y; m2.z += mat.m2.z; m2.w += mat.m2.w;
		m3.x += mat.m3.x; m3.y += mat.m3.y; m3.z += mat.m3.z; m3.w += mat.m3.w;
		m4.x += mat.m4.x; m4.y += mat.m4.y; m4.z += mat.m4.z; m4.w += mat.m4.w;

		return *this;
	}

	inline Matrix4& Matrix4::operator -=(const Matrix4& mat){
		m1.x -= mat.m1.x; m1.y -= mat.m1.y; m1.z -= mat.m1.z; m1.w -= mat.m1.w;
		m2.x -= mat.m2.x; m2.y -= mat.m2.y; m2.z -= mat.m2.z; m2.w -= mat.m2.w;
		m3.x -= mat.m3.x; m3.y -= mat.m3.y; m3.z -= mat.m3.z; m3.w -= mat.m3.w;
		m4.x -= mat.m4.x; m4.y -= mat.m4.y; m4.z -= mat.m4.z; m4.w -= mat.m4.w;
		return *this;
	}

	inline Matrix4& Matrix4::operator *=(const Matrix4& mat){
		*this = Matrix4(
			Vector4(m1.x*mat.m1.x + m1.y*mat.m2.x + m1.z*mat.m3.x + m1.w*mat.m4.x,
			m1.x*mat.m1.y + m1.y*mat.m2.y + m1.z*mat.m3.y + m1.w*mat.m4.y,
			m1.x*mat.m1.z + m1.y*mat.m2.z + m1.z*mat.m3.z + m1.w*mat.m4.z,
			m1.x*mat.m1.w + m1.y*mat.m2.w + m1.z*mat.m3.w + m1.w*mat.m4.w),

			Vector4(m2.x*mat.m1.x + m2.y*mat.m2.x + m2.z*mat.m3.x + m2.w*mat.m4.x,
			m2.x*mat.m1.y + m2.y*mat.m2.y + m2.z*mat.m3.y + m2.w*mat.m4.y,
			m2.x*mat.m1.z + m2.y*mat.m2.z + m2.z*mat.m3.z + m2.w*mat.m4.z,
			m2.x*mat.m1.w + m2.y*mat.m2.w + m2.z*mat.m3.w + m2.w*mat.m4.w),

			Vector4(m3.x*mat.m1.x + m3.y*mat.m2.x + m3.z*mat.m3.x + m3.w*mat.m4.x,
			m3.x*mat.m1.y + m3.y*mat.m2.y + m3.z*mat.m3.y + m3.w*mat.m4.y,
			m3.x*mat.m1.z + m3.y*mat.m2.z + m3.z*mat.m3.z + m3.w*mat.m4.z,
			m3.x*mat.m1.w + m3.y*mat.m2.w + m3.z*mat.m3.w + m3.w*mat.m4.w),

			Vector4(m4.x*mat.m1.x + m4.y*mat.m2.x + m4.z*mat.m3.x + m4.w*mat.m4.x,
			m4.x*mat.m1.y + m4.y*mat.m2.y + m4.z*mat.m3.y + m4.w*mat.m4.y,
			m4.x*mat.m1.z + m4.y*mat.m2.z + m4.z*mat.m3.z + m4.w*mat.m4.z,
			m4.x*mat.m1.w + m4.y*mat.m2.w + m4.z*mat.m3.w + m4.w*mat.m4.w)
		);

		return *this;
	}

	//inline Matrix3& Matrix3::operator /=(const Matrix3& m){
	//	
	//	return *this;
	//}

	//単項
	//inline Vector4& Matrix4::operator[](int i){
	//	return *(&m1+i);
	//}
	//
	//inline Vector4 Matrix4::operator[](int i)const{
	//	return *(&m1+i);
	//}

	//inline float Matrix4::operator[](int i)const{
	//	return *(&m1.x+i);
	//}

	//2項
	inline const Matrix4 Matrix4::operator +(const Matrix4& mat)const{
		return Matrix4(m1+mat.m1, m2+mat.m2, m3+mat.m3, m4+mat.m4);
	}
	
	inline const Matrix4 Matrix4::operator -(const Matrix4& mat)const{
		return Matrix4(m1-mat.m1, m2-mat.m2, m3-mat.m3, m4-mat.m4);
	}


	inline const Matrix4 Matrix4::operator *(const Matrix4& mat)const{
		return Matrix4(
			Vector4(m1.x*mat.m1.x + m1.y*mat.m2.x + m1.z*mat.m3.x + m1.w*mat.m4.x, 
			        m1.x*mat.m1.y + m1.y*mat.m2.y + m1.z*mat.m3.y + m1.w*mat.m4.y,
					m1.x*mat.m1.z + m1.y*mat.m2.z + m1.z*mat.m3.z + m1.w*mat.m4.z,
			        m1.x*mat.m1.w + m1.y*mat.m2.w + m1.z*mat.m3.w + m1.w*mat.m4.w
					),
			
		    Vector4(m2.x*mat.m1.x + m2.y*mat.m2.x + m2.z*mat.m3.x + m2.w*mat.m4.x,
			        m2.x*mat.m1.y + m2.y*mat.m2.y + m2.z*mat.m3.y + m2.w*mat.m4.y,
			        m2.x*mat.m1.z + m2.y*mat.m2.z + m2.z*mat.m3.z + m2.w*mat.m4.z,
			        m2.x*mat.m1.w + m2.y*mat.m2.w + m2.z*mat.m3.w + m2.w*mat.m4.w
					),

			Vector4(m3.x*mat.m1.x + m3.y*mat.m2.x + m3.z*mat.m3.x + m3.w*mat.m4.x,
			        m3.x*mat.m1.y + m3.y*mat.m2.y + m3.z*mat.m3.y + m3.w*mat.m4.y,
			        m3.x*mat.m1.z + m3.y*mat.m2.z + m3.z*mat.m3.z + m3.w*mat.m4.z,
			        m3.x*mat.m1.w + m3.y*mat.m2.w + m3.z*mat.m3.w + m3.w*mat.m4.w
					),
		
			Vector4(m4.x*mat.m1.x + m4.y*mat.m2.x + m4.z*mat.m3.x + m4.w*mat.m4.x, 
			        m4.x*mat.m1.y + m4.y*mat.m2.y + m4.z*mat.m3.y + m4.w*mat.m4.y,
					m4.x*mat.m1.z + m4.y*mat.m2.z + m4.z*mat.m3.z + m4.w*mat.m4.z,
			        m4.x*mat.m1.w + m4.y*mat.m2.w + m4.z*mat.m3.w + m4.w*mat.m4.w
					)
			);
	}





	inline void Matrix4::Identify(){
		m1.x = 1.0f; m1.y = 0;    m1.z = 0;    m1.w = 0;
		m2.x = 0;    m2.y = 1.0f; m2.z = 0;    m2.w = 0;
		m3.x = 0;    m3.y = 0;    m3.z = 1.0f; m3.w = 0;
		m4.x = 0;    m4.y = 0;    m4.z = 0;    m4.w = 1.0f;
	}

	inline void Matrix4::Inverse(){

	}

	inline void Matrix4::Inverse(Matrix4& out){

	}

//========--------========--------========--------========--------========
//
//			Matrix4関数
//
//========--------========--------========--------========--------========
	
	inline void Mat4MakeProjectionMatrixLH(Matrix4& out, float fieldOfView, float aspectRatio, float nearClipping, float farClipping){
		out.m2.x = 0;
		out.m2.y = 1.0f / tanf(fieldOfView*0.5f);
		out.m2.z = 0;
		out.m2.w = 0;

		out.m1.x = out.m2.y / aspectRatio;
		out.m1.y = 0;
		out.m1.z = 0;
		out.m1.w = 0;

		out.m3.x = 0;
		out.m3.y = 0;
		out.m3.z = farClipping / (farClipping-nearClipping);
		out.m3.w = 1;

		out.m4.x = 0;
		out.m4.y = 0;
		out.m4.z = (-nearClipping*farClipping) / (farClipping-nearClipping);
		out.m4.w = 0;
	}

	inline void Mat4MakeViewMatrixLH(Matrix4& out, const Vector3& position, const Vector3& target, const Vector3& upwardDirection){
		Vector3 zAxis;
		zAxis.x = target.x - position.x;
		zAxis.y = target.y - position.y;
		zAxis.z = target.z - position.z;
		zAxis.Normalize();

		Vector3 xAxis;
		Vec3Cross(xAxis, upwardDirection, zAxis);
		xAxis.Normalize();

		Vector3 yAxis;
		Vec3Cross(yAxis, zAxis, xAxis);
		yAxis.Normalize();

		out.m1.x = xAxis.x;
		out.m2.x = xAxis.y;
		out.m3.x = xAxis.z;

		out.m1.y = yAxis.x;
		out.m2.y = yAxis.y;
		out.m3.y = yAxis.z;

		out.m1.z = zAxis.x;
		out.m2.z = zAxis.y;
		out.m3.z = zAxis.z;

		out.m1.w = 0;
		out.m2.w = 0;
		out.m3.w = 0;

		out.m4.x = -(xAxis.x*position.x + xAxis.y*position.y + xAxis.z*position.z);
		out.m4.y = -(yAxis.x*position.x + yAxis.y*position.y + yAxis.z*position.z);
		out.m4.z = -(zAxis.x*position.x + zAxis.y*position.y + zAxis.z*position.z);
		out.m4.w = 1.0f;
	}
	
	inline void Mat4MakeScalingMatrix(Matrix4& out, float scale){
		out.m1.x = scale;
		out.m1.y = 0;
		out.m1.z = 0;
		out.m1.w = 0;

		out.m2.x = 0;
		out.m2.y = scale; 
		out.m2.z = 0;
		out.m2.w = 0;

		out.m3.x = 0; 
		out.m3.y = 0;
		out.m3.z = scale; 
		out.m3.w = 0;

		out.m4.x = 0;
		out.m4.y = 0;
		out.m4.z = 0;
		out.m4.w = 1.0f;
	}
	inline void Mat4MakeScalingMatrix(Matrix4& out, float x, float y, float z){
		out.m1.x = x;
		out.m1.y = 0;
		out.m1.z = 0;
		out.m1.w = 0;

		out.m2.x = 0;
		out.m2.y = y; 
		out.m2.z = 0;
		out.m2.w = 0;

		out.m3.x = 0; 
		out.m3.y = 0;
		out.m3.z = z; 
		out.m3.w = 0;

		out.m4.x = 0;
		out.m4.y = 0;
		out.m4.z = 0;
		out.m4.w = 1.0f;
	}
	
	inline void Mat4MakeScalingMatrix(Matrix4& out, const Vector3& scale){
		out.m1.x = scale.x;
		out.m1.y = 0;
		out.m1.z = 0;
		out.m1.w = 0;

		out.m2.x = 0;
		out.m2.y = scale.y; 
		out.m2.z = 0;
		out.m2.w = 0;

		out.m3.x = 0; 
		out.m3.y = 0;
		out.m3.z = scale.z; 
		out.m3.w = 0;

		out.m4.x = 0;
		out.m4.y = 0;
		out.m4.z = 0;
		out.m4.w = 1.0f;
	}

	//要テスト
	inline void Mat4MakeRotationMatrixZXY(Matrix4& out, const Vector3 rotation){
		float	sinX, sinY, sinZ, cosX, cosY, cosZ;

		sinX = sinf(rotation.x);	
		sinY = sinf(rotation.y); 
		sinZ = sinf(rotation.z);
		
		cosX = cosf(rotation.x);	
		cosY = cosf(rotation.y);	
		cosZ = cosf(rotation.z);
		
		out.m1.x = cosZ*cosY + sinZ*sinX*sinY;
		out.m1.y = sinZ*cosX;
		out.m1.z = cosZ*-sinY + sinZ*sinX*cosY;
		out.m1.w = 0;

		out.m2.x = -sinZ*cosY + cosZ*sinX*sinY;
		out.m2.y = cosZ*cosX; 
		out.m2.z = sinZ*sinY + cosZ*sinX*cosY;
		out.m2.w = 0;

		out.m3.x = cosX*sinY; 
		out.m3.y = -sinX;
		out.m3.z = cosX*cosY; 
		out.m3.w = 0;

		out.m4.x = 0;
		out.m4.y = 0;
		out.m4.z = 0;
		out.m4.w = 1.0f;
	}

	inline void Mat4MakeRotationMatrixZXY(Matrix4& out, const Vector3 rotation, const Vector3& position){
		float	sinX, sinY, sinZ, cosX, cosY, cosZ;

		sinX = sinf(rotation.x);	
		sinY = sinf(rotation.y); 
		sinZ = sinf(rotation.z);
		
		cosX = cosf(rotation.x);	
		cosY = cosf(rotation.y);	
		cosZ = cosf(rotation.z);
		
		out.m1.x = cosZ*cosY + sinZ*sinX*sinY;
		out.m1.y = sinZ*cosX;
		out.m1.z = cosZ*-sinY + sinZ*sinX*cosY;
		out.m1.w = 0;

		out.m2.x = -sinZ*cosY + cosZ*sinX*sinY;
		out.m2.y = cosZ*cosX; 
		out.m2.z = sinZ*sinY + cosZ*sinX*cosY;
		out.m2.w = 0;

		out.m3.x = cosX*sinY; 
		out.m3.y = -sinX;
		out.m3.z = cosX*cosY; 
		out.m3.w = 0;

		out.m4.x = position.x;
		out.m4.y = position.y;
		out.m4.z = position.z;
		out.m4.w = 1.0f;
	}

	inline void Mat4MakeRotationMatrixX(Matrix4& out, float xRotation){
		float cos = cosf(xRotation);
		float sin = sinf(xRotation);
		
		out.m1.x = 1.0f;
		out.m1.y = 0;
		out.m1.z = 0;
		out.m1.w = 0;

		out.m2.x = 0;
		out.m2.y = cos;
		out.m2.z = sin;
		out.m2.w = 0;

		out.m3.x = 0;
		out.m3.y = -sin;
		out.m3.z = cos;
		out.m3.w = 0;

		out.m4.x = 0;
		out.m4.y = 0;
		out.m4.z = 0;
		out.m4.w = 1.0f;
	}


	inline void Mat4MakeRotationMatrixY(Matrix4& out, float yRotation){
		float cos = cosf(yRotation);
		float sin = sinf(yRotation);
		
		out.m1.x = cos;
		out.m1.y = 0;
		out.m1.z = -sin;
		out.m1.w = 0;

		out.m2.x = 0;
		out.m2.y = 1.0f;
		out.m2.z = 0;
		out.m2.w = 0;

		out.m3.x = sin;
		out.m3.y = 0;
		out.m3.z = cos;
		out.m3.w = 0;

		out.m4.x = 0;
		out.m4.y = 0;
		out.m4.z = 0;
		out.m4.w = 1.0f;
	}

	inline void Mat4MakeRotationMatrixZ(Matrix4& out, float zRotation){
		float cos = cosf(zRotation);
		float sin = sinf(zRotation);
		
		out.m1.x = cos;
		out.m1.y = sin;
		out.m1.z = 0;
		out.m1.w = 0;

		out.m2.x = -sin;
		out.m2.y = cos;
		out.m2.z = 0;
		out.m2.w = 0;

		out.m3.x = 0;
		out.m3.y = 0;
		out.m3.z = 1.0f;
		out.m3.w = 0;

		out.m4.x = 0;
		out.m4.y = 0;
		out.m4.z = 0;
		out.m4.w = 1.0f;
	}

	inline void Mat4MakeTranslateMatrix(Matrix4& out, float x, float y, float z){
		out.m1.x = 1.0f;
		out.m1.y = 0;
		out.m1.z = 0;
		out.m1.w = 0;

		out.m2.x = 0;
		out.m2.y = 1.0f;
		out.m2.z = 0;
		out.m2.w = 0;

		out.m3.x = 0;
		out.m3.y = 0;
		out.m3.z = 1.0f;
		out.m3.w = 0;

		out.m4.x = x;
		out.m4.y = y;
		out.m4.z = z;
		out.m4.w = 1.0f;
	}

	inline void Mat4MakeTranslateMatrix(Matrix4& out, const Vector3& position){
		out.m1.x = 1.0f;
		out.m1.y = 0;
		out.m1.z = 0;
		out.m1.w = 0;

		out.m2.x = 0;
		out.m2.y = 1.0f;
		out.m2.z = 0;
		out.m2.w = 0;

		out.m3.x = 0;
		out.m3.y = 0;
		out.m3.z = 1.0f;
		out.m3.w = 0;

		out.m4.x = position.x;
		out.m4.y = position.y;
		out.m4.z = position.z;
		out.m4.w = 1.0f;
	}

	inline void Mat4MakeWorldTransMatrixZXY(Matrix4& out, const Vector3& scale, const Vector3& rotation, const Vector3& position){
		float	sinX, sinY, sinZ, cosX, cosY, cosZ;
		
		sinX = sinf(rotation.x);	
		sinY = sinf(rotation.y); 
		sinZ = sinf(rotation.z);
		
		cosX = cosf(rotation.x);	
		cosY = cosf(rotation.y);	
		cosZ = cosf(rotation.z);

		out.m1.x = scale.x * (cosZ*cosY + sinZ*sinX*sinY);
		out.m1.y = scale.x * (sinZ*cosX);
		out.m1.z = scale.x * (cosZ*-sinY + sinZ*sinX*cosY);
		out.m1.w = 0;
			
		out.m2.x = scale.y * (-sinZ*cosY + cosZ*sinX*sinY);
		out.m2.y = scale.y * (cosZ*cosX); 
		out.m2.z = scale.y * (sinZ*sinY + cosZ*sinX*cosY);
		out.m2.w = 0;
				 
		out.m3.x = scale.z * (cosX*sinY); 
		out.m3.y = scale.z * -sinX;
		out.m3.z = scale.z * (cosX*cosY); 
		out.m3.w = 0;
				 
		out.m4.x = position.x;
		out.m4.y = position.y;
		out.m4.z = position.z;
		out.m4.w = 1.0f;
	}

	inline void Mat4MakeWorldTransMatrixZXY(Matrix4& out, float scale, float angle, const Vector3& position){
		float sinY = sinf(angle);
		float cosY = cosf(angle);

		out.m1.x = scale * cosY;
		out.m1.y = 0;
		out.m1.z = scale * -sinY;
		out.m1.w = 0;
			
		out.m2.x = 0;
		out.m2.y = scale; 
		out.m2.z = 0;
		out.m2.w = 0;
				 
		out.m3.x = scale * sinY; 
		out.m3.y = 0;
		out.m3.z = scale * cosY; 
		out.m3.w = 0;
				 
		out.m4.x = position.x;
		out.m4.y = position.y;
		out.m4.z = position.z;
		out.m4.w = 1.0f;
	}
	

	inline void Mat4InvertOrthogonalMatrix(Matrix4& out, const Matrix4& in){
		Matrix4 m;

		m.m1.x = in.m1.x;
		m.m1.y = in.m2.x;
		m.m1.z = in.m3.x;
		m.m1.w = 0;
		
		m.m2.x = in.m1.y;
		m.m2.y = in.m2.y;
		m.m2.z = in.m3.y;
		m.m2.w = 0;
		
		m.m3.x = in.m1.z;
		m.m3.y = in.m2.z;
		m.m3.z = in.m3.z;
		m.m3.w = 0;
		
		m.m4.x = -(in.m4.x*in.m1.x + in.m4.y*in.m1.y + in.m4.z*in.m1.z);
		m.m4.y = -(in.m4.x*in.m2.x + in.m4.y*in.m2.y + in.m4.z*in.m2.z);
		m.m4.z = -(in.m4.x*in.m3.x + in.m4.y*in.m3.y + in.m4.z*in.m3.z);
		m.m4.w = 1.0f;


		out.m1.x = m.m1.x;
		out.m1.y = m.m1.y;
		out.m1.z = m.m1.z;
		out.m1.w = m.m1.w;
				   
		out.m2.x = m.m2.x;
		out.m2.y = m.m2.y;
		out.m2.z = m.m2.z;
		out.m2.w = m.m2.w;
				   
		out.m3.x = m.m3.x;
		out.m3.y = m.m3.y;
		out.m3.z = m.m3.z;
		out.m3.w = m.m3.w;
				   
		out.m4.x = m.m4.x;
		out.m4.y = m.m4.y;
		out.m4.z = m.m4.z;
		out.m4.w = m.m4.w;
	}
	
	inline void Mat4TransposeMatrix(Matrix4& out, const Matrix4& in){
		Matrix4 m;

		m.m1.x = in.m1.x;
		m.m1.y = in.m2.x;
		m.m1.z = in.m3.x;
		m.m1.w = in.m4.x;
		
		m.m2.x = in.m1.y;
		m.m2.y = in.m2.y;
		m.m2.z = in.m3.y;
		m.m2.w = in.m4.y;
		
		m.m3.x = in.m1.z;
		m.m3.y = in.m2.z;
		m.m3.z = in.m3.z;
		m.m3.w = in.m4.z;
		
		m.m4.x = in.m1.w;
		m.m4.y = in.m2.w;
		m.m4.z = in.m3.w;
		m.m4.w = in.m4.w;

		out.m1.x = m.m1.x;
		out.m1.y = m.m1.y;
		out.m1.z = m.m1.z;
		out.m1.w = m.m1.w;

		out.m2.x = m.m2.x;
		out.m2.y = m.m2.y;
		out.m2.z = m.m2.z;
		out.m2.w = m.m2.w;

		out.m3.x = m.m3.x;
		out.m3.y = m.m3.y;
		out.m3.z = m.m3.z;
		out.m3.w = m.m3.w;

		out.m4.x = m.m4.x;
		out.m4.y = m.m4.y;
		out.m4.z = m.m4.z;
		out.m4.w = m.m4.w;
	}

	inline void Mat4TransformTo2D(Vector2& screenPos, const Vector3& worldPos, Matrix4 view, Matrix4 projection, unsigned int windowWidth, unsigned int windowHeight)
	{
		Vector3 p;
		float w = 1.0f;

		Matrix4	mat = view * projection;

		p.x = worldPos.x * mat.m1.x + worldPos.y * mat.m2.x + worldPos.z * mat.m3.x + mat.m4.x;
		p.y = worldPos.x * mat.m1.y + worldPos.y * mat.m2.y + worldPos.z * mat.m3.y + mat.m4.y;
		p.z = worldPos.x * mat.m1.z + worldPos.y * mat.m2.z + worldPos.z * mat.m3.z + mat.m4.z;
		w   = worldPos.x * mat.m1.w + worldPos.y * mat.m2.w + worldPos.z * mat.m3.w + mat.m4.w;

		p.x = p.x / w;
		p.y = p.y / w;

		p.x = p.x * 0.5f + 0.5f;
		p.y = -p.y;
		p.y = p.y * 0.5f + 0.5f;


		screenPos.x = p.x * windowWidth;
		screenPos.y = p.y * windowHeight;
	}


} //namespace Kmath

#endif