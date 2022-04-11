#pragma once
#include "JSort.h"
#include <iostream>
#include <algorithm>

#define JSORT_SET(A) template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT> \
class JSort<T, CONT, A> \
{  \
public: \
   void Sort(CONT<T>& elems); \
};

#define JSORT_SET_WITH_RANGE(A) template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT> \
class JSort<T, CONT, A> \
{  \
public: \
   void Sort(CONT<T>& elems, int begin_, int end_); \
};

JSORT_SET(JSortType::BubbleSort)
JSORT_SET(JSortType::HeapSort)
JSORT_SET_WITH_RANGE(JSortType::QuickSort)
JSORT_SET_WITH_RANGE(JSortType::MergeSort)

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
void Heapify(CONT<T>& elems, int root, int length)
{
	int left = 2 * root + 1;
	int right = left + 1;
	int largest = root;
	
	if (left < length && elems[largest] < elems[left])
	{
		largest = left;
	}

	if (right < length && elems[largest] < elems[right])
	{
		largest = right;
	}

	if (largest != root)
	{
		std::swap(elems[root], elems[largest]);
		Heapify(elems, largest, length);
	}
}

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
void Merge(CONT<T>& elems, int begin_, int medium_, int end_)
{
	CONT<T> temp_;
	int a = begin_, b = medium_ + 1;
	while (a <= medium_ && b <= end_)
	{
		if (elems[a] < elems[b])
		{
			temp_.push_back(elems[a]);
			++a;
		}
		else
		{
			temp_.push_back(elems[b]);
			++b;
		}
	}

	while (a <= medium_)
	{
		temp_.push_back(elems[a]);
		++a;
	}

	while (b <= end_)
	{
		temp_.push_back(elems[b]);
		++b;
	}

	std::copy(temp_.begin(), temp_.end(), elems.begin() + begin_);
}

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
void JSort<T, CONT, JSortType::BubbleSort>::Sort(CONT<T>& elems)
{
	auto len = elems.size();

	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (elems[j] > elems[j + 1])
				std::swap(elems[j], elems[j + 1]);
		}
	}
}

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
void JSort<T, CONT, JSortType::HeapSort>::Sort(CONT<T>& elems)
{
	int length = elems.size();
	for (int i = length / 2; i >= 0; --i)
		Heapify(elems, i, length);

	for (int i = length - 1; i >= 0; --i)
	{
		std::swap(elems[0], elems[i]);
		--length;
		Heapify(elems, 0, length);
	}
}

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
void JSort<T, CONT, JSortType::QuickSort>::Sort(CONT<T>& elems, int begin_, int end_)
{
	if (begin_ >= end_) return;
	T pivot = elems[end_];
	int pos = begin_ - 1;

	for (int i = begin_; i < end_; ++i)
	{
		if (elems[i] < pivot) {
			std::swap(elems[i], elems[++pos]);
		}
	}

	std::swap(elems[++pos], elems[end_]);

	JSort<T, CONT, JSortType::QuickSort> A;
	A.Sort(elems, begin_, pos - 1);
	A.Sort(elems, pos + 1, end_);
}

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
void JSort<T, CONT, JSortType::MergeSort>::Sort(CONT<T>& elems, int begin_, int end_)
{
	if (begin_ >= end_) return;
	int medium_ = (begin_ + end_) / 2;
	JSort<T, CONT, JSortType::MergeSort> A;
	A.Sort(elems, begin_, medium_);
	A.Sort(elems, medium_ + 1, end_);
	Merge(elems, begin_, medium_, end_);
}