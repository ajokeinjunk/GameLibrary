#pragma once

#include <math.h>
#include <float.h>
#include <Windows.h>
#include "KJ_MathDefines.h"
//========--------========--------========--------========--------========
//
//			数学ライブラリ
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
	//		Vector2クラス
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

		//コンストラクタ
		inline Vector2() :x(0), y(0){}
		inline Vector2(const Vector2& v);
		inline Vector2(float x, float y);
		//explicitはクラス初期化時に指定したクラスや構造体を明示させるようにする。

		//オペレーター
		//代入
		inline Vector2& operator =(const Vector2& v);
		inline Vector2& operator +=(const Vector2& v);
		inline Vector2& operator -=(const Vector2& v);
		inline Vector2& operator *=(float s);
		inline Vector2& operator /=(float s);

		//単項
		inline float& operator [](BYTE i);
		inline float operator [](BYTE i)const;

		//2項
		inline const Vector2 operator +(const Vector2& v)const;
		inline const Vector2 operator -(const Vector2& v)const;
		inline const Vector2 operator *(float s)const;
		inline const Vector2 operator /(float s)const;

		////関数
		inline void Normalize();
		inline void Normalize(Vector2& out);
		inline float Length();
	};

	//Vector2関数
	inline float Vec2Dot(const Vector2& v1, const Vector2& v2);


	//----------------------------------------------------------------------------------------------------------------------------
	//		Vector3クラス
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

		//コンストラクタ
		inline Vector3():x(0),y(0),z(0){}
		inline Vector3(const Vector3& v);
		inline Vector3(float x, float y, float z);
		//explicitはクラス初期化時に指定したクラスや構造体を明示させるようにする。

		//オペレーター
		//代入
		inline Vector3& operator =(const Vector3& v);
		inline Vector3& operator +=(const Vector3& v);
		inline Vector3& operator -=(const Vector3& v);
		inline Vector3& operator *=(float s);
		inline Vector3& operator /=(float s);

		//単項
		inline float& operator [](BYTE i);
		inline float  operator [](BYTE i)const;

		//2項
		inline const Vector3 operator +(const Vector3& v)const;
		inline const Vector3 operator -(const Vector3& v)const;
		inline const Vector3 operator *(float s)const;
		inline const Vector3 operator /(float s)const;

		//関数
		inline void Normalize();
		inline void Normalize(Vector3& out);
		inline float Length();
	};

	//Vector3関数
	inline float Vec3Dot(const Vector3& v1, const Vector3& v2);
	inline void Vec3Cross(Vector3& out, const Vector3& v1, const Vector3& v2);

	inline void Vec3XRotationVector(const Vector3& out, float radPitch);
	inline void Vec3YRotationVector(const Vector3& out, float radYaw);
	inline void Vec3ZRotationVector(const Vector3& out, float radRoll);

	//----------------------------------------------------------------------------------------------------------------------------
	//		Vector4クラス
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

		//コンストラクタ
		inline Vector4():x(0),y(0),z(0),w(0){}
		inline Vector4(float x, float y, float z, float w);
		inline Vector4(const Vector4& v);

		//オペレーター
		//代入
		inline Vector4& operator =(const Vector4& v);
		//inline Vector4& operator =(const Vector3& v);
		inline Vector4& operator +=(const Vector4& v);
		inline Vector4& operator -=(const Vector4& v);
		inline Vector4& operator *=(float s);
		inline Vector4& operator /=(float s);

		//単項
		inline float& operator[](BYTE i);
		inline float operator[](BYTE i)const;

		//2項
		inline const Vector4 operator +(const Vector4& v)const;
		inline const Vector4 operator -(const Vector4& v)const;
		inline const Vector4 operator *(float s)const;
		inline const Vector4 operator /(float s)const;

		////関数
		//void Normalize();
		//void Normalize(Vector4& out);
		//float Length();
	};

	//----------------------------------------------------------------------------------------------------------------------------
	//		Point2Lクラス
	//----------------------------------------------------------------------------------------------------------------------------
	class Point2L{
	public:
		long x, y;

		//コンストラクタ
		inline Point2L() :x(0), y(0){}
		inline Point2L(long x, long y);
		inline Point2L(const Point2L& point);
		inline Point2L(const POINT& point);

		//オペレーター
		//代入
		inline Point2L& operator =(const Point2L& p);
		inline Point2L& operator +=(const Point2L& p);
		inline Point2L& operator -=(const Point2L& p);


		//単項
		inline long& operator [](BYTE i);
		inline long operator [](BYTE i)const;

		//2項
		inline const Point2L operator +(const Point2L& p)const;
		inline const Point2L operator -(const Point2L& p)const;
	};

	//----------------------------------------------------------------------------------------------------------------------------
	//		Point3Fクラス
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

		//コンストラクタ
		inline Point3() :x(0), y(0), z(0){}
		inline Point3(const Point3& p);
		inline Point3(float x, float y, float z);

		//オペレーター
		//代入
		inline Point3& operator =(const Point3& v);
		inline Point3& operator +=(const Vector3& v);
		inline Point3& operator -=(const Vector3& v);

		//単項
		inline float& operator [](BYTE i);
		inline float operator [](BYTE i)const;

		//2項
		inline const Point3  operator +(const Vector3& v)const;
		inline const Point3  operator -(const Vector3& v)const;
		inline const Vector3 operator -(const Point3& p)const;
	};

	//----------------------------------------------------------------------------------------------------------------------------
	//		Point4Fクラス
	//----------------------------------------------------------------------------------------------------------------------------


	//----------------------------------------------------------------------------------------------------------------------------
	//		Quaternionクラス
	//----------------------------------------------------------------------------------------------------------------------------
	class Quaternion{
	public:
		float x;
		float y;
		float z;
		float w;

		//コンストラクタ
		inline Quaternion():x(0),y(0),z(0),w(0){}
		inline Quaternion(const Quaternion& q);
		inline Quaternion(float x, float y, float z, float w);
		inline Quaternion(const Matrix3& rotMat);

		//オペレーター
		//代入
		inline Quaternion& operator =(const Quaternion& q);
		inline Quaternion& operator +=(const Quaternion& q);
		inline Quaternion& operator -=(const Quaternion& q);
		inline Quaternion& operator *=(const Quaternion& q);
		inline Quaternion& operator /=(const Quaternion& q);

		//単項
		inline float& operator[](BYTE i);
		inline float operator[](BYTE i)const;

		//2項
		inline const Quaternion operator +(const Quaternion& q)const;
		inline const Quaternion operator -(const Quaternion& q)const;
		inline const Quaternion operator *(const Quaternion& q)const;

		//関数
		inline void Identity(){ x = y = z = 0.0f; w = 1.0f; }
	};

	//Quaternion関数
	inline void QuaternionSlerp(Quaternion& out, const Quaternion& origin, const Quaternion& destination, float ratio);
	inline float QuaternionDot(const Quaternion& q1, const Quaternion& q2);

	/** ===================================================================================
	* @class Matrix3
	* @brief Vector4とfloat[4][4]とfloat[16]からなる4×4行列。
	==================================================================================== */
	class Matrix3{
	public:
		union {
			struct{
				Vector3 m1;
				Vector3 m2;
				Vector3 m3;
			};
			float m[3][3];
			float _m[9];
		};
		//コンストラクタ
		inline Matrix3();
		inline Matrix3(const Matrix3& m);
		inline Matrix3(const Vector3 v1, const Vector3& v2, const Vector3& v3);
		//Matrix3(const float* m);
		
		

		//オペレーター
		//代入
		inline Matrix3& operator = (const Matrix3& m);
		inline Matrix3& operator +=(const Matrix3& m);
		inline Matrix3& operator -=(const Matrix3& m);
		inline Matrix3& operator *=(const Matrix3& m);
		//inline Matrix3& operator /=(const Matrix3& m);

		//単項
		//inline Vector3& operator[](BYTE i);
		//inline Vector3 operator[](BYTE i)const;
		//inline float operator[](BYTE i)const;


		//2項
		inline const Matrix3 operator +(const Matrix3& m)const;
		inline const Matrix3 operator -(const Matrix3& m)const;
		inline const Matrix3 operator *(const Matrix3& m)const;
		//inline const Matrix3 operator /(const Matrix3& m)const;
		
		//Matrix3関数
		inline void Identify();
	};

	/** ===================================================================================
	* @class Matrix4
	* @brief Vector4とfloat[4][4]とfloat[16]からなる4×4行列。
	==================================================================================== */
	class Matrix4{
		public:
			union {
				struct {
					Vector4 m1;
					Vector4 m2;
					Vector4 m3;
					Vector4 m4;
				};
				float m[4][4];
				float _m[16];
			};


		//コンストラクタ
		inline Matrix4();
		inline Matrix4(const Matrix4& m);
		inline Matrix4(const Vector4 v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);
		//Matrix4(const float* m);
		

		//オペレーター
		//代入
		inline Matrix4& operator = (const Matrix4& mat);
		inline Matrix4& operator +=(const Matrix4& mat);
		inline Matrix4& operator -=(const Matrix4& mat);
		inline Matrix4& operator *=(const Matrix4& mat);
		//inline Matrix4& operator /=(const Matrix4& m);

		//単項
		inline Vector4& operator[](unsigned char i);
		inline Vector4  operator[](unsigned char i)const;
		inline float    operator[](char i)const;

		//2項
		inline const Matrix4 operator +(const Matrix4& mat)const;
		inline const Matrix4 operator -(const Matrix4& mat)const;
		inline const Matrix4 operator *(const Matrix4& mat)const;
		//inline const Matrix4 operator /(const Matrix4& m)const;

		//Matrix4関数
		inline void Identify();
		inline void Inverse();
		inline void Inverse(Matrix4& out);

		//セッター
		inline void SetPosition(const Vector3& position);
		inline void SetScale(const Vector3& scale);

		//ゲッター
		inline void GetPosition(Vector3& position);
		inline void GetScale(Vector3& scale);

		inline void GetRightDirection(Vector3& right);
		inline void GetUpDirection(Vector3& up);
		inline void GetForwardDirection(Vector3& forward);

	};

	//Matrix4関数
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
	inline void Mat4TransformTo2D(Vector2& screenPos, const Vector3& worldPos, Matrix4 view, Matrix4 projection, unsigned int windowWidth, unsigned int windowHeight);

	/** ===================================================================================
	* @class AABBMinMax
	* @brief 最大値と最小値によるAABBクラス。
	==================================================================================== */
	struct AABBMinMax{

		Vector3 maxPoint;
		Vector3 minPoint;

		AABBMinMax() :maxPoint(-FLT_MAX, -FLT_MAX, -FLT_MAX), minPoint(FLT_MAX, FLT_MAX, FLT_MAX){
		}

		~AABBMinMax(){}

		//bool MakeAABB(const LPD3DXMESH& mesh);
		static bool Collide(const AABBMinMax& p1, const AABBMinMax& p2);
		void DrawBox(DWORD color, bool ZEnable);
	};

	/** ===================================================================================
	* @class AABBCenterHalf
	* @brief 中心と大きさの半分によるAABBクラス。
	==================================================================================== */
	struct AABBCenterHalf{

		Vector3 center;
		Vector3 half;

		AABBCenterHalf() :center(0, 0, 0), half(-FLT_MAX, -FLT_MAX, -FLT_MAX){
		}

		~AABBCenterHalf(){}

		//bool MakeAABB(const LPD3DXMESH& mesh);
		bool MakeAABB(const Vector3& center, const Vector3& half);  //centerはAABBの中心点、そこからの長さがhalf。よってhalfに0以下の数値を入れてはならない。
		void Update(const Matrix4& worldTransMatrix);
		void UpdatePos(const Vector3& pos);
		void UpdateScale(float scale);
		void UpdateScale(const Vector3& scale);


		static bool Collide(const AABBCenterHalf& p1, const AABBCenterHalf& p2);
		void DrawBox(DWORD color, bool ZEnable);
	};

	/** ===================================================================================
	* @class Plane
	* @brief 無限平面を表すクラス。
	* デバッグ描画も可能。
	==================================================================================== */
	class Plane{
	public:
		float m_p[4];

	};

	/** ===================================================================================
	* @class Frustum
	* @brief 視錘台を表すクラス。
	* デバッグ描画も可能。
	==================================================================================== */
	class Frustum{
	public:
		enum SideType{Near, Far, Top, Bottom, Left, Num_Planes};

		Plane   m_Planes[Num_Planes];
		Vector3 m_NearClip[4];
		Vector3 m_FarClip[4];

		float   m_FiledOfView;
		float   m_Aspect;
		float   m_Near;
		float   m_Far;

	public:
		Frustum();

		bool IsInside() const;
		bool IsInside(const Vector3 &point, const float radius) const;

		void DebugRender();
	};

} //namespace



#include "KJ_Matrix.h"
#include "KJ_Quaternion.h"
#include "KJ_Vector.h"
#include "KJ_Point.h"

