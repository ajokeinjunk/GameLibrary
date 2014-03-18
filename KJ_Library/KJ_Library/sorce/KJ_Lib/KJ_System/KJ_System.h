#ifndef H_KLIB_SYSTEM_H
#define H_KLIB_SYSTEM_H


//ƒ}ƒNƒ
#define SAFE_RELEASE(x){if(x){x->Release(); x = nullptr;}}
#define SAFE_DELETE(x){if(x){delete x; x = nullptr;}}
#define SAFE_DELETE_ARRAY(x) {if(x){delete[] x; x = nullptr;}}

#define DEFAULT_ARRAY_DELETE(x) {std::default_delete<x[]>()}
#define SIZE_OF_ARRAY(x) {sizeof(x)/sizeof(x[0]) }

#endif