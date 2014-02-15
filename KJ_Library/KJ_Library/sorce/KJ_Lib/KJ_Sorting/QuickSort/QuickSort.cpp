#include "QuickSort.h"

namespace Klibrary{
	template <class T>
	void QuickSort::SortContents(T* arrayData[], unsigned int head, unsigned int terminus){
		if (head == terminus)return;
		if ((terminus - head) == 1){
			if (arrayData[terminus] < arrayData[head]){
				T* workData = nullptr;
				workData = arrayData[head];
				arrayData[head] = arrayData[terminus];
				arrayData[terminus] = workData;
			}
			return;
		}

		float pivotNum = 0;
		unsigned int count = 0;
		for (unsigned int i = head; i <= terminus; i++){
			pivotNum += arrayData[i];
			count++;
		}

		pivotNum /= count;
		unsigned int h = head;
		unsigned int t = terminus;
		ColPoint* workData = nullptr;
		bool flag = false;

		while (h <= t)
		{
			while (arrayData[h] < pivotNum)
			{
				flag |= true;
				h++;
			}

			while (arrayData[t] > pivotNum)
			{
				flag |= true;
				t--;
			}

			if (h>t){
				if (flag == false){
					return;
				}
				break;
			}
			workData = arrayData[h];
			arrayData[h] = arrayData[t];
			arrayData[t] = workData;
			h++;
			t--;
		}


		SortContents(arrayData, head, h - 1);
		SortContents(arrayData, h, terminus);
	}

	template <class T>
	bool QuickSort::Sort(T* arrayData[], unsigned int numElements){
		if (numPoints <= 1)return false;
		if (arrayData == nullptr)return false;

		SortContents(arrayData, 0, numElements - 1);
		return true;
	}

}