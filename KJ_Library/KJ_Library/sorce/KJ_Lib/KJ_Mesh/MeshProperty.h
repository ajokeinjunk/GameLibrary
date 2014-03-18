#ifndef H_KLIB_MESH_DATA_H
#define H_KLIB_MESH_DATA_H

#pragma warning(disable:4005)

#include "../KJ_Texture/KJ_Texture.h"
#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Defines/KJ_Defines.h"
#include "Material.h"
#include <Windows.h>

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			Colorクラス
	//
	//========--------========--------========--------========--------========
#define COLOR_MAXIMUM 255

	struct TexPos{
		float u;
		float v;

		TexPos():u(0.0f), v(0.0f){}
	};


	//頂点情報
	struct Vertex3D{
		Vector3 pos;
		ColorF color;
		Vector3 normal;
		TexPos texPos;
	};

	//1ポリゴン情報
	struct Face3D{
		jUInt16 index[3];
		Vector3 faceNormal;
		Vector3 vertexNormal[3];
		ColorI color;
		TexPos texPos[3];
		jUInt16 materialIndex;
	};

	////マテリアル情報
	//struct Material{
	//	ColorF ambient;
	//	ColorF diffuese;
	//	ColorF specular;
	//	float  specularPower;
	//	ColorF luminous;
	//};

	//========--------========--------========--------========--------========
	//
	//			BaseMeshInfoクラス
	//
	//========--------========--------========--------========--------========
	class BaseMeshInfo{
	protected:
		jUInt32 m_numVertices;  //頂点数
		Vector3* m_pVertices;

		jUInt32 m_numFaces;
		Face3D* m_pFaces;

		jUInt8 m_numMaterials;
		Material* m_pMaterials;
		jUInt8* m_pNumFacesPerMaterial;

		jUInt16 m_numTextures;
		BaseTexture** m_ppTexture;

		bool CalculateNormal();
		void SortByMaterials();
		virtual void CreateBuffer() = 0;
	
	public:
		BaseMeshInfo() : m_numTextures(0), m_numVertices(0), m_pVertices(nullptr), m_numFaces(0),
			m_pFaces(nullptr), m_numMaterials(0), m_pMaterials(nullptr), m_ppTexture(nullptr), m_pNumFacesPerMaterial(nullptr){}
		virtual ~BaseMeshInfo(){ Release(); }

		bool LoadMesh(char* filename);
		bool SetMeshInformation(bool doSetNormal, jUInt32 numVertices, const Vector3* vertices, jUInt32 numFaces, const Face3D* faces, jUInt8 numMaterials, const Material* materials);

		virtual void Render() = 0;
		virtual BaseMeshInfo* CopyMesh(){ return nullptr; }


		virtual void Release(){
			SAFE_DELETE_ARRAY(m_pVertices);
			SAFE_DELETE_ARRAY(m_pFaces);
			SAFE_DELETE_ARRAY(m_pMaterials);
			SAFE_DELETE_ARRAY(m_pNumFacesPerMaterial);

			if (m_ppTexture){
				for (jUInt16 i = 0; i < m_numTextures; i++){
					SAFE_DELETE(m_ppTexture[i]);
				}
				SAFE_DELETE_ARRAY(m_ppTexture);
			}
		}


		static bool LoadMQO(char* filename, BaseMeshInfo& pMeshInfo);
		static bool LoadFBX(char* filename, BaseMeshInfo& pMeshInfo);
	};


	//========--------========--------========--------========--------========
	//			MeshIndexedInfoクラス
	//========--------========--------========--------========--------========
	class MeshIndexedInfo : public BaseMeshInfo{
	protected:
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		void CreateBuffer();


	public:
		MeshIndexedInfo() : m_pVertexBuffer(nullptr),
			m_pIndexBuffer(nullptr){}

		virtual ~MeshIndexedInfo(){
			Release();
		}

		void Render();


		void Release(){
			BaseMeshInfo::Release();

			SAFE_RELEASE(m_pVertexBuffer);
			SAFE_RELEASE(m_pIndexBuffer);
		}
	};

	//========--------========--------========--------========--------========
	//			MeshVertexInfoクラス
	//========--------========--------========--------========--------========
	class MeshVertexInfo : public BaseMeshInfo{
	protected:
		ID3D11Buffer* m_pVertexBuffer;

		void CreateBuffer();


	public:
		MeshVertexInfo() : m_pVertexBuffer(nullptr){}
		virtual ~MeshVertexInfo(){
			Release();
		}

		void Render();

		void Release(){
			BaseMeshInfo::Release();
			SAFE_RELEASE(m_pVertexBuffer);
		}
	};

}//namespace
#endif