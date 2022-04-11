#pragma once
#include <memory>

enum class JSortType {
	BubbleSort,
	HeapSort,
	QuickSort,
	MergeSort
};

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT, JSortType type_>
class JSort {
public:

	void Sort(CONT<T>& elems);

};

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
void Heapify(CONT<T>& elems, int root, int length);

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
void Merge(CONT<T>& elems, int begin_, int medium_, int end_);