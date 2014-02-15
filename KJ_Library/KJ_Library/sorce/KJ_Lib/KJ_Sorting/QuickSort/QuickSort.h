#ifndef H_KLIB_QUICK_SORT_H
#define H_KLIB_QUICK_SORT_H

namespace Klibrary{


	class QuickSort{
	private:
		template <class T>
		static void SortContents(T* arrayData[], unsigned int head, unsigned int terminus);

	public:
		template <class T>
		static bool Sort(T* arrayData[], unsigned int numElements);
	};
}

#endif