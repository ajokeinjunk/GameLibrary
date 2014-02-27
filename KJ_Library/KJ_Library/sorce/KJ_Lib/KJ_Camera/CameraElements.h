#ifndef H_KLIB_CAMERA_DATA_H
#define H_KLIB_CAMERA_DATA_H

#include "../KJ_Math/KJ_Math.h"

namespace Klibrary{

	class BaseCamerElements{
	protected:
	public:

		BaseCamerElements(){}
		virtual ~BaseCamerElements(){}

		virtual void Initialize() = 0;
		virtual void Update() = 0;
	};

	//どっちかというとキーボードよりの設定になっている。
	class AxisCameraElements : public BaseCamerElements{
	private:
		float m_Yaw;
		float m_Pitch;
		float m_Roll;

		float m_Range;
		float m_ResistVal;

		Vector3 m_AngularVelocity;
		Vector3 m_AngularVelocityLimit;
		Vector3 m_AngularAcc;
		Vector3 m_AngularLimit;

		Vector3 m_SphereVector;// こいつをバネにしたい。
		//Klibrary::RubberStringPtr m_rubberString;
	public:
		AxisCameraElements() :m_Yaw(0), m_Pitch(0), m_Roll(0), m_Range(0), m_ResistVal(0){
			m_AngularVelocity.x = 0; m_AngularVelocity.y = 0; m_AngularVelocity.z = 0;
			m_AngularVelocityLimit.x = 0; m_AngularVelocityLimit.y = 0; m_AngularVelocityLimit.z = 0;
			m_AngularAcc.x = 0; m_AngularAcc.y = 0;  m_AngularAcc.z = 0;
			m_AngularLimit.x = 0; m_AngularLimit.y = 0; m_AngularLimit.z = 0;
			m_SphereVector.x = 0; m_SphereVector.y = 0; m_SphereVector.z = 0;
		}

		~AxisCameraElements(){}

		void Initialize();
		void Update();

		bool AddAccX(bool plus);
		bool AddAccY(bool plus);
		bool AddAccZ(bool plus);

		void AddAcc(const Vector3& acc);

		void Resist(bool x, bool y, bool z);

		void SetRange(float range){ m_Range = range; }
		void SetResistValue(float resistVal){ m_ResistVal = resistVal; }
		void SetAngularVelocityLimit(const Vector3& limit){ m_AngularVelocityLimit = limit; }
		void SetAngularAcc(const Vector3& acc){ m_AngularAcc = acc; }
		void SetVel(const Vector3& vel);

		float GetRange(){ return m_Range; }
		float GetRoll(){ return m_Roll; }
		float GetYaw(){ return m_Yaw; }
		float GetPitch(){ return m_Pitch; }
		inline const Vector3& GetSphereVector()const{ return m_SphereVector; }
		//const Klibrary::RubberStringPtr GetRubberString()const{ return m_rubberString; }
		void Release();
	};


}


#endif