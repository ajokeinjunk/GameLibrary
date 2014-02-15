//========--------========--------========--------========--------========
//
//			VS
//
//========--------========--------========--------========--------========

//#include "PSLight.h"



//グローバル
cbuffer AlwaysChangeCB : register(b0)
{
	matrix g_mWVP; //ワールドから射影までの変換行列
	float4 g_directionalColor;
	float4 g_directionaLight;
	float4 g_Ambient = float4(1,0.3f,0.3f,0.3f);
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR;   //lolカラー使わんかな～？ 柔軟に頂点レイアウトを変える方法があればいいんだが。
	float3 Normal : NORMAL;
	float2 Tex : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 Tex : TEXCOORD;
	float3 Normal : TEXCOORD1;
};

//-------------------------------------
//		頂点シェーダー
//-------------------------------------
VS_OUTPUT VS_Base(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	input.Normal = mul(input.Normal, g_mWVP);
	output.Normal = normalize(input.Normal);

	
	output.Pos = mul(input.Pos,g_mWVP);
	output.Color = input.Color;
	output.Tex = input.Tex;
	return output;
}

