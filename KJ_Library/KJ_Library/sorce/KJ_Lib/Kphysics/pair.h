#ifndef __H_PAIR_H__
#define __H_PAIR_H__
#include "../../../IEX/iextreme.h"
#include "Contact.h"

namespace Kmath{
	
	//ペアの種類
	enum PairType{
		NEW,       //新規
		KEEP,      //継続
	};

	//ペア
	struct Pair{
		PairType type;
		union{
			unsigned long long key;
			struct{
				unsigned int rigidBodyA;   //剛体Aのインデックス
				unsigned int rigidBodyB;   //剛体Bのインデックス
			};
		};
		
		ContactData   *contactData; //衝突情報へのポインタ

	};
}//////// namespace Kmath


#endif