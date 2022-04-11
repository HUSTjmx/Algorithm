#include<iostream>
#include<vector>
#include<array>
#include <algorithm>
#include <stack>
#include <map>
#include <array>
#include <utility>
#include <set>
using namespace std;

// ´òÓ¡Êý×é
void PrintListInGreedy(vector<int> & list)
{
    for (int i = 0;i < list.size();i++)
    {
        std::cout << list[i] << " ";
    }
	std::cout << endl;
}

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};


class LRUCache {
public:
	map<int, array<int, 2>> cache;
	int cap = 0;
	LRUCache(int capacity) {
		cap = capacity;
	}

	int get(int key) {
		if (cache.find(key) == cache.end())
			return -1;
		for (auto it = cache.begin(); it != cache.end(); it++)
		{
			it->second[1]++;
			//cout<<it->first<<" "<<it->second[1]<<endl;
		}
		cache[key][1] = -1;
		return cache[key][0];
	}

	void put(int key, int value) {
		cache[key] = { value,-1};

		int key2 = 0, max = -2;
		for (auto it = cache.begin(); it != cache.end(); it++)
		{
			if (it->second[1] > max)
			{
				max = it->second[1];
				key2 = it->first;
			}
			it->second[1]++;
		}

		if (cache.size() > cap)
		{
			cache.erase(key2);
		}
	}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = l1, *tail;
		int a = 0, b = 0;
		while (l1 != nullptr || l2!=nullptr)
		{
			b = a;
			if (l2 != nullptr)
			{
				a = (b + l2->val) / 10;
				b = (b + l2->val) % 10;
				l2 = l2->next;
			}
			if (l1 != nullptr)
			{
				a = a + (b + l1->val) / 10;
				b = (b + l1->val) % 10;
				tail = l1;
				l1->val = b;
				l1 = l1->next;
			}
			else {
				ListNode* c = new ListNode();
				c->val = b;
				tail->next = c;
				tail = c;
			}
		}
		if (a != 0)
		{
			ListNode* c = new ListNode();
			c->val = a;
			tail->next = c;
		}
		return head;
		
	}

	int lengthOfLongestSubstring(string s) {
		vector<char> a;
		int max = 0;
		for (char c : s)
		{
			auto it = find(a.begin(), a.end(), c);
			if (it != a.end())
			{
				max = max > a.size() ? max : a.size();
				a.erase(a.begin(), it);
				a.push_back(c);
			}
		}
		return max > a.size() ? max : a.size();
	}

	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = (nums1.size() + nums2.size()) / 2;
		int n = (nums1.size() + nums2.size()) % 2;
		int a = 0, b = 0;
		double x = 0, y = 0;
		for (int i = 0;i <= m;i++)
		{
			if (a < nums1.size())
			{
				x = y;
				y = nums1[a];
				a++;
			}
			if (b < nums2.size())
			{
				if (a >= nums1.size())
				{
					x = y;
					y = nums2[b];
					b++;
				}
				else if (nums2[b] < y)
				{
					y = nums2[b];
					b++;
					a--;
				}
			}
			if (y == nums1[nums1.size() - 1] && a == nums1.size())a++;
		}
		if (n == 1)return y;
		return (x + y) / 2;
	}

	int trap(vector<int>& height) {
		if (height.size() < 3)return 0;
		int L = 0, R = height.size() - 1;
		int r = 0;
		int b = 0;
		for (int i = 1;i < height.size();i++)
		{
			if (height[i] >= height[L])
			{
				r = r + (i - L - 1) * height[L] - b;
				L = i;
				b = 0;
			}
			else {
				b += height[i];
			}
		}
		b = 0;
		for (int i = height.size() - 2;i >= 0;i--)
		{
			if (height[i] >= height[R])
			{
				r = r + (R - i - 1) * height[R] - b;
				R = i;
				b = 0;
			}
			else{
				b += height[i];
			}
		}
		return r;

	}

	vector<int> twoSum(vector<int>& nums, int target) {
		map<int,int> a;
		vector<int> r;
		for (int i = 0;i < nums.size();i++)
		{
			if (a.size() ==0 || a.find(target - nums[i]) != a.end())
			{
				r.push_back(a[target - nums[i]]);
				r.push_back(i);
				return r;
			}
			else a[target - nums[i]] = i;
		}
		return r;
	}
	void Surf(ListNode* &a, int k)
	{
		if (k == 0)return;
		Surf(a->next, k--);
		a->next->next = a;
	}
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode* h1= head;
		ListNode* temp = new ListNode;
		int L = k;
		temp->next = head;
		while (head != nullptr)
		{
			L--;
			if (L == 0)
			{
				ListNode* a = head->next;
				ListNode* b = temp->next;
				Surf(b, k - 1);
				b->next = a;
				temp->next = head;
				temp = b;
				L = k;
			}
			head = head->next;
		}
		return h1;
	}


	void Surf2(ListNode*& a, ListNode*& b)
	{
		if (a->next == nullptr)
		{
			b = a;
			return;
		}
		Surf2(a->next,b);
		a->next->next = a;
	}

	ListNode* reverseList(ListNode* head) {
		ListNode* p = head;
		Surf2(head,p);
		return p;
	}

	bool cmp(const int& a, const int& b)
	{
		return a < b;
	}

	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> dp(nums.size() + 1, vector<int>(nums.size() + 1, 0));
		vector<vector<int>> a;
		for (int i = 1;i <= nums.size();i++)
			dp[i][0] = nums[i - 1];
		for (int i = 1;i <= nums.size();i++)
			for (int j = 1;j <= nums.size();j++)
			{
				if (i == j)continue;
				dp[i][j] = dp[i][0] + nums[j - 1];
				auto it = find(nums.begin(), nums.end(), -1 * dp[i][j]);
				int p = it - nums.begin();
				if (it != nums.end() && p != i && p != j)
				{
					vector<int> temp{ nums[i - 1],nums[j - 1],*it };
					sort(temp.begin(), temp.end(), cmp);
					if (find(a.begin(), a.end(), temp) == a.end())
						a.push_back(temp);
				}
			}
	}

	int maxArea(vector<int>& height) {
		int max = 0;
		int temp = 0;
		for(int i=0;i<height.size()-1;i++)
			for (int j = height.size() - 1;j > i;j--)
			{
				if (height[j] >= height[i])
				{
					temp = (j - i) * height[i];
					max = max > temp ? max : temp;
					break;
				}
			}

		for(int i=height.size()-1;i>0;i--)
			for (int j = 0;j < i;j++)
			{
				if (height[j] > height[i])
				{
					temp = (i - j) * height[i];
					max = max > temp ? max : temp;
					break;
				}
			}
		
		return max;

	}

	void Search(TreeNode* tree, vector<int>& a, int n)
	{
		if (a.size() <= n)a.push_back(tree->val);
		if(tree->right!=nullptr)
			Search(tree->right, a, n + 1);
		if (tree->left != nullptr)
			Search(tree->left, a, n + 1);
	}

	vector<int> rightSideView(TreeNode* root) {
		vector<int> r;
		Search(root, r, 0);
		return r;
	}

	int maxSubArray(vector<int>& nums) {
		if (nums.size() == 1)return nums[0];
		int L = nums[0], R = nums[0];
		int r = nums[0];
		for (int i = 1;i < nums.size();i++)
		{
			if (nums[i] >= 0)
			{
				R += nums[i];
				if (i == nums.size() - 1)r = r > R ? r : L;
			}
			else
			{
				if (nums[i] + R <= 0) {
					r = r > L ? r : L;
					R = 0;
				}
				else {
					L = R;
					R = R + nums[i];
				}
			}
		}
		r = r > L ? r : L;
		return r;
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* head = new ListNode;
		ListNode* p = head;

		while (l1 != nullptr || l2 != nullptr)
		{
			if (l1 != nullptr && l2 != nullptr)
			{
				if (l1->val > l2->val)
				{
					p->next = l2;
					l2 = l2->next;
				}
				else {
					p->next = l1;
					l1 = l1->next;
				}
			}
			else if (l1 != nullptr)
			{
				p->next = l1;
				l1 = l1->next;
			}
			else
			{
				p->next = l2;
				l2 = l2->next;
			}
			p = p->next;
		}
		return head;
	}

	void Swap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = a;
	}
	void nextPermutation(vector<int>& nums) {
		int pos = 0;
		for (int i = nums.size();i > 0;i--)
		{
			if (nums[i] > nums[i - 1])
			{
				pos = i - 1;
				break;
			}
		}
		for(int i=nums.size()-1;i>pos;i--)
		{
			if (nums[i] > nums[pos]) {
				Swap(nums[pos], nums[i]);
				break;
			}
		}
		sort(nums.begin() + pos + 1, nums.end());
	}

};

int main()
{
	Solution a;
	return 1;
	
}