#ifndef H_K_DIRECTX3D_H
#define H_K_DIRECTX3D_H

#pragma warning(disable:4005)

#include <D3D11.h>
#include <d3dx10.h>
#include <D3DX11.h>
#include <d3dCompiler.h>
#include "../../KJ_Math/KJ_Math.h"
#include "../../KJ_System/KJ_System.h"
#include "../../KJ_Windows/KJ_WindowSystem.h"
#include "../KJ_Renderer.h"
#include "../../KJ_Mesh/MeshProperty.h"
#include <memory>

#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")


namespace Klibrary{


	enum BufferType{
		VERTEX_BUFFER = 0,
	};


	//シェーダーに渡すデータ
	//シェーダーとmain側両方で共通のバッファー
	//データ変更はmainのみ
	
	//コンスタントバッファの仕様
	//データ数が4byteの倍数でしか送れない。
	struct AlwaysChangeCB{
		Matrix4 WVP; //ワールド、ビュー、プロジェクション
		ColorF LightColor;
		Vector4 directionalLight;
		
	};

	struct NeverChangeCB{

	};

	struct SometimeChangeCB{

	};

	//========--------========--------========--------========--------========
	//
	//			DirectX3Dクラス
	//
	//========--------========--------========--------========--------========
	class KdirectX3D : public Krenderer{
	
	private:
		Matrix4 m_worldTransMatrix;
		Matrix4 m_viewMatrix;
		Matrix4 m_projectionMatrix;
		
		IDXGISwapChain* m_pSwapChain;			      //スワップチェーン
		
		ID3D11RenderTargetView* m_pRenderTargetView;  //レンダーターゲットビュー
		ID3D11DepthStencilView* m_pDepthStencilView;  //デプスステンシルビュー
	
		ID3D11Texture2D* m_pDepthStencilTex;		  //深度ステンシルテクスチャ
		ID3D11RasterizerState* m_pRasterizerState;    //ラスタライザーステイト
		ID3D11InputLayout* m_pInputLayout;			  //シェーダー入力時レイアウト(セマンティクスとか)
	
		ID3D11VertexShader* m_pVertexShader;		  //頂点シェーダー
		ID3D11PixelShader*  m_pPixelShader;		      //ピクセルシェーダー

		ID3D11Buffer* m_pConstantBuffer;			  //コンスタントバッファー
		ID3D11Buffer* m_pVertexBuffer;				  //頂点バッファー
		ID3D11Buffer* m_pIndexBuffer;				  //頂点バッファー

		ID3D11SamplerState* m_pSamplerState;

		//関数
		HRESULT InitializeDevice();                  //DirectX初期化
		HRESULT CreateDevicesAndSwapChain(ID3D11Device*& device, ID3D11DeviceContext*& deviceContext, IDXGISwapChain*& swapChain, D3D_FEATURE_LEVEL featureLevel, D3D_DRIVER_TYPE driverType);
		HRESULT CreateRenderTargetView(ID3D11Device* device, IDXGISwapChain* swapChain, ID3D11RenderTargetView*& RenderTargetView);
		HRESULT CreateStencilDepthViewAndTexture(ID3D11Device* device, ID3D11Texture2D*& depthStencilTex, ID3D11DepthStencilView*& depthStencilView, DXGI_FORMAT format);
		
		HRESULT InitializeShader();                   //シェーダー初期化
		HRESULT InitializeDebugPolygon();                  //ポリゴン初期化

		AlwaysChangeCB m_constantBufferData;

	public:
		ID3D11Device* m_pDevice;					  //描画デバイス(主にCreate命令)
		ID3D11DeviceContext* m_pDeviceContext;        //描画命令を生成する

		
		KdirectX3D();
		~KdirectX3D();
	
		HRESULT Initialize();
		void BeginRender();
		void EndRender();

		void RenderIndexed(DWORD numIndex);
		void Render(DWORD numVertex);

		void ClearTargetView();
		void ClearTargetView(float a, float r, float g, float b);
		void ClearTargetView(ColorI color);
		void ClearDepthStencilView();

		void Release();

		inline void SetWorldTransMatrix(const Matrix4& wMat){m_worldTransMatrix = wMat;}
		inline void SetViewMatrix(const Matrix4& viewMat){m_viewMatrix = viewMat;}
		inline void SetProjectionMatrix(const Matrix4& projectionMat){m_projectionMatrix = projectionMat;}
		inline void SetViewport(const D3D11_VIEWPORT& viewport){ m_pDeviceContext->RSSetViewports(1, &viewport); }
		inline void SetViewport(float screenWidth, float screenHeight);
		inline void SetDirectionalLight(const ColorF& color, const Vector3& direction);
		void SetBuffer(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer);
		void SetVertexBuffer(ID3D11Buffer* vertexBuffer);
		void SetIndexBuffer(ID3D11Buffer* indexBuffer);

		HRESULT CreateVertexBuffer(ID3D11Buffer*& vertexBuffer, const Vertex3D* vertices, unsigned int numVertices);
		HRESULT CreateIndexBuffer(ID3D11Buffer*& indexBuffer, const WORD* indices, unsigned int numIndices);
	};


	inline void KdirectX3D::SetViewport(float screenWidth, float screenHeight){
		//ビューポート設定、セット
		D3D11_VIEWPORT vp;
		vp.Width = screenWidth;
		vp.Height = screenHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pDeviceContext->RSSetViewports(1, &vp);
	}

	inline void KdirectX3D::SetDirectionalLight(const ColorF& color, const Vector3& direction){
		m_constantBufferData.LightColor = color;
		//lol 光にかけるべき行列はどこまでか調べて置く。
		//　　行列ライブラリ要拡張
		m_constantBufferData.directionalLight.x = direction.x;
		m_constantBufferData.directionalLight.y = direction.y;
		m_constantBufferData.directionalLight.z = direction.z;
		m_constantBufferData.directionalLight.w = 0;
	}

}//namespace

#endif