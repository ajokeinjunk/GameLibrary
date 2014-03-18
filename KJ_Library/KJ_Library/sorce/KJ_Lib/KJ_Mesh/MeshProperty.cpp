#include "MeshProperty.h"
#include <stdio.h>
#include "../KJ_Renderer/KJ_RenderSystem.h"
#include "../KJ_File/KJ_File.h"
//#include "../KJ_Resource/AllResourceManager.h"

#include <string>

#define MQO "mqo"

#pragma warning(disable : 4996)

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Colorクラス
	//
	//========--------========--------========--------========--------========
	const ColorF BasicColor::White  = { 1.0f, 1.0f, 1.0f, 1.0f };
	const ColorF BasicColor::Black  = { 0.0f, 0.0f, 0.0f, 1.0f };
	const ColorF BasicColor::Red    = { 1.0f, 0.0f, 0.0f, 1.0f };
	const ColorF BasicColor::Green  = { 0.0f, 1.0f, 0.0f, 1.0f };
	const ColorF BasicColor::Blue   = { 0.0f, 0.0f, 1.0f, 1.0f };
	const ColorF BasicColor::Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	const ColorF BasicColor::Gray   = { 0.5f, 0.5f, 0.5f, 1.0f };


	//========--------========--------========--------========--------========
	//
	//			BaseMeshInfoクラス
	//
	//========--------========--------========--------========--------========
	bool BaseMeshInfo::LoadMesh(char* filename){

		bool f = false;
		char extention[20];
		f = KJ_File::CopyFileExtention(extention, filename);

#ifdef _DEBUG
		if (f == false){
			MessageBox(NULL, TEXT(filename), TEXT("わーにん!ファイル名読み込み"), MB_OK | MB_ICONWARNING);
		}
#endif

		if (0 == stricmp(extention, MQO)){
			LoadMQO(filename, *this);
			CalculateNormal();
		}
		

		CreateBuffer();


		return f;
	}

	

	//========--------========--------========--------========--------========
	//			作成ポリゴン読み込み用
	//			自分で作ったポリゴン作った場合のみ呼び出す。
	//========--------========--------========--------========--------========
	bool BaseMeshInfo::SetMeshInformation(bool doSetNormal, jUInt32 numVertices, const Vector3* vertices, jUInt32 numFaces, const Face3D* faces, jUInt8 numMaterials, const Material* materials){
		if (numVertices <= 0 || numFaces <= 0 || numMaterials <= 0)return false;
		if (m_numVertices > 0)return false;

		//頂点コピー
		m_numVertices = numVertices;
		SAFE_DELETE(m_pVertices);
		m_pVertices = new Vector3[numVertices];
		memcpy(m_pVertices, vertices, sizeof(Vector3)* numVertices);

		//面コピー
		m_numFaces = numFaces;
		SAFE_DELETE(m_pFaces);
		m_pFaces = new Face3D[numFaces];
		memcpy(m_pFaces, faces, sizeof(Face3D)* numFaces);

		//マテリアルコピー
		m_numMaterials = numMaterials;
		SAFE_DELETE(m_pMaterials);
		m_pMaterials = new Material[numMaterials];
		memcpy(m_pMaterials, materials, sizeof(Material)* numMaterials);

		if(doSetNormal)CalculateNormal();
		CreateBuffer();

		return true;
	}

	//========--------========--------========--------========--------========
	//			面法線と頂点法線を計算する。
	//========--------========--------========--------========--------========
	bool BaseMeshInfo::CalculateNormal(){
		if (m_numFaces <= 0 || m_numVertices <= 0)return false;

		Vector3 v1, v2, n;
		jUInt16 i0, i1, i2;

		for (jUInt32 f = 0; f<m_numFaces; f++){
			i0 = m_pFaces[f].index[0];
			i1 = m_pFaces[f].index[1];
			i2 = m_pFaces[f].index[2];

			v1.x = m_pVertices[i1].x - m_pVertices[i0].x;
			v1.y = m_pVertices[i1].y - m_pVertices[i0].y;
			v1.z = m_pVertices[i1].z - m_pVertices[i0].z;

			v2.x = m_pVertices[i2].x - m_pVertices[i0].x;
			v2.y = m_pVertices[i2].y - m_pVertices[i0].y;
			v2.z = m_pVertices[i2].z - m_pVertices[i0].z;

			Vec3Cross(n, v1, v2);
			n.Normalize();
			m_pFaces[f].faceNormal = n;
		}


		Vector3* work = new Vector3[m_numVertices];
		//面法線から頂点法線計算
		jUInt32 f = 0;
		for (f = 0; f<m_numFaces; f++){
			work[m_pFaces[f].index[0]] += m_pFaces[f].faceNormal;
			work[m_pFaces[f].index[1]] += m_pFaces[f].faceNormal;
			work[m_pFaces[f].index[2]] += m_pFaces[f].faceNormal;
		}

		//法線正規化
		for (f = 0; f<m_numVertices; f++){
			work[f].Normalize();
		}

		//全ポリゴン頂点法線に代入
		for (f = 0; f<m_numFaces; f++){
			m_pFaces[f].vertexNormal[0] = work[m_pFaces[f].index[0]];
			m_pFaces[f].vertexNormal[1] = work[m_pFaces[f].index[1]];
			m_pFaces[f].vertexNormal[2] = work[m_pFaces[f].index[2]];

		}

		SAFE_DELETE_ARRAY(work);

		return true;
	}

	void BaseMeshInfo::SortByMaterials(){
		if (m_numMaterials <= 1)return;

		Face3D* workFace = new Face3D[m_numFaces];
		jUInt32 currentFace = 0;
		m_pNumFacesPerMaterial = new jUInt8[m_numMaterials];

		for (jUInt8 m = 0; m < m_numMaterials; m++){
			m_pNumFacesPerMaterial[m] = 0;

			for (jUInt32 f = 0; f < m_numFaces; f++){
				if (m_pFaces[f].materialIndex != m){ continue; }

				workFace[currentFace] = m_pFaces[f];

				currentFace++;
				m_pNumFacesPerMaterial[m]++;
			}
		}

		SAFE_DELETE_ARRAY(m_pFaces);
		m_pFaces = workFace;
	}


	//========--------========--------========--------========--------========
	//			MeshIndexedInfoクラス
	//========--------========--------========--------========--------========
	//========--------========--------========--------========--------========
	//			これが呼ばれない限りrendererにバッファーが作られない
	//========--------========--------========--------========--------========
	void MeshIndexedInfo::CreateBuffer(){
		Vertex3D* vertex = new Vertex3D[m_numVertices];
		jUInt16* indices = new jUInt16[m_numFaces * 3];  //lol どこでJUint16使用と定義づけているか確認すること。


		//インデックス情報代入
		jUInt32 count = 0;
		jUInt8 v = 0;
		for (jUInt32 f = 0; f<m_numFaces; f++){
			for (v = 0; v < 3; v++){
				//インデックス代入
				indices[count + v] = m_pFaces[f].index[v]; 
				vertex[m_pFaces[f].index[v]].normal.x = m_pFaces[f].vertexNormal[v].x;//lol法線はどの順番で入れればいいのか。
				vertex[m_pFaces[f].index[v]].normal.y = m_pFaces[f].vertexNormal[v].y;
				vertex[m_pFaces[f].index[v]].normal.z = m_pFaces[f].vertexNormal[v].z;
				
				vertex[m_pFaces[f].index[v]].texPos.u = m_pFaces[f].texPos[v].u;
				vertex[m_pFaces[f].index[v]].texPos.v = m_pFaces[f].texPos[v].v;

				vertex[m_pFaces[f].index[v]].color.a = (float)m_pFaces[f].color.a / 255.0f;
				vertex[m_pFaces[f].index[v]].color.r = (float)m_pFaces[f].color.r / 255.0f;
				vertex[m_pFaces[f].index[v]].color.g = (float)m_pFaces[f].color.g / 255.0f;
				vertex[m_pFaces[f].index[v]].color.b = (float)m_pFaces[f].color.b / 255.0f;
			}
			count += 3;
		}

		//頂点情報代入
		for (jUInt32 v = 0; v<m_numVertices; v++){
			//頂点
			vertex[v].pos.x = m_pVertices[v].x;
			vertex[v].pos.y = m_pVertices[v].y;
			vertex[v].pos.z = m_pVertices[v].z;
		}

		RenderSystem::GetRenderer()->CreateVertexBuffer(m_pVertexBuffer, vertex, m_numVertices);
		RenderSystem::GetRenderer()->CreateIndexBuffer(m_pIndexBuffer, indices, m_numFaces * 3);

		SAFE_DELETE_ARRAY(vertex);
		SAFE_DELETE_ARRAY(indices);
	}



	//========--------========--------========--------========--------========
	//		　 描画
	//========--------========--------========--------========--------========
	void MeshIndexedInfo::Render(){

		Renderer->SetBuffer(m_pVertexBuffer, m_pIndexBuffer);
		if(m_ppTexture)m_ppTexture[0]->SendShader(0);
		Renderer->RenderIndexed(m_numFaces*3); 
	}


	//========--------========--------========--------========--------========
	//			MeshVertexInfoクラス
	//========--------========--------========--------========--------========
	
	void MeshVertexInfo::CreateBuffer(){
		Vertex3D* vertex = new Vertex3D[m_numFaces*3];


		//インデックス情報代入
		jUInt32 count = 0;
		jUInt8 v = 0;
		for (jUInt32 f = 0; f<m_numFaces; f++){
			for (v = 0; v < 3; v++){
				//インデックス代入
				vertex[count].normal.x = m_pFaces[f].vertexNormal[v].x;//lol法線はどの順番で入れればいいのか。
				vertex[count].normal.y = m_pFaces[f].vertexNormal[v].y;
				vertex[count].normal.z = m_pFaces[f].vertexNormal[v].z;
				
				vertex[count].texPos.u = m_pFaces[f].texPos[v].u;
				vertex[count].texPos.v = m_pFaces[f].texPos[v].v;
				
				vertex[count].color.a = (float)m_pFaces[f].color.a / 255.0f;
				vertex[count].color.r = (float)m_pFaces[f].color.r / 255.0f;
				vertex[count].color.g = (float)m_pFaces[f].color.g / 255.0f;
				vertex[count].color.b = (float)m_pFaces[f].color.b / 255.0f;

				vertex[count].pos.x = m_pVertices[m_pFaces[f].index[v]].x;
				vertex[count].pos.y = m_pVertices[m_pFaces[f].index[v]].y;
				vertex[count].pos.z = m_pVertices[m_pFaces[f].index[v]].z;
				
				count++;
			}
		}

		RenderSystem::GetRenderer()->CreateVertexBuffer(m_pVertexBuffer, vertex, m_numFaces * 3);

		SAFE_DELETE_ARRAY(vertex);
	}



	//========--------========--------========--------========--------========
	//		　 描画
	//========--------========--------========--------========--------========
	void MeshVertexInfo::Render(){

		Renderer->SetVertexBuffer(m_pVertexBuffer);
		if (m_ppTexture)m_ppTexture[0]->SendShader(0);
		Renderer->Render(m_numFaces * 3);
	}



}//namespace