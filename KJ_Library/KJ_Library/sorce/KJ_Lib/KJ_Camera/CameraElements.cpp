#include "CameraElements.h"
#include"../KJ_Defines/KJ_Defines.h"

using namespace Klibrary;
using namespace std;


void AxisCameraElements::Initialize(){
	m_Yaw = 0;
	m_Pitch = 0;
	m_Roll = 0;

	m_Range = 0;
	m_ResistVal = 0;
	
	m_AngularVelocity.x = 0;      m_AngularVelocity.y = 0;      m_AngularVelocity.z = 0;
	m_AngularVelocityLimit.x = 0; m_AngularVelocityLimit.y = 0; m_AngularVelocityLimit.z = 0;
	m_AngularAcc.x = 0;           m_AngularAcc.y = 0;           m_AngularAcc.z = 0;

	//m_rubberString = std::make_shared<RubberString>(10.1f, range, Vector3(1,0,1), Vector3(0,0,0));
	//m_rubberString->GetEnd()->Freeze(true);
}

void AxisCameraElements::Update(){
	//Vector3 tempSpherVec = Vector3(cosf(m_Pitch)*sinf(m_Yaw), -sinf(m_Pitch), cosf(m_Pitch)*cosf(m_Yaw));

	m_Pitch += m_AngularVelocity.x;
	m_Yaw   += m_AngularVelocity.y;
	m_Roll  += m_AngularVelocity.z;


	if (m_Yaw   > K_PI * 2) { m_Yaw  -= K_PI * 2; }
	if (m_Pitch > K_PI * 2){ m_Pitch -= K_PI * 2; }
	if (m_Roll  > K_PI * 2){ m_Roll  -= K_PI * 2; }



	if (m_Pitch > K_PI*0.4f - 0.01f){
		m_Pitch = K_PI*0.4f - 0.01f;
	}
	
	if (m_Pitch < -K_PI*0.4f - 0.01f){
		m_Pitch = -K_PI*0.4f - 0.01f;
	}

	m_SphereVector.x =  cosf(m_Pitch) * sinf(m_Yaw);
	m_SphereVector.y = -sinf(m_Pitch);
	m_SphereVector.z =  cosf(m_Pitch) * cosf(m_Yaw);
	
	m_SphereVector.Normalize();
	m_SphereVector *= m_Range;

	//ひも処理
	//sphereVecは原点からどれだけの距離と位置にあるかを表しているにすぎない。
	//回転時の移動量が欲しいなら別で出さないといけない。

	//sphereVector = sphereVector - tempSpherVec;
	//sphereVector.Normalize();
	//sphereVector *= 3.0f;
	//m_rubberString->GetHead()->AddForce(sphereVector);

	//m_rubberString->SetHead();
	//m_rubberString->SetNaturalLength(10.0f);
	//m_rubberString->Update(SPF);
}

bool AxisCameraElements::AddAccX(bool plus){
	if(plus){
		m_AngularVelocity.x += m_AngularAcc.x;
		if(m_AngularVelocity.x > m_AngularVelocityLimit.x){
			m_AngularVelocity.x = m_AngularVelocityLimit.x;
			return false;
		}
	}else{
		m_AngularVelocity.x -= m_AngularAcc.x;
		if (m_AngularVelocity.x < -m_AngularVelocityLimit.x){
			m_AngularVelocity.x = -m_AngularVelocityLimit.x;
				return false;
			}
	}

	return true;
}

bool AxisCameraElements::AddAccY(bool plus){
	if(plus){
		m_AngularVelocity.y += m_AngularAcc.y;
		if (m_AngularVelocity.y > m_AngularVelocityLimit.y){
			m_AngularVelocity.y = m_AngularVelocityLimit.y;
			return false;
		}
	}else{
		m_AngularVelocity.y -= m_AngularAcc.y;
		if (m_AngularVelocity.y < -m_AngularVelocityLimit.y){
			m_AngularVelocity.y = -m_AngularVelocityLimit.y;
			return false;
		}
	}

	return true;
}

bool AxisCameraElements::AddAccZ(bool plus){
	if(plus){
		m_AngularVelocity.z += m_AngularAcc.z;
		if (m_AngularVelocity.z > m_AngularVelocityLimit.z){
			m_AngularVelocity.z = m_AngularVelocityLimit.z;
			return false;
		}
	}else{
		m_AngularVelocity.z -= m_AngularAcc.z;
		if (m_AngularVelocity.z < -m_AngularVelocityLimit.z){
			m_AngularVelocity.z = -m_AngularVelocityLimit.z;
			return false;
		}
	}
	return false;
}

void AxisCameraElements::AddAcc(const Vector3& acc){
	m_AngularVelocity.x += acc.x;
	//if (angularVelocity.x > angularVelocityLimit.x){
	//	angularVelocity.x = angularVelocityLimit.x;
	//}
	//else if (angularVelocity.x < -angularVelocityLimit.x){
	//	angularVelocity.x = -angularVelocityLimit.x;
	//}

	m_AngularVelocity.y += acc.y;
	//if (angularVelocity.y > angularVelocityLimit.y){
	//	angularVelocity.y = angularVelocityLimit.y;
	//}
	//else if (angularVelocity.y < -angularVelocityLimit.y){
	//	angularVelocity.y = -angularVelocityLimit.y;
	//}
	
	m_AngularVelocity.z += acc.z;
	//if (angularVelocity.z > angularVelocityLimit.z){
	//	angularVelocity.z = angularVelocityLimit.z;
	//}
	//else if (angularVelocity.z < -angularVelocityLimit.z){
	//	angularVelocity.z = -angularVelocityLimit.z;
	//}
}

void AxisCameraElements::SetVel(const Vector3& vel){
	m_AngularVelocity.x = vel.x;
	m_AngularVelocity.y = vel.y;
	m_AngularVelocity.z = vel.z;
}


void AxisCameraElements::Resist(bool x, bool y, bool z){
	if(x){
		m_AngularVelocity.x *= m_ResistVal;
	}

	if(y){
		m_AngularVelocity.y *= m_ResistVal;
	}
	
	if(z){
		m_AngularVelocity.z *= m_ResistVal;
	}
}




