#ifndef H_K_MATH_H
#define H_K_MATH_H

#include <math.h>
#include <Windows.h>
#include "KJ_MathDefines.h"
//========--------========--------========--------========--------========
//
//			���w���C�u����
//
//========--------========--------========--------========--------========

namespace Klibrary{
	struct SVector2;
	class Vector2;
	struct SVector3;
	class Vector3;
	struct SVector4;
	class Vector4;

	class Point2L;
	class Point3;
	
	class Quaternion;
	
	class Matrix3;
	class Matrix4;
	
	//----------------------------------------------------------------------------------------------------------------------------
	//		Vector2�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	struct SVector2{
		float x;
		float y;

		SVector2() :x(0), y(0){}
	};

	class Vector2{
	public:
		float x;
		float y;

		//�R���X�g���N�^
		inline Vector2() :x(0), y(0){}
		inline Vector2(const Vector2& v);
		inline Vector2(float x, float y);
		//explicit�̓N���X���������Ɏw�肵���N���X��\���̂𖾎�������悤�ɂ���B

		//�I�y���[�^�[
		//���
		inline Vector2& operator =(const Vector2& v);
		inline Vector2& operator +=(const Vector2& v);
		inline Vector2& operator -=(const Vector2& v);
		inline Vector2& operator *=(float s);
		inline Vector2& operator /=(float s);

		//�P��
		inline float& operator [](BYTE i);
		inline float operator [](BYTE i)const;

		//2��
		inline const Vector2 operator +(const Vector2& v)const;
		inline const Vector2 operator -(const Vector2& v)const;
		inline const Vector2 operator *(float s)const;
		inline const Vector2 operator /(float s)const;

		////�֐�
		inline void Normalize();
		inline void Normalize(Vector2& out);
		inline float Length();
	};

	//Vector2�֐�
	inline float Vec2Dot(const Vector2& v1, const Vector2& v2);


	//----------------------------------------------------------------------------------------------------------------------------
	//		Vector3�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	struct SVector3{
		float x;
		float y;
		float z;

		SVector3():x(0),y(0),z(0){}
	};
	

	class Vector3{
	public:
		float x;
		float y;
		float z;

		//�R���X�g���N�^
		inline Vector3():x(0),y(0),z(0){}
		inline Vector3(const Vector3& v);
		inline Vector3(float x, float y, float z);
		//explicit�̓N���X���������Ɏw�肵���N���X��\���̂𖾎�������悤�ɂ���B

		//�I�y���[�^�[
		//���
		inline Vector3& operator =(const Vector3& v);
		inline Vector3& operator +=(const Vector3& v);
		inline Vector3& operator -=(const Vector3& v);
		inline Vector3& operator *=(float s);
		inline Vector3& operator /=(float s);

		//�P��
		inline float& operator [](BYTE i);
		inline float operator [](BYTE i)const;

		//2��
		inline const Vector3 operator +(const Vector3& v)const;
		inline const Vector3 operator -(const Vector3& v)const;
		inline const Vector3 operator *(float s)const;
		inline const Vector3 operator /(float s)const;

		//�֐�
		inline void Normalize();
		inline void Normalize(Vector3& out);
		inline float Length();
	};

	//Vector3�֐�
	inline float Vec3Dot(const Vector3& v1, const Vector3& v2);
	inline void Vec3Cross(Vector3& out, const Vector3& v1, const Vector3& v2);

	//----------------------------------------------------------------------------------------------------------------------------
	//		Vector4�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	struct SVector4{
		float x;
		float y;
		float z;
		float w;

		SVector4():x(0),y(0),z(0),w(0){}
	};
	
	class Vector4{
		public:
		float x;
		float y;
		float z;
		float w;

		//�R���X�g���N�^
		inline Vector4():x(0),y(0),z(0),w(0){}
		inline Vector4(float x, float y, float z, float w);
		inline Vector4(const Vector4& v);

		//�I�y���[�^�[
		//���
		inline Vector4& operator =(const Vector4& v);
		//inline Vector4& operator =(const Vector3& v);
		inline Vector4& operator +=(const Vector4& v);
		inline Vector4& operator -=(const Vector4& v);
		inline Vector4& operator *=(float s);
		inline Vector4& operator /=(float s);

		//�P��
		inline float& operator[](BYTE i);
		inline float operator[](BYTE i)const;

		//2��
		inline const Vector4 operator +(const Vector4& v)const;
		inline const Vector4 operator -(const Vector4& v)const;
		inline const Vector4 operator *(float s)const;
		inline const Vector4 operator /(float s)const;

		////�֐�
		//void Normalize();
		//void Normalize(Vector4& out);
		//float Length();
	};

	//----------------------------------------------------------------------------------------------------------------------------
	//		Point2L�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	class Point2L{
	public:
		long x, y;

		//�R���X�g���N�^
		inline Point2L() :x(0), y(0){}
		inline Point2L(long x, long y);
		inline Point2L(const Point2L& point);
		inline Point2L(const POINT& point);

		//�I�y���[�^�[
		//���
		inline Point2L& operator =(const Point2L& p);
		inline Point2L& operator +=(const Point2L& p);
		inline Point2L& operator -=(const Point2L& p);


		//�P��
		inline long& operator [](BYTE i);
		inline long operator [](BYTE i)const;

		//2��
		inline const Point2L operator +(const Point2L& p)const;
		inline const Point2L operator -(const Point2L& p)const;
	};

	//----------------------------------------------------------------------------------------------------------------------------
	//		Point3F�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	struct SPoint3{
		float x;
		float y;
		float z;

		SPoint3() :x(0), y(0), z(0){}
	};

	class Point3{
	public:
		float x;
		float y;
		float z;

		//�R���X�g���N�^
		inline Point3() :x(0), y(0), z(0){}
		inline Point3(const Point3& p);
		inline Point3(float x, float y, float z);

		//�I�y���[�^�[
		//���
		inline Point3& operator =(const Point3& v);
		inline Point3& operator +=(const Vector3& v);
		inline Point3& operator -=(const Vector3& v);

		//�P��
		inline float& operator [](BYTE i);
		inline float operator [](BYTE i)const;

		//2��
		inline const Point3  operator +(const Vector3& v)const;
		inline const Point3  operator -(const Vector3& v)const;
		inline const Vector3 operator -(const Point3& p)const;
	};

	//----------------------------------------------------------------------------------------------------------------------------
	//		Point4F�N���X
	//----------------------------------------------------------------------------------------------------------------------------


	//----------------------------------------------------------------------------------------------------------------------------
	//		Quaternion�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	class Quaternion{
	public:
		float x;
		float y;
		float z;
		float w;

		//�R���X�g���N�^
		inline Quaternion():x(0),y(0),z(0),w(0){}
		inline Quaternion(const Quaternion& q);
		inline Quaternion(float x, float y, float z, float w);
		inline Quaternion(const Matrix3& rotMat);

		//�I�y���[�^�[
		//���
		inline Quaternion& operator =(const Quaternion& q);
		inline Quaternion& operator +=(const Quaternion& q);
		inline Quaternion& operator -=(const Quaternion& q);
		inline Quaternion& operator *=(const Quaternion& q);
		inline Quaternion& operator /=(const Quaternion& q);

		//�P��
		inline float& operator[](BYTE i);
		inline float operator[](BYTE i)const;

		//2��
		inline const Quaternion operator +(const Quaternion& q)const;
		inline const Quaternion operator -(const Quaternion& q)const;
		inline const Quaternion operator *(const Quaternion& q)const;

		//�֐�
		inline void Identity(){ x = y = z = 0.0f; w = 1.0f; }
	};

	//Quaternion�֐�
	inline void QuaternionSlerp(Quaternion& out, const Quaternion& origin, const Quaternion& destination, float ratio);
	inline float QuaternionDot(const Quaternion& q1, const Quaternion& q2);

	//----------------------------------------------------------------------------------------------------------------------------
	//		Matrix3�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	class Matrix3{
	public:
		Vector3 m1;
		Vector3 m2;
		Vector3 m3;

		//�R���X�g���N�^
		inline Matrix3();
		inline Matrix3(const Matrix3& m);
		inline Matrix3(const Vector3 v1, const Vector3& v2, const Vector3& v3);
		//Matrix3(const float* m);
		
		

		//�I�y���[�^�[
		//���
		inline Matrix3& operator = (const Matrix3& m);
		inline Matrix3& operator +=(const Matrix3& m);
		inline Matrix3& operator -=(const Matrix3& m);
		inline Matrix3& operator *=(const Matrix3& m);
		//inline Matrix3& operator /=(const Matrix3& m);

		//�P��
		//inline Vector3& operator[](BYTE i);
		//inline Vector3 operator[](BYTE i)const;
		//inline float operator[](BYTE i)const;


		//2��
		inline const Matrix3 operator +(const Matrix3& m)const;
		inline const Matrix3 operator -(const Matrix3& m)const;
		inline const Matrix3 operator *(const Matrix3& m)const;
		//inline const Matrix3 operator /(const Matrix3& m)const;
		
		//Matrix3�֐�
		inline void Identify();
	};

	//----------------------------------------------------------------------------------------------------------------------------
	//		Matrix4�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	class Matrix4{
		public:
		Vector4 m1;
		Vector4 m2;
		Vector4 m3;
		Vector4 m4;

		//�R���X�g���N�^
		inline Matrix4();
		inline Matrix4(const Matrix4& m);
		inline Matrix4(const Vector4 v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);
		//Matrix4(const float* m);
		

		//�I�y���[�^�[
		//���
		inline Matrix4& operator = (const Matrix4& mat);
		inline Matrix4& operator +=(const Matrix4& mat);
		inline Matrix4& operator -=(const Matrix4& mat);
		inline Matrix4& operator *=(const Matrix4& mat);
		//inline Matrix4& operator /=(const Matrix4& m);

		//�P��
		//inline Vector4& operator[](BYTE i);
		//inline Vector4 operator[](BYTE i)const;
		//inline float    operator[](BYTE i)const;

		//2��
		inline const Matrix4 operator +(const Matrix4& mat)const;
		inline const Matrix4 operator -(const Matrix4& mat)const;
		inline const Matrix4 operator *(const Matrix4& mat)const;
		//inline const Matrix4 operator /(const Matrix4& m)const;

		//Matrix4�֐�
		inline void Identify();
		inline void Inverse();
		inline void Inverse(Matrix4& out);
	};

	//Matrix4�֐�
	inline void Mat4MakeProjectionMatrixLH(Matrix4& out, float fieldOfView, float aspectRatio, float nearClipping, float farClipping);
	inline void Mat4MakeViewMatrixLH(Matrix4& out, const Vector3& position, const Vector3& target, const Vector3& upwardDirection);
	
	inline void Mat4MakeScalingMatrix(Matrix4& out, float scale);
	inline void Mat4MakeScalingMatrix(Matrix4& out, float x, float y, float z);
	inline void Mat4MakeScalingMatrix(Matrix4& out, const Vector3& scale);
	inline void Mat4MakeRotationMatrixZXY(Matrix4& out, const Vector3 rotation);
	inline void Mat4MakeRotationMatrixZXY(Matrix4& out, const Vector3 rotation, const Vector3& position);
	inline void Mat4MakeRotationMatrixX(Matrix4& out, float xRotation);
	inline void Mat4MakeRotationMatrixY(Matrix4& out, float yRotation);
	inline void Mat4MakeRotationMatrixZ(Matrix4& out, float zRotation);
	inline void Mat4MakeTranslateMatrix(Matrix4& out, float x, float y, float z);
	inline void Mat4MakeTranslateMatrix(Matrix4& out, const Vector3& position);
	inline void Mat4MakeWorldTransMatrixZXY(Matrix4& out, const Vector3& scale, const Vector3& rotation, const Vector3& position);
	inline void Mat4MakeWorldTransMatrixZXY(Matrix4& out, float scale, float angle, const Vector3& position);


	inline void Mat4InvertOrthogonalMatrix(Matrix4& out, const Matrix4& in);
	inline void Mat4TransposeMatrix(Matrix4& out, const Matrix4& in);



} //namespace



#include "KJ_Matrix.h"
#include "KJ_Quaternion.h"
#include "KJ_Vector.h"
#include "KJ_Point.h"


#endif