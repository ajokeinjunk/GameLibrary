#ifndef __H_PAIR_H__
#define __H_PAIR_H__
#include "../../../IEX/iextreme.h"
#include "Contact.h"

namespace Kmath{
	
	//�y�A�̎��
	enum PairType{
		NEW,       //�V�K
		KEEP,      //�p��
	};

	//�y�A
	struct Pair{
		PairType type;
		union{
			unsigned long long key;
			struct{
				unsigned int rigidBodyA;   //����A�̃C���f�b�N�X
				unsigned int rigidBodyB;   //����B�̃C���f�b�N�X
			};
		};
		
		ContactData   *contactData; //�Փˏ��ւ̃|�C���^

	};
}//////// namespace Kmath


#endif