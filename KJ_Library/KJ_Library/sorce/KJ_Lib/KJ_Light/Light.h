#ifndef H_KLIB_LIGHT_H
#define H_KLIB_LIGHT_H

#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Mesh/MeshProperty.h"
#include "../KJ_Interface/KJ_Interface.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//		   Lightクラス
	//
	//========--------========--------========--------========--------========


	class DirectionalLight : public ILight{
	private:
		ColorF m_color;
		Vector3 m_direction;

	public:
		DirectionalLight() :m_direction(-1, 0, 0){
			m_color.a = m_color.r = m_color.g = m_color.b =  1.0f;
		}

		DirectionalLight(const Vector3& direction){
			m_direction.x = direction.x;
			m_direction.y = direction.y;
			m_direction.z = direction.z;
			m_direction.Normalize();

			m_color.a = m_color.r = m_color.g = m_color.b = 1.0f;
		}

		DirectionalLight(const Vector3& direction, const ColorF& color){
			m_direction.x = direction.x;
			m_direction.y = direction.y;
			m_direction.z = direction.z;
			m_direction.Normalize();

			m_color.a = color.a;
			m_color.r = color.r;
			m_color.g = color.g;
			m_color.b = color.b;
		}

		void VLocate();
		
		//アクセサ
		void SetDirection(const Vector3& dir){ m_direction = dir; }
		void SetColor(ColorF color){ m_color = color; }

		const Vector3& GetDirection()const{ return m_direction; }
		const ColorF GetColor()const{ return m_color; }

	};

	class PointLight : public ILight{
	private:
		ColorF m_color;

	protected:
		Vector3 m_pos;
		float m_range;


	public:

	};

	class SpotLight : public ILight{
	private:

	public:
	};

}

#endif