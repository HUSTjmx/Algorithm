#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include "JDesignPattern.h"

class JIO : public Singleton<JIO>
{
public:
	friend class Singleton<JIO>;

	template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
	std::ostream& ListOutput(std::ostream& os, CONT<T>& elems);

protected:
	JIO() {}
};

template<typename T, template<typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT>
std::ostream& JIO::ListOutput(std::ostream& os, CONT<T>& elems)
{
	os << "The list is [";
	
	int num = 1;

	auto func = [&num, &os](const T& elem) {
		os << " " << elem;
		if (num % 10 == 0) os << std::endl;
		num++;
	};

	std::for_each(elems.cbegin(), elems.cend(), func);

	os << " ]";

	return os;
}

