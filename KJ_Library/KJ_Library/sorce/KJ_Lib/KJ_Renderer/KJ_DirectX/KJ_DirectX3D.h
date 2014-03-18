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


	//�V�F�[�_�[�ɓn���f�[�^
	//�V�F�[�_�[��main�������ŋ��ʂ̃o�b�t�@�[
	//�f�[�^�ύX��main�̂�
	
	//�R���X�^���g�o�b�t�@�̎d�l
	//�f�[�^����4byte�̔{���ł�������Ȃ��B
	struct AlwaysChangeCB{
		Matrix4 WVP; //���[���h�A�r���[�A�v���W�F�N�V����
		ColorF LightColor;
		Vector4 directionalLight;
		
	};

	struct NeverChangeCB{

	};

	struct SometimeChangeCB{

	};

	//========--------========--------========--------========--------========
	//
	//			DirectX3D�N���X
	//
	//========--------========--------========--------========--------========
	class KdirectX3D : public Krenderer{
	
	private:
		Matrix4 m_worldTransMatrix;
		Matrix4 m_viewMatrix;
		Matrix4 m_projectionMatrix;
		
		IDXGISwapChain* m_pSwapChain;			      //�X���b�v�`�F�[��
		
		ID3D11RenderTargetView* m_pRenderTargetView;  //�����_�[�^�[�Q�b�g�r���[
		ID3D11DepthStencilView* m_pDepthStencilView;  //�f�v�X�X�e���V���r���[
	
		ID3D11Texture2D* m_pDepthStencilTex;		  //�[�x�X�e���V���e�N�X�`��
		ID3D11RasterizerState* m_pRasterizerState;    //���X�^���C�U�[�X�e�C�g
		ID3D11InputLayout* m_pInputLayout;			  //�V�F�[�_�[���͎����C�A�E�g(�Z�}���e�B�N�X�Ƃ�)
	
		ID3D11VertexShader* m_pVertexShader;		  //���_�V�F�[�_�[
		ID3D11PixelShader*  m_pPixelShader;		      //�s�N�Z���V�F�[�_�[

		ID3D11Buffer* m_pConstantBuffer;			  //�R���X�^���g�o�b�t�@�[
		ID3D11Buffer* m_pVertexBuffer;				  //���_�o�b�t�@�[
		ID3D11Buffer* m_pIndexBuffer;				  //���_�o�b�t�@�[

		ID3D11SamplerState* m_pSamplerState;

		//�֐�
		HRESULT InitializeDevice();                  //DirectX������
		HRESULT CreateDevicesAndSwapChain(ID3D11Device*& device, ID3D11DeviceContext*& deviceContext, IDXGISwapChain*& swapChain, D3D_FEATURE_LEVEL featureLevel, D3D_DRIVER_TYPE driverType);
		HRESULT CreateRenderTargetView(ID3D11Device* device, IDXGISwapChain* swapChain, ID3D11RenderTargetView*& RenderTargetView);
		HRESULT CreateStencilDepthViewAndTexture(ID3D11Device* device, ID3D11Texture2D*& depthStencilTex, ID3D11DepthStencilView*& depthStencilView, DXGI_FORMAT format);
		
		HRESULT InitializeShader();                   //�V�F�[�_�[������
		HRESULT InitializeDebugPolygon();                  //�|���S��������

		AlwaysChangeCB m_constantBufferData;

	public:
		ID3D11Device* m_pDevice;					  //�`��f�o�C�X(���Create����)
		ID3D11DeviceContext* m_pDeviceContext;        //�`�施�߂𐶐�����

		
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
		//�r���[�|�[�g�ݒ�A�Z�b�g
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
		//lol ���ɂ�����ׂ��s��͂ǂ��܂ł����ׂĒu���B
		//�@�@�s�񃉃C�u�����v�g��
		m_constantBufferData.directionalLight.x = direction.x;
		m_constantBufferData.directionalLight.y = direction.y;
		m_constantBufferData.directionalLight.z = direction.z;
		m_constantBufferData.directionalLight.w = 0;
	}

}//namespace

#endif