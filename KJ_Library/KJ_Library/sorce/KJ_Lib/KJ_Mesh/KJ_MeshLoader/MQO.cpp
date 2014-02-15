#include "../MeshProperty.h"
#include "../../TextLoader/textLoader.h"
#include <assert.h>

#pragma warning(disable:4996)

namespace Klibrary{
	//========--------========--------========--------========--------========
	//			MQO�Ǎ�
	//			lol�}�e���A���ƃe�N�X�`������������Ă��܂��B
	//========--------========--------========--------========--------========
	bool BaseMeshInfo::LoadMQO(char* filename, BaseMeshInfo& meshInfo){
		textLoader* loader = new textLoader(filename);

		//�ގ�����
		loader->Search("Material");


		//�ގ��ǂݍ���
		meshInfo.m_numMaterials = loader->LoadInt();
		assert(meshInfo.m_numMaterials > 0);


		if (meshInfo.m_numMaterials > 0){
			//�o�b�t�@�m��
			SAFE_DELETE_ARRAY(meshInfo.m_pMaterials);
			meshInfo.m_pMaterials = new Material[meshInfo.m_numMaterials];
			meshInfo.m_ppTexture = new BaseTexture*[meshInfo.m_numMaterials];  //lol �ގ����e�N�X�`�����������m�ۂ���̂Ŗ��ʂ�����B
		}
		loader->In();

		jFloat amb, emi, spec, dif, power;
		char work[64];
		char dir[250];

		for (jUInt32 m = 0; m<meshInfo.m_numMaterials; m++){
			//�ގ���

			loader->LoadString(work);

			//�ގ��F�ǂݍ���
			loader->SearchLine("col");
			meshInfo.m_pMaterials[m].diffuese.r = loader->LoadFloat();
			meshInfo.m_pMaterials[m].diffuese.g = loader->LoadFloat();
			meshInfo.m_pMaterials[m].diffuese.b = loader->LoadFloat();
			meshInfo.m_pMaterials[m].diffuese.a = loader->LoadFloat();

			//�f�B�t���[�Y�ǂݍ���
			loader->SearchLine("dif");
			dif = loader->LoadFloat();

			//�A���r�G���ǂݍ���
			loader->SearchLine("amb");
			amb = loader->LoadFloat();

			//���݂����ԓǂݍ���
			loader->SearchLine("emi");
			emi = loader->LoadFloat();


			//���؂����[
			loader->SearchLine("spc");
			spec = loader->LoadFloat();

			//���؂����[�ς�`
			loader->SearchLine("power");
			power = loader->LoadFloat();


			meshInfo.m_pMaterials[m].ambient.r = amb;
			meshInfo.m_pMaterials[m].ambient.g = amb;
			meshInfo.m_pMaterials[m].ambient.b = amb;
			meshInfo.m_pMaterials[m].ambient.a = 1.0f;

			meshInfo.m_pMaterials[m].specular.r = spec;
			meshInfo.m_pMaterials[m].specular.g = spec;
			meshInfo.m_pMaterials[m].specular.b = spec;
			meshInfo.m_pMaterials[m].specular.a = spec;

			meshInfo.m_pMaterials[m].specularPower = power;

			/*workM[m].luminousA = emi;
			workM[m].luminousR = emi;
			workM[m].luminousG = emi;
			workM[m].luminousB = emi;*/

			//�e�N�X�`�����擾
			if (loader->SearchLine("tex")){
				loader->LoadName(work);


				strcpy(dir, filename);
				int i = -1;
				int j = 0;

				while (dir[j] != '\0'){
					if (dir[j] == '/')i = j;
					if (dir[j] == '\\')i = j;
					j++;
				}

				dir[i + 1] = '\0';

				char texname[128];
				sprintf(texname, "%s%s", dir, work);

				meshInfo.m_ppTexture[m] = new BaseTexture();
				meshInfo.m_ppTexture[m]->LoadTexture(texname);

				meshInfo.m_numTextures++;

			}
			else{
				meshInfo.m_ppTexture[m] = new BaseTexture();
				meshInfo.m_ppTexture[m]->LoadTexture("NoTex.png");
				meshInfo.m_numTextures++;
			}
			//���̍s��
			loader->newLine();
		}


		//���_������
		loader->Search("vertex");
		//���_�ǂݍ��݁��o�b�t�@�m��
		meshInfo.m_numVertices = loader->LoadInt();
		assert(meshInfo.m_numVertices > 0);
		if (meshInfo.m_numVertices <= 0){ return false; }

		meshInfo.m_pVertices = new Vector3[meshInfo.m_numVertices];

		//���_�ǂݍ���
		loader->In();
		for (jUInt32 v = 0; v<meshInfo.m_numVertices; v++){
			meshInfo.m_pVertices[v].x = -loader->LoadFloat();
			meshInfo.m_pVertices[v].y = loader->LoadFloat();
			meshInfo.m_pVertices[v].z = loader->LoadFloat();
		}

		//�|���S���f�[�^����
		loader->Search("face");
		//�|���S�����ǂݍ��݁��o�b�t�@�m��
		meshInfo.m_numFaces = loader->LoadInt();
		assert(meshInfo.m_numFaces > 0);


		meshInfo.m_pFaces = new Face3D[meshInfo.m_numFaces];

		//�|���S���ǂݍ���
		loader->In();
		for (jUInt32 f = 0; f<meshInfo.m_numFaces; f++){
			//�g�p���_�ǂݔ�΂�
			loader->LoadInt();
			
			//if (numFaceVertex == 4){
			//	//�ŏ���face�Ǎ���ŁA
			//	//�c��񐔕�while�񂷁B
			//
			//	numFaceVertex -= 3;
			//	Face3D* face = new Face3D[numFaceVertex+1];

			//	while (numFaceVertex){

			//	}


			//	loader->newLine();
			//	continue;
			//}

			//���_�C���f�b�N�X�ǂݍ���
			loader->SearchLine("V");
			meshInfo.m_pFaces[f].index[0] = loader->LoadInt();
			meshInfo.m_pFaces[f].index[1] = loader->LoadInt();
			meshInfo.m_pFaces[f].index[2] = loader->LoadInt();


			//�}�e���A���ԍ��ǂݍ���
			loader->SearchLine("M");
			meshInfo.m_pFaces[f].materialIndex = loader->LoadInt();

			loader->SearchLine("UV");


			for (jUInt8 n = 0; n<3; n++){
				meshInfo.m_pFaces[f].texPos[n].u = loader->LoadFloat();
				meshInfo.m_pFaces[f].texPos[n].v = loader->LoadFloat();
			}

			meshInfo.m_pFaces[f].color.argb = 0xFF000000;


			//���ɍs��
			loader->newLine();
		}


		delete loader;

		return true;
	}
}