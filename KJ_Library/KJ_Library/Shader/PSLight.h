//========--------========--------========--------========--------========
//
//			Light�N���X
//			
//========--------========--------========--------========--------========
//========--------========--------========--------========--------========
//			���C�g�C���^�[�t�F�C�X
//========--------========--------========--------========--------========
interface IBaseLight
{
	float3 IlluminateAmbient(float3 vNormal);

	float3 IlluminateDiffuse(float3 vNormal);

	float3 IlluminateSpecular(float3 vNormal, int specularPower);

};

//========--------========--------========--------========--------========
//			���C�g�N���X
//========--------========--------========--------========--------========
class AmbientLight : IBaseLight{
	float3   m_vLightColor;
	bool     m_bEnable;

	float3 IlluminateAmbient(float3 vNormal);

	//�g��Ȃ��̂ŋ�
	float3 IlluminateDiffuse(float3 vNormal)
	{
		return (float3)0;
	}

	float3 IlluminateSpecular(float3 vNormal, int specularPower)
	{
		return (float3)0;
	}
};

//========--------========--------========--------========--------========
//			���C�g���\�b�h
//========--------========--------========--------========--------========

float3 AmbientLight::IlluminateAmbient(float3 vNormal){
	return m_vLightColor * m_bEnable;
}
