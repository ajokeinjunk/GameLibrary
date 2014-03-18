#ifndef H_K_VECTOR_H
#define H_K_VECTOR_H

namespace Klibrary{

//----------------------------------------------------------------------------------------------------------------------------
//		Vector2クラス
//----------------------------------------------------------------------------------------------------------------------------
	//コンストラクタ
	inline Vector2::Vector2(const Vector2& v){
		x = v.x;
		y = v.y;
	}

	inline Vector2::Vector2(float x, float y){
		this->x = x;
		this->y = y;
	}

	//オペレーター
	//代入
	inline Vector2& Vector2::operator =(const Vector2& v){
		x = v.x;
		y = v.y;
		return *this;
	}

	inline Vector2& Vector2::operator +=(const Vector2& v){
		x += v.x;
		y += v.y;
		return *this;
	}

	inline Vector2& Vector2::operator -=(const Vector2& v){
		x -= v.x;
		y -= v.y;
		return *this;
	}


	inline Vector2& Vector2::operator *=(float s){
		x *= s;
		y *= s;

		return *this;
	}

	inline Vector2& Vector2::operator /=(float s){
#ifdef _DEBUG
		assert(s != 0);
#endif

		x /= s;
		y /= s;
		return *this;
	}

	//単項
	inline float& Vector2::operator[](BYTE i){
		return *(&x + i);
	}

	inline float Vector2::operator[](BYTE i) const {
		return *(&x + i);
	}

	//2項
	inline const Vector2 Vector2::operator +(const Vector2& v)const{
		return Vector2(x + v.x, y + v.y);
	}

	inline const Vector2 Vector2::operator -(const Vector2& v)const{
		return Vector2(x - v.x, y - v.y);
	}

	inline const Vector2 Vector2::operator *(float s)const{
		return Vector2(x * s, y * s);
	}

	inline const Vector2 Vector2::operator /(float s)const{
		return Vector2(x / s, y / s);
	}

	//Vector2関数
	inline void Vector2::Normalize(){
		float s = sqrtf(x*x + y*y);
		x /= s;
		y /= s;
	}

	inline void Vector2::Normalize(Vector2& out){
		float invLen = (1.0f / sqrtf(x*x + y*y));
		out.x = x * invLen;
		out.y = y * invLen;
	}

	inline float Vector2::Length(){
		return sqrtf(x*x + y*y);
	}

	inline float Vec2Dot(const Vector2& v1, const Vector2& v2){
		return v1.x*v2.x + v1.y*v2.y;
	}


//----------------------------------------------------------------------------------------------------------------------------
//		Vector3クラス
//----------------------------------------------------------------------------------------------------------------------------


	//コンストラクタ
	inline Vector3::Vector3(const Vector3& v){
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline Vector3::Vector3(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//オペレーター
	//代入
	inline Vector3& Vector3::operator =(const Vector3& v){
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	
	inline Vector3& Vector3::operator +=(const Vector3& v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	
	inline Vector3& Vector3::operator -=(const Vector3& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	

	inline Vector3& Vector3::operator *=(float s){
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	
	inline Vector3& Vector3::operator /=(float s){
#ifdef _DEBUG
		assert(s != 0);
#endif

		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	//単項
	inline float& Vector3::operator[](BYTE i){
		return *(&x+i);
	}

	inline float Vector3::operator[](BYTE i) const {
		return *(&x+i);
	}

	//2項
	inline const Vector3 Vector3::operator +(const Vector3& v)const{
		return Vector3(x+v.x, y+v.y, z+v.z);
	}
	
	inline const Vector3 Vector3::operator -(const Vector3& v)const{
		return Vector3(x-v.x, y-v.y, z-v.z);
	}

	inline const Vector3 Vector3::operator *(float s)const{
		return Vector3(x*s, y*s, z*s);
	}

	inline const Vector3 Vector3::operator /(float s)const{
		return Vector3(x/s, y/s, z/s);
	}

	//Vector3関数
	inline void Vector3::Normalize(){
		float s = sqrtf(x*x + y*y + z*z);
		if (s != 0.0f){
			x /= s;
			y /= s;
			z /= s;
		}
	}

	inline void Vector3::Normalize(Vector3& out){
		float invLen = (1.0f / sqrtf(x*x + y*y + z*z));
		out.x = x*invLen;
		out.y = y*invLen;
		out.z = z*invLen;
	}

	inline float Vector3::Length(){
		return sqrtf(x*x + y*y + z*z);
	}

	inline float Vec3Dot(const Vector3& v1, const Vector3& v2){
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

	inline void Vec3Cross(Vector3& out, const Vector3& v1, const Vector3& v2){
		out.x = v1.y * v2.z - v1.z * v2.y;
		out.y = v1.z * v2.x - v1.x * v2.z;
		out.z = v1.x * v2.y - v1.y * v2.x;
	}

//----------------------------------------------------------------------------------------------------------------------------
//		Vector4クラス
//----------------------------------------------------------------------------------------------------------------------------
	//コンストラクタ
	inline Vector4::Vector4(const Vector4& v){
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	inline Vector4::Vector4(float x, float y, float z, float w){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//オペレーター
	//代入
	inline Vector4& Vector4::operator =(const Vector4& v){
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	
	inline Vector4& Vector4::operator +=(const Vector4& v){
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	
	inline Vector4& Vector4::operator -=(const Vector4& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	
	inline Vector4& Vector4::operator *=(float s){
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	
	inline Vector4& Vector4::operator /=(float s){
#ifdef _DEBUG
		assert(s != 0);
#endif

		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}

	//単項
	inline float& Vector4::operator[](BYTE i){
		return *(&x+i);
	}

	inline float Vector4::operator[](BYTE i)const {
		return *(&x+i);
	}

	//2項
	inline const Vector4 Vector4::operator +(const Vector4& v)const{
		return Vector4(x+v.x, y+v.y, z+v.z, w+v.w);
	}
	
	inline const Vector4 Vector4::operator -(const Vector4& v)const{
		return Vector4(x-v.x, y-v.y, z-v.z, w-v.w);
	}

	inline const Vector4 Vector4::operator *(float s)const{
		return Vector4(x*s, y*s, z*s, w*s);
	}

	inline const Vector4 Vector4::operator /(float s)const{
		return Vector4(x/s, y/s, z/s, w/s);
	}

	//Vector4関数
	//void Vector4::Normalize(){
	//	float invLen = (1.0f/sqrtf(x*x + y*y + z*z + w*w));
	//	x *= invLen;
	//	y *= invLen;
	//	z *= invLen;
	//	w *= invLen;
	//}

	//void Vector4::Normalize(Vector4& out){
	//	float invLen = (1.0f/sqrtf(x*x + y*y + z*z + w*w));
	//	out.x *= invLen;
	//	out.y *= invLen;
	//	out.z *= invLen;
	//	out.w *= invLen;
	//}

	//float Vector4::Length(){
	//	return sqrtf(x*x + y*y + z*z + w*w);
	//}


}  //namespace  Kmath

#endif