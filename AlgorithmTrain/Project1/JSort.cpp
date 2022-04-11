#include <vector>

// JMX
// #include "JSort.h" ：意味着我们使用显示实例化模型
// #include "JSortDef.h" ：意味着我们使用包含模型
#include "JSortDef.h"
#include "JStream.h"


void main()
{
	JSort<int, std::vector, JSortType::MergeSort> A;
	std::vector<int> elems = { 10, 3, 2, 199, 34, 98, 732, 32 };
	A.Sort(elems, 0, elems.size() - 1);
	JIO::Instance().ListOutput(std::cout, elems);
}
