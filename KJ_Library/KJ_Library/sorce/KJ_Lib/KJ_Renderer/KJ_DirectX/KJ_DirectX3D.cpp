#include "KJ_DirectX3D.h"
#include "../../KJ_Windows/KJ_Window.h"

#pragma warning(disable:4482)

//========--------========--------========--------========--------========
//
//			KdirectX3D�N���X
//
//========--------========--------========--------========--------========

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			1�x������΂�Ȃ�����
	//
	//========--------========--------========--------========--------========
	//--------------------------------------------------------
	//			�R���X�g���N�^
	//--------------------------------------------------------
	KdirectX3D::KdirectX3D(){
		m_pDevice			= nullptr;
		m_pDeviceContext   	= nullptr;
		m_pSwapChain		= nullptr;

		m_pRenderTargetView	= nullptr;
		m_pDepthStencilView	= nullptr;
							
		m_pDepthStencilTex	= nullptr;
		m_pRasterizerState	= nullptr;
		m_pInputLayout		= nullptr;
							
		m_pVertexShader		= nullptr;
		m_pPixelShader   	= nullptr;
							 
		m_pConstantBuffer	= nullptr;
		m_pVertexBuffer		= nullptr;
		m_pIndexBuffer      = nullptr;

		m_pSamplerState     = nullptr;
	}

	//--------------------------------------------------------
	//			�f�X�g���N�^
	//--------------------------------------------------------
	KdirectX3D::~KdirectX3D(){
		Release();
	}


	//--------------------------------------------------------
	//			������
	//--------------------------------------------------------
	HRESULT KdirectX3D::Initialize(){
		m_pDevice			= nullptr;
		m_pDeviceContext   	= nullptr;
		m_pSwapChain		= nullptr;
						
		m_pRenderTargetView	= nullptr;
		m_pDepthStencilView	= nullptr;
						
		m_pDepthStencilTex	= nullptr;
		m_pRasterizerState	= nullptr;
		m_pInputLayout		= nullptr;
		
		m_pVertexShader		= nullptr;
		m_pPixelShader   	= nullptr;
					
		m_pConstantBuffer	= nullptr;
		m_pVertexBuffer		= nullptr;
		m_pIndexBuffer      = nullptr;

		HRESULT result = InitializeDevice();
		return result;
	}


	//--------------------------------------------------------
	//			DirectX������(Device��SwapChain�쐬)
	//--------------------------------------------------------
	HRESULT KdirectX3D::InitializeDevice(){
		HRESULT result = S_OK;

		//�X���b�v�`�F�[���쐬
		result = CreateDevicesAndSwapChain(m_pDevice, m_pDeviceContext, m_pSwapChain, D3D_FEATURE_LEVEL_11_0, D3D_DRIVER_TYPE_HARDWARE);
		if(FAILED(result)){
			MessageBox(0,"�X���b�v�`�F�[���쐬���s�BDirectX�o�[�W�����v�m�F",NULL,MB_OK);
			return result;
		}

		//�����_�[�^�[�Q�b�g�r���[�쐬
		result = CreateRenderTargetView(m_pDevice, m_pSwapChain, m_pRenderTargetView);
		if(FAILED(result)){
			return result;
		}

		//�f�v�X�X�e���V���r���[���e�N�X�`���[�쐬
		result = CreateStencilDepthViewAndTexture(m_pDevice, m_pDepthStencilTex, m_pDepthStencilView, DXGI_FORMAT_D32_FLOAT);
		if(FAILED(result)){
			return result;
		}

		//�p�C�v���C���Ɋ�{�r���[�ݒ�
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);


		//�r���[�|�[�g�ݒ�A�Z�b�g
		D3D11_VIEWPORT vp;
		vp.Width = (float)WindowSystem::windowWidth;
		vp.Height = (float)WindowSystem::windowHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pDeviceContext->RSSetViewports( 1, &vp);

		
		//���X�^���C�Y�ݒ�
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.FrontCounterClockwise = true;
		result = m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState);
		if(FAILED(result)){
			return result;
		}
		m_pDeviceContext->RSSetState(m_pRasterizerState);

		//�V�F�[�_�[������
		result = InitializeShader();
		if(FAILED(result))return result;

		//�|���S��������
		result = InitializeDebugPolygon();
		if(FAILED(result))return result;

		//�`���ʏ�����
		ClearTargetView(1.0f, 0, 0, 1.0f);

		//���[���h�s��ݒ�
		m_worldTransMatrix.Identify();

		//�r���[�s��ݒ�
		Mat4MakeViewMatrixLH(m_viewMatrix,  Vector3(  0.0f, 0.0f, -10.0f ), Vector3( 0.0f, 1.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ));

		//�ˉe�s��ݒ�
		Mat4MakeProjectionMatrixLH(m_projectionMatrix, K_45_DEGREE, WindowSystem::GetScreenAspectRatio(), 0.01f, 100.0f);

		//�v���~�e�B�u�̌`�Ԃ��w��
		m_pDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		return result;
	}

	//--------------------------------------------------------
	//			�V�F�[�_�[������
	//--------------------------------------------------------
	HRESULT KdirectX3D::InitializeShader(){
		//�u���u�쐬
		ID3DBlob *pShader = NULL;
		//ID3DBlob *pError = NULL;  //�G���[���b�Z�[�W�p
		HRESULT result;
		//hlsl�t�@�C������V�F�[�_�[�R���p�C���B

		//�u���u�֒��_�V�F�[�_�[�R���p�C��
		result = D3DX11CompileFromFile("Shader\\VS.hlsl", NULL, NULL,
			"VS_Base", "vs_5_0", 0, 0, NULL, &pShader, NULL, NULL);
		if (FAILED(result)){
			MessageBox(0, "hlsl�ǂݍ��ݎ��s VS or vs_5_0", NULL, MB_OK);
			return E_FAIL;
		}

		//���_�V�F�[�_�[�쐬
		result = m_pDevice->CreateVertexShader(pShader->GetBufferPointer(),
			pShader->GetBufferSize(), NULL, &m_pVertexShader);

		if (FAILED(result)){
			SAFE_RELEASE(pShader);
			MessageBox(0, "���_�V�F�[�_�[�쐬���s", NULL, MB_OK);
			return E_FAIL;
		}

		//���_�C���v�b�g�^�C�v���`,�@�Z�}���e�B�N�X�̍\�����`
		//�K�X�ǉ�
		D3D11_INPUT_ELEMENT_DESC inputElements[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		UINT numElement = sizeof(inputElements) / sizeof(D3D11_INPUT_ELEMENT_DESC);

		//���_�C���v�b�g���C�A�E�g(�Z�}���e�B�N�X�Ȃ�)���쐬
		result = m_pDevice->CreateInputLayout(inputElements, numElement,
			pShader->GetBufferPointer(), pShader->GetBufferSize(), &m_pInputLayout);

		if (FAILED(result))return result;

		
		//�u���u�փs�N�Z���V�F�[�_�[�R���p�C��
		result = D3DX11CompileFromFile("Shader\\PS.hlsl", NULL, NULL,
			"PS_Base", "ps_5_0", 0, 0, NULL, &pShader, NULL, NULL);

		if (FAILED(result)){
			MessageBox(0, "hlsl�ǂݍ��ݎ��s  PS or ps_5_0", NULL, MB_OK);
			return result;
		}

		result = m_pDevice->CreatePixelShader(pShader->GetBufferPointer(), pShader->GetBufferSize(),
			NULL, &m_pPixelShader);

		if (FAILED(result)){
			SAFE_RELEASE(pShader);
			MessageBox(0, "�s�N�Z���V�F�[�_�[�쐬���s", NULL, MB_OK);
			return result;
		}

		SAFE_RELEASE(pShader);



		//�R���X�^���g�o�b�t�@�[�쐬
		//SIMPLESHADER_CONSTANT_BUFFER�ō쐬���ꂽ
		//�ϊ��s����V�F�[�_�[�Ŏg�����߂̃o�b�t�@�[
		D3D11_BUFFER_DESC constantBufDesc;
		ZeroMemory(&constantBufDesc, sizeof(D3D11_BUFFER_DESC));
		constantBufDesc.Usage = D3D11_USAGE_DYNAMIC;
		constantBufDesc.ByteWidth = sizeof(AlwaysChangeCB);
		constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufDesc.MiscFlags = 0;
		constantBufDesc.StructureByteStride = 0;

		result = m_pDevice->CreateBuffer(&constantBufDesc, NULL, &m_pConstantBuffer);
		if (FAILED(result)){
			return result;
		}

		//�e�N�X�`���`��ׂ̈̏���SamplerState�ݒ�
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(D3D11_SAMPLER_DESC));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		result = m_pDevice->CreateSamplerState(&sampDesc, &m_pSamplerState);
		if (FAILED(result)){
			return result;
		}


		return S_OK;
	}

	//--------------------------------------------------------
	//			�|���S��������
	//--------------------------------------------------------
	HRESULT KdirectX3D::InitializeDebugPolygon(){
		HRESULT result = S_OK;

		////���_���`(�e�X�g�p��ł�)
		///*
		//Vertex3D verticies[] = 
		//{
		//	{ -1.0f, -1.0f,.0f},
		//	{ 0.0f, 1.0f, .0f },
		//	{ 1.0f, -1.0f, .0f }
		//	//{ -1.0f, 1.0f, .0f },

		//};


		//WORD indicecs[] = 
		//{
		//	0,2,1
		//	//2,1,3
  //    
		//};
		//*/
		//		Vertex3D verticies[] = 
		//{
		//	{0,     0.5f, 0},
		//	{0.5f, -0.5f, 0},
		//	{-0.5f, -0.5f, 0},
		//	{0.5f, 0.5f, 0}

		//};

		//WORD indicecs[] = 
		//{
		//	0,2,1,
		//	3,0,1
		//};


		//unsigned int numVertex = sizeof(verticies)/sizeof(Vertex3D);

		//result = CreateVertexBuffer(m_pVertexBuffer,verticies,numVertex);

		//numI = sizeof(indicecs)/sizeof(WORD);
		//result = CreateIndexBuffer(m_pIndexBuffer,indicecs,numI);
		//SetBuffer(m_pVertexBuffer, m_pIndexBuffer);
		
		return result;
	}

	//========--------========--------========--------========--------========
	//
	//			���t���[������
	//
	//========--------========--------========--------========--------========
	//--------------------------------------------------------
	//			DirectXBeginRender
	//-------------------------------------------------- ------
	void KdirectX3D::BeginRender(){
		//��ʃN���A(������)
		ColorF clearColor = {0,0,0.0f,1.0f};
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor.argb);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0); 

		//�`��Ɏg���V�F�[�_�[�Z�b�g
		m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
		m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
		m_pDeviceContext->HSSetShader(NULL, NULL, 0); //�n���V�F�[�_�[
		m_pDeviceContext->DSSetShader(NULL, NULL, 0); //�h���C���V�F�[�_�[
		m_pDeviceContext->GSSetShader(NULL, NULL, 0); //�W�I���g���V�F�[�_�[
		m_pDeviceContext->CSSetShader(NULL, NULL, 0); //�R���s���[�g�V�F�[�_�[

		//SamplerState�ݒ�
		m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	
	
	}
	
	//--------------------------------------------------------
	//			DirectXEndRender
	//--------------------------------------------------------
	void KdirectX3D::EndRender(){		

		
		//��ʍX�V(�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɃZ�b�g)
		m_pSwapChain->Present(0, 0);
	}


	//--------------------------------------------------------
	//			RenderIndexed
	//--------------------------------------------------------
	void KdirectX3D::RenderIndexed(DWORD numIndex){
		D3D11_MAPPED_SUBRESOURCE mappedData;

		m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);


		m_constantBufferData.WVP = m_worldTransMatrix * m_viewMatrix * m_projectionMatrix;
		//�V�F�[�_�[�͗�D�悾����]�u
		Mat4TransposeMatrix(m_constantBufferData.WVP, m_constantBufferData.WVP);

		memcpy(mappedData.pData, (void*)(&m_constantBufferData), sizeof(AlwaysChangeCB));
		//�R���X�^���g�o�b�t�@�[���A���}�b�v
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

		//�V�F�[�_�[�ɃR���X�^���g�o�b�t�@�[���Z�b�g
		m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);  //lol�K�v�ɂȂ�΃R�����g����

		//���_���̓��C�A�E�g���Z�b�g
		m_pDeviceContext->IASetInputLayout(m_pInputLayout);

		m_pDeviceContext->DrawIndexed(numIndex,0,0);
	}

	//--------------------------------------------------------
	//			Render
	//--------------------------------------------------------
	void KdirectX3D::Render(DWORD numVertex){
		D3D11_MAPPED_SUBRESOURCE mappedData;

		m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);


		m_constantBufferData.WVP = m_worldTransMatrix * m_viewMatrix * m_projectionMatrix;
		//�V�F�[�_�[�͗�D�悾����]�u
		Mat4TransposeMatrix(m_constantBufferData.WVP, m_constantBufferData.WVP);

		memcpy(mappedData.pData, (void*)(&m_constantBufferData), sizeof(AlwaysChangeCB));
		//�R���X�^���g�o�b�t�@�[���A���}�b�v
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

		//�V�F�[�_�[�ɃR���X�^���g�o�b�t�@�[���Z�b�g
		m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);  //lol�K�v�ɂȂ�΃R�����g����

		//���_���̓��C�A�E�g���Z�b�g
		m_pDeviceContext->IASetInputLayout(m_pInputLayout);

		m_pDeviceContext->Draw(numVertex, 0);
	}

	//--------------------------------------------------------
	//			Clear
	//--------------------------------------------------------
	void KdirectX3D::ClearTargetView(){
		float clearRGBA[4] = { 0, 0, 0, 0 };

		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearRGBA);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}


	void KdirectX3D::ClearTargetView(float a, float r, float g, float b){
		float clearRGBA[4] = {r , g, b, a};
	
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearRGBA);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0); 
	}

	void KdirectX3D::ClearTargetView(ColorI color){
		float clearRGBA[4] = { color.r / 256.0f, color.g / 256.0f, color.b / 256.0f, color.a / 256.0f };

		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearRGBA);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}


	void KdirectX3D::ClearDepthStencilView(){
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}



	//========--------========--------========--------========--------========
	//
	//			���̑�
	//
	//========--------========--------========--------========--------========
	//--------------------------------------------------------
	//			Release
	//--------------------------------------------------------
	void KdirectX3D::Release(){
		SAFE_RELEASE(m_pDevice);		
		SAFE_RELEASE(m_pDeviceContext);   	
		SAFE_RELEASE(m_pSwapChain);		
				
		SAFE_RELEASE(m_pRenderTargetView);	
		SAFE_RELEASE(m_pDepthStencilView);	

		SAFE_RELEASE(m_pDepthStencilTex);	
		SAFE_RELEASE(m_pRasterizerState);	
		SAFE_RELEASE(m_pInputLayout);		

		SAFE_RELEASE(m_pVertexShader);		
		SAFE_RELEASE(m_pPixelShader);   	
				
		SAFE_RELEASE(m_pConstantBuffer);	
		SAFE_RELEASE(m_pVertexBuffer);
		SAFE_RELEASE(m_pIndexBuffer);

		SAFE_RELEASE(m_pSamplerState);
	}

	
	//--------------------------------------------------------
	//			�`��p�o�b�t�@�[�Z�b�g
	//--------------------------------------------------------
	void KdirectX3D::SetBuffer(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer){
		//���_�o�b�t�@�[�Z�b�g
		UINT strides = sizeof(Vertex3D);
		UINT offsets = 0;
		m_pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offsets);

		//�C���f�b�N�X�o�b�t�@�[�Z�b�g
		m_pDeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);  //lol�C���f�b�N�X�o�b�t�@�[�T�C�Y��ύX����Ȃ炱�����ς���B
	}

	void KdirectX3D::SetVertexBuffer(ID3D11Buffer* vertexBuffer){
		UINT strides = sizeof(Vertex3D);
		UINT offsets = 0;
		m_pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offsets);
	}

	void KdirectX3D::SetIndexBuffer(ID3D11Buffer* indexBuffer){
		m_pDeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0); 
	}
	//--------------------------------------------------------
	//			���_�o�b�t�@�[�쐬
	//--------------------------------------------------------
	HRESULT KdirectX3D::CreateVertexBuffer(ID3D11Buffer*& vertexBuffer, const Vertex3D* vertices, unsigned int numVertices){
		HRESULT result;
		
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
		bd.ByteWidth = sizeof(Vertex3D)*numVertices;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		
		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory( &resourceData, sizeof(resourceData) );
		resourceData.pSysMem = vertices;
		
		result = m_pDevice->CreateBuffer(&bd, &resourceData, &vertexBuffer);
		if(FAILED(result))return result;

		return S_OK;
	}

	//--------------------------------------------------------
	//			�C���f�b�N�X�o�b�t�@�[�쐬
	//--------------------------------------------------------
	HRESULT KdirectX3D::CreateIndexBuffer(ID3D11Buffer*& indexBuffer, const WORD* indices, unsigned int numIndices){
		HRESULT result;
		
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.MiscFlags = 0;
		bd.ByteWidth = sizeof(WORD)*numIndices;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		
		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory( &resourceData, sizeof(resourceData) );
		resourceData.pSysMem = indices;
		
		result = m_pDevice->CreateBuffer(&bd, &resourceData, &indexBuffer);
		if(FAILED(result))return result;

		return S_OK;
	}

	//--------------------------------------------------------
	//			CreateDeviceAndSwapChain
	//--------------------------------------------------------
	HRESULT KdirectX3D::CreateDevicesAndSwapChain(ID3D11Device*& device, ID3D11DeviceContext*& deviceContext, IDXGISwapChain*& swapChain, D3D_FEATURE_LEVEL featureLevel, D3D_DRIVER_TYPE driverType){
		HRESULT result = S_OK;

		//SWAP_CHAIN�\���̂𖄂߂�
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = WindowSystem::windowWidth;
		sd.BufferDesc.Height = WindowSystem::windowHeight;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60; //FPS
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = WindowSystem::hWnd;  //DirectX�`���E�B���h�E�ݒ�
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;


		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		//�f�o�C�X�ƃX���b�v�`�F�[���쐬	
		result = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags, &featureLevel,
			1, D3D11_SDK_VERSION, &sd, &swapChain, &device, NULL, &deviceContext);
	
		if(FAILED(result)){
			MessageBox(0,"�X���b�v�`�F�[���쐬���s�BDirectX�o�[�W�����v�m�F",NULL,MB_OK);
			return result;
		}

		return result;
	}

	//--------------------------------------------------------
	//			CreateRenderTargetView
	//--------------------------------------------------------
	HRESULT KdirectX3D::CreateRenderTargetView(ID3D11Device* device, IDXGISwapChain* swapChain, ID3D11RenderTargetView*& RenderTargetView){
		HRESULT result = S_OK;
		ID3D11Texture2D *pBackBuffer = nullptr;

		//�X���b�v�`�F�[���������Ă���o�b�N�o�b�t�@�[���擾
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if(FAILED(result)){
			return result;
		}
		
		//�o�b�N�o�b�t�@�[�𗘗p���郌���_�[�^�[�Q�b�g�r���[�쐬
		result = device->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		SAFE_RELEASE(pBackBuffer);//GetBuffer�Ń|�C���^���擾������̓����[�X����B
		if(FAILED(result)){
			return result;
		}

		return result;
	}

	//--------------------------------------------------------
	//			CreateStencilDepthView
	//--------------------------------------------------------
	HRESULT KdirectX3D::CreateStencilDepthViewAndTexture(ID3D11Device* device, ID3D11Texture2D*& depthStencilTex, ID3D11DepthStencilView*& depthStencilView, DXGI_FORMAT format){
		HRESULT result;

		//DepthStencil�e�N�X�`���쐬
		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory( &descDepth, sizeof(descDepth) );
		descDepth.Width = WindowSystem::windowWidth;
		descDepth.Height = WindowSystem::windowHeight;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = format;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		result = device->CreateTexture2D( &descDepth, NULL, &depthStencilTex );
		if( FAILED( result ) ){
			return result;
		}

		//DepthStencilView�쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory( &descDSV, sizeof(descDSV) );
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		result = device->CreateDepthStencilView( depthStencilTex, &descDSV, &depthStencilView );
		if( FAILED( result ) ){
			return result;
		}

		return S_OK;
	}




} //namespace