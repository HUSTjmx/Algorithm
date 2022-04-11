#include <vector>

// JMX
// #include "JSort.h" ����ζ������ʹ����ʾʵ����ģ��
// #include "JSortDef.h" ����ζ������ʹ�ð���ģ��
#include "JSortDef.h"
#include "JStream.h"


void main()
{
	JSort<int, std::vector, JSortType::MergeSort> A;
	std::vector<int> elems = { 10, 3, 2, 199, 34, 98, 732, 32 };
	A.Sort(elems, 0, elems.size() - 1);
	JIO::Instance().ListOutput(std::cout, elems);
}
