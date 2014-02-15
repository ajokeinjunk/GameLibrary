#ifndef H_K_QUATERNION_H
#define H_K_QUATERNION_H

#include <assert.h>

namespace Klibrary{
	//コンストラクタ
	inline Quaternion::Quaternion(const Quaternion& q){
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}

	inline Quaternion::Quaternion(float x, float y, float z, float w){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//inline Quaternion::Quaternion(const Matrix3& rotMat){
	//	this->x = x;
	//	this->y = y;
	//	this->z = z;
	//	this->w = 1.0f;
	//}

	//オペレーター
	//代入
	inline Quaternion& Quaternion::operator =(const Quaternion& q){
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
		return *this;
	}

	inline Quaternion& Quaternion::operator +=(const Quaternion& q){
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
		return *this;
	}

	inline Quaternion& Quaternion::operator -=(const Quaternion& q){
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
		return *this;
	}

	inline Quaternion& Quaternion::operator *=(const Quaternion& q){
		*this = *this * q;

		return *this;
	}

	//単項
	inline  float& Quaternion::operator[](BYTE i){
		return *(&x+i);
	}

	inline float Quaternion::operator[](BYTE i)const{
		return *(&x+i);
	}

	//2項
	inline const Quaternion Quaternion::operator +(const Quaternion& q)const{
		return Quaternion(x+q.x, y+q.y, z+q.z, w+q.w);
	}

	inline const Quaternion Quaternion::operator -(const Quaternion& q)const{
		return Quaternion(x-q.x, y-q.y, z-q.z, w-q.w);
	}

	inline const Quaternion Quaternion::operator *(const Quaternion& q)const{
		return Quaternion(x * q.w + z * q.y + w * q.x - y * q.z,
			              x * q.z + y * q.w + w * q.y - z * q.x,
					      y * q.x + z * q.w + w * q.z - x * q.y,
					      w * q.w - x * q.x - y * q.y - z * q.z);

	}



	inline void QuaternionSlerp(Quaternion& out, const Quaternion& origin, const Quaternion& destination, float ratio){

		if (ratio < 0){
			out = origin; 
			return;
		}
		else if(ratio > 1.0f){
			out = destination;
			return;
		}

		float cosTheta = QuaternionDot(origin, destination);
		
		float desX = destination.x;
		float desY = destination.y;
		float desZ = destination.z;
		float desW = destination.w;

		if (cosTheta < 0){
			cosTheta = -cosTheta;
			desX = -desX;
			desY = -desY;
			desZ = -desZ;
			desW = -desW;
		}

#ifdef _DEBUG
		assert(cosTheta < 1.1f);
#endif
		float k0, k1;

		if (cosTheta > 0.9999f){
			//0除算を防ぐため線形補完
			k0 = 1.0f - ratio;
			k1 = ratio;
		}
		else{
			float sinTheta = sqrt(1.0f - cosTheta * cosTheta);
			float omega = atan2(sinTheta, cosTheta);

			//除算の省略のため分母の逆数をはじき出す。
			float inverseSin = 1.0f / sinTheta;

			k0 = sin(1.0f - ratio) * omega * inverseSin;
			k1 = sin(ratio * omega) * inverseSin;
		}

		out.x = origin.x * k0 + desX * k1;
		out.y = origin.y * k0 + desY * k1;
		out.z = origin.z * k0 + desZ * k1;
		out.w = origin.w * k0 + desW * k1;
	}

	inline float QuaternionDot(const Quaternion& q1, const Quaternion& q2){
		return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	}


} //namespace Kmath

#endif