#include "KJ_BasicForm.h"



namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			基本形状クラス
	//
	//========--------========--------========--------========--------========

	//----------------------------------------------------------------------------------------------------------------------------
	//			箱作成
	//----------------------------------------------------------------------------------------------------------------------------
	bool KJ_BaseFormMesh::MakeBox(float width, float height, float devide){
		KJ_Mesh::Initialize();
		
		//頂点位置配列
		width /= 2.0f;
		height /= 2.0f;
		devide /= 2.0f;

		Vector3 workV[8] = {
			Vector3(-width,height,devide),
			Vector3(width,height,devide),
			Vector3(-width,-height,devide),
			Vector3(width,-height,devide),
			Vector3(-width,height,-devide),
			Vector3(width,height,-devide),
			Vector3(-width,-height,-devide),
			Vector3(width,-height,-devide),
		};

		Face3D workF[12] = {
			{0,1,2},
			{1,3,2},
			{1,5,3},
			{5,7,3},
			{5,4,7},
			{4,6,7},
			{4,0,6},
			{0,2,6},
			{4,5,0},
			{5,1,0},
			{2,3,6},
			{3,7,6}
		};

		//材質設定
		Material workM = {
		0.1f, 0.1f, 0.1f, 1.0f,
		1.0f, 0.4f, 0.4f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		15.0f
		};

		m_meshInfo->SetMeshInformation(true, 8,workV, 12, workF, 1, &workM);

		return true;
	}

	//----------------------------------------------------------------------------------------------------------------------------
	//			平面作成
	//----------------------------------------------------------------------------------------------------------------------------
	bool KJ_BaseFormMesh::MakePlane(float w, float h, int numPartition){
		int numV = (numPartition+1) * (numPartition+1); //頂点数
		int numF = numPartition *numPartition * 2;     //面数
		Vector3* workV = new Vector3[numV];
		Face3D* workP = new Face3D[numF];
	

		float wd = 2*w/numPartition;
		float hd = 2*h/numPartition;
		float hh = 2*w/2;
		float wh = 2*h/2;

		//頂点設定
		int now = 0;
		for(int y=0; y<numPartition+1; y++){
			for(int x=0; x<numPartition+1; x++){
				now = y*(numPartition+1) + x;
				workV[now].x = x*wd-hh;
				workV[now].y = 0.0f;
				workV[now].z = -y*hd+wh;
			}
		}
	
		Vector3 n;
		Vec3Cross(n, workV[1],workV[0]);
		n.Normalize();

		int i=0;
		float texU = 0;
		float texV = 0;
		//ポリゴン設定

		for(int y=0; y<numPartition; y++){
			texU = (float)y / (float)numPartition;

			for(int x=0; x<numPartition; x++){
				texV = (float)x / (float)numPartition;
				int now = y*(numPartition+1) + x;

				workP[i].index[0] = now;
				workP[i].index[1] = now+1;
				workP[i].index[2] = now+numPartition+1;
				workP[i].color.argb = 0xFF000000 + x * 255;

				workP[i].faceNormal = n;
				workP[i].texPos[0].u = texU;
				workP[i].texPos[0].v = texV;
				workP[i].texPos[1].u = texU;
				workP[i].texPos[1].v = texV;
				workP[i].texPos[2].u = texU;
				workP[i].texPos[2].v = texV;

			
				workP[i+1].index[0] = now+1;
				workP[i+1].index[1] = now+numPartition+2;
				workP[i+1].index[2] = now+numPartition+1;
				workP[i+1].color.argb = 0xFF00FFFF + y * 255;
				workP[i+1].faceNormal = n;
				workP[i+1].texPos[0].u = texU;
				workP[i+1].texPos[0].v = texV;
				workP[i+1].texPos[1].u = texU;
				workP[i+1].texPos[1].v = texV;
				workP[i+1].texPos[2].u = texU;
				workP[i+1].texPos[2].v = texV;



				i += 2;
			}
		}

	
			//材質設定
		Material workM = {
			0.1f, 0.1f, 0.1f, 0.1f,
			0.2f, 0.2f, 0.2f, 1.0f,
			0.5f, 1.5f, 0.5f, 1.0f,
			15.0f
		};

		m_meshInfo->SetMeshInformation(true, numV,workV,numF,workP, 1, &workM);
		delete[] workV;
		delete[] workP;

		return true;
	}

}//namespace