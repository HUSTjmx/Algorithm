#include<iostream>
#include<vector>
#include<array>

using namespace std;

//打印数组
void PrintListInSort(vector<int>& list)
{
	for (int i = 0;i < list.size();i++)
	{
		cout << list[i] << " ";
	}
	cout << endl;
}

//交换元素
void SwapByIndex(vector<int>& list, int i, int j)
{
	if (i < 0 || j < 0 || j >= list.size() || i >= list.size()) {
		cout << "error,out of index" << endl;
		return;
	}

	int temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}

//冒泡排序
void BubbleSort(vector<int>& list)
{
	for (int i = 0;i < list.size() - 1;i++)
	{
		for (int j = 0;j < list.size() - i - 1;j++)
		{
			int temp = list[j];
			if (list[j] > list[j + 1])
			{
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

//选择排序
void SelectionSort(vector<int>& list)
{
	for (int i = 0;i < list.size() - 1;i++)
	{
		int id = i;
		for (int j = i;j < list.size();j++)
		{
			if (list[j] < list[id])id = j;
		}
		int temp = list[i];
		list[i] = list[id];
		list[id] = temp;
	}
}

//插入排序
void InsertSort(vector<int>& list)
{
	if (list.size() <= 1)return;

	for (int i = 0;i < list.size() - 1;i++)
	{
		for (int j = i + 1;j >= 1;j--)
		{
			if (list[j] < list[j - 1])
			{
				int temp = list[j];
				list[j] = list[j - 1];
				list[j - 1] = temp;
			}
		}
	}
}

//希尔排序
void ShellSort(vector<int>& list)
{
	if (list.size() <= 1)return;
	for (int gap = list.size() / 2;gap > 0;gap = gap / 2)
	{
		for (int i = gap;i < list.size();i++)
		{
			int j = i;
			int temp = list[i];
			while (j - gap >= 0 && temp < list[j - gap])
			{
				list[j] = list[j - gap];
				j = j - gap;
			}
			list[j] = temp;
		}
	}
}

//归并排序
void Merge(vector<int>& list, int head, int tail)
{
	int middle = (head + tail) / 2;
	vector<int> temp;
	int a = head;
	int b = middle + 1;

	while (a <= middle && b <= tail)
	{
		if (list[a] <= list[b])
		{
			temp.push_back(list[a]);
			a++;
		}
		else {
			temp.push_back(list[b]);
			b++;
		}
	}

	while (a <= middle)
	{
		temp.push_back(list[a]);
		a++;
	}

	while (b <= tail)
	{
		temp.push_back(list[b]);
		b++;
	}

	for (int i = 0;i <= tail - head;i++)
	{
		list[head + i] = temp[i];
	}

}
void MergeSort(vector<int>& list,int head,int tail)
{
	if (head >= tail)return;
	int middle = (head + tail) / 2;
	MergeSort(list, head, middle);
	MergeSort(list, middle + 1, tail);
	Merge(list, head, tail);
}

//快速排序
void QuickSort(vector<int>& list, int head, int tail)
{
	if (head >= tail)return;

	int pivot = tail; //基准这里直接设置为末尾元素
	int a = -1;

	for (int i = 0;i <= tail - 1;i++)
	{
		if (list[i] < list[pivot])
		{
			SwapByIndex(list, i, ++a);
		}
	}

	SwapByIndex(list, ++a, pivot);
	QuickSort(list, head, a - 1);
	QuickSort(list, a + 1, tail);
}

//堆排序
void Heapify(vector<int>& list, int root,int length)
{
	int left = 2 * root + 1;
	int right = 2 * root + 2;
	int largest = root;
	int len = length;

	if (left<len && list[left] > list[largest])
	{
		largest = left;
	}

	if (right<len && list[right]>list[largest])
	{
		largest = right;
	}

	if (largest != root)
	{
		SwapByIndex(list, root, largest);
		Heapify(list, largest,len);
	}
}
void HeapSort(vector<int>& list)
{
	int len = list.size();
	for (int i = list.size() / 2;i >= 0;i--)
	{
		Heapify(list, 0, len);
	}
	for (int i = list.size() - 1;i > 0;i--)
	{
		SwapByIndex(list, 0, i);
		len--;
		Heapify(list, 0, len);
	}

}

//计数排序
void CountingSort(vector<int>& list)
{
	array<int, 10000> box = {0};
	for (int i = 0;i < list.size();i++)
	{
		box[list[i]]++;
	}

	int j = 0;
	for (int i = 0;i < box.size();i++)
	{
		while (box[i]-- > 0)list[j++] = i;
	}
}

//桶排序，默认桶数是3
#define BUCKET_NUM 3
void BucketSort(vector<int>& list)
{
	int max = list[0], min = list[0];
	for (int i = 0;i < list.size();i++)
	{
		if (list[i] > max)max = list[i];
		if (list[i] < min)min = list[i];
	}
	int level = (max - min) / BUCKET_NUM;

	array<vector<int>, BUCKET_NUM> buckets;
	for (int i = 0;i < BUCKET_NUM;i++)
	{
		buckets[i].clear();
	}

	for (int i = 0;i < list.size();i++)
	{
		int index = (list[i] - min) / level;
		if (index >= BUCKET_NUM)index = BUCKET_NUM - 1;
		buckets[index].push_back(list[i]);
	}
	for (int i = 0;i < BUCKET_NUM;i++)
	{
		CountingSort(buckets[i]);
	}
	for (int i = 1;i < BUCKET_NUM;i++)
	{
		buckets[0].insert(buckets[0].end(), buckets[i].begin(), buckets[i].end());
	}

	list = buckets[0];
}

//基数排序
#define RADIX 10
void RadixSort(vector<int>& list)
{
	int max = list[0];
	for (int i = 0;i < list.size();i++)
	{
		if (list[i] > max)max = list[i];
	}

	int b_num = 0,temp = max;

	while (temp > 0) {
		temp = temp / RADIX;
		b_num++;
	}

	array<vector<int>, RADIX> buckets;

	int d = 1;
	for (int i = 0;i < b_num;i++)
	{
		for (int j = 0;j < list.size();j++)
		{
			int a = (list[j] / d) % RADIX;
			buckets[a].push_back(list[j]);
		}

		for (int i = 1;i < RADIX;i++)
		{
			buckets[0].insert(buckets[0].end(), buckets[i].begin(), buckets[i].end());
		}

		list = buckets[0];

		for (int i = 0;i < RADIX;i++)buckets[i].clear();

		d *= RADIX;
		PrintListInSort(list);
	}
}

//void main()
//{
//	vector<int> list = { 5,44,21,554,1111,4,0};
//	
//	//BubbleSort(list);
//	
//	//SelectionSort(list);
//
//	//InsertSort(list);
//
//	//ShellSort(list);
//
//	//MergeSort(list, 0, list.size() - 1);
//
//	//QuickSort(list, 0, list.size() - 1);
//
//	//HeapSort(list);
//
//	//CountingSort(list);
//
//	//BucketSort(list);
//
//	RadixSort(list);
//
//	PrintListInSort(list);
//}