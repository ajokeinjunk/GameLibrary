#pragma once

#include "../KJ_Defines/KJ_Defines.h"

namespace Klibrary{
	//Colorç\ë¢ëÃ
	union ColorF{
		struct{
			float r;
			float g;
			float b;
			float a;
		};
		float argb[4];  //RGBAÇ≈äiî[ÇµÇ‹Ç∑ÅB

		inline void operator *=(float s){
			a *= s; r *= s; g *= s; b *= s;
		}

		inline ColorF operator *(float s){
			ColorF color;
			color.a *= s; color.r *= s; color.g *= s; color.b *= s;
			return  color;
		}
	};

	union ColorI{
		struct{
			jUInt8 b;
			jUInt8 g;
			jUInt8 r;
			jUInt8 a;
		};
		//0xFFFFFFFF
		jUInt32 argb;

		inline ColorI& operator *=(jUInt8 s){
			a *= s; r *= s; g *= s; b *= s;
			return *this;
		}

		inline ColorI operator *(float s){
			ColorI color;
			color.a = (jUInt8)((float)color.a * s);
			color.r = (jUInt8)((float)color.r * s);
			color.g = (jUInt8)((float)color.g * s);
			color.b = (jUInt8)((float)color.b * s);
			return  color;
		}

	};

	class BasicColor{
	public:
		const static ColorF White;
		const static ColorF Black;
		const static ColorF Red;
		const static ColorF Green;
		const static ColorF Blue;
		const static ColorF Yellow;
		const static ColorF Gray;
	};
}