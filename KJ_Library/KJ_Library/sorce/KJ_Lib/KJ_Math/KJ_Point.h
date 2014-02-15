#ifndef H_KLIB_POINT_H
#define H_KLIB_POINT_H

#include "KJ_Math.h"

namespace Klibrary{
	//----------------------------------------------------------------------------------------------------------------------------
	//		Point2L�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	//�R���X�g���N�^
	inline Point2L::Point2L(long x, long y){ this->x = x; this->y = y; }
	inline Point2L::Point2L(const Point2L& point){ x = point.x; y = point.y; }
	inline Point2L::Point2L(const POINT& point){ x = point.x; y = point.y; }

	//�I�y���[�^�[
	//���
	inline Point2L& Point2L::operator = (const Point2L& p){
		x = p.x;
		y = p.y;
		return *this;
	}

	inline Point2L& Point2L::operator += (const Point2L& p){
		x += p.x;
		y += p.y;
		return *this;
	}

	inline Point2L& Point2L::operator -= (const Point2L& p){
		x -= p.x;
		y -= p.y;
		return *this;
	}


	//�P��
	inline long& Point2L::operator[](BYTE i){
		return *(&x + i);

	}

	inline long Point2L::operator[](BYTE i)const{
		return *(&x + i);
	}

	//2��
	inline const Point2L Point2L::operator + (const Point2L& p)const{
		return Point2L(x + p.x, y + p.y);

	}

	inline const Point2L Point2L::operator - (const Point2L& p)const{
		return Point2L(x + p.x, y + p.y);

	}

	//----------------------------------------------------------------------------------------------------------------------------
	//		Point3F�N���X
	//----------------------------------------------------------------------------------------------------------------------------
	//�R���X�g���N�^
	inline Point3::Point3(const Point3& v){
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline Point3::Point3(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//�I�y���[�^�[
	//���
	inline Point3& Point3::operator =(const Point3& p){
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}

	inline Point3& Point3::operator +=(const Vector3& v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	
	inline Point3& Point3::operator -=(const Vector3& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	//�P��
	inline float& Point3::operator[](BYTE i){
		return *(&x+i);
	}

	inline float Point3::operator[](BYTE i) const {
		return *(&x+i);
	}

	
	//2��
	inline const Point3 Point3::operator +(const Vector3& v)const{
		return Point3(x + v.x, y + v.y, z + v.z);
	}
	
	inline const Point3 Point3::operator -(const Vector3& v)const{
		return Point3(x - v.x, y - v.y, z - v.z);
	}

	inline const Vector3 Point3::operator -(const Point3& p)const{
		return Vector3(x-p.x, y-p.y, z-p.z);
	}

}//namespace

#endif