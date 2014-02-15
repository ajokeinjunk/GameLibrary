//========--------========--------========--------========--------========
//
//			PS
//
//========--------========--------========--------========--------========
//#include  "PSBufferAndMethods.h"
Texture2D texDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer AlwaysChangeCB : register(b0)
{
	matrix g_mWVP; //ワールドから射影までの変換行列
	float4 g_directionalColor;
	float4 g_directionaLight;
	float4 g_Ambient = float4(1, 0.3f, 0.3f, 0.3f);
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 Tex : TEXCOORD;
	float3 Normal : TEXCOORD1;
};


//-------------------------------------
//		ピクセルシェーダー
//-------------------------------------

float4 PS_Base(PS_INPUT input) : SV_Target
{
	float4 lightColor = g_directionalColor;
	lightColor.rgb *= g_directionalColor.a;

	lightColor = saturate(dot((float3)g_directionaLight, input.Normal) * lightColor);

	return lightColor * texDiffuse.Sample(samLinear, input.Tex);
}