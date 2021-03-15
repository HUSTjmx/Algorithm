#include<iostream>
#include<vector>
#include<array>
#include <algorithm>
#include <stack>
using namespace std;

// ��ӡ����
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


class MyHashSet {
public:
	
	int HashSet[10000];
	int EmptySet[10000];
	int zs = 89;
	int num = 0;
	/** Initialize your data structure here. */
	MyHashSet() {
		for (int i = 0;i < 10000;i++)
			HashSet[i] = INT_MIN;

	}

	void add(int key) {
		int pos = key % zs;
		int i = 1;
		while (EmptySet[pos] != 0 && HashSet[pos] != key)
		{
			pos += (i * i);
			pos = pos % 10000;
			i++;
		}
		if (HashSet[pos] != key)
		{
			HashSet[pos] = key;
			EmptySet[pos] = 1;
			num++;
		}
	}

	void remove(int key) {
		int pos = key % zs;
		int i = 1;
		while (HashSet[pos] != key)
		{
			pos += (i * i);
			pos = pos % 10000;
			i++;
		}
		HashSet[pos] = INT_MIN;
		EmptySet[pos] = 0;
		num--;
	}

	/** Returns true if this set contains the specified element */
	bool contains(int key) {
		int pos = key % zs;
		int i = 1;
		while (HashSet[pos] != key && i <= num)
		{
			pos += (i * i);
			pos = pos % 10000;
			i++;
		}
		if (HashSet[pos] != key)return true;
		else return false;

	}
};

class Solution {
public:


	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0)return NULL;
        TreeNode* root = new TreeNode(preorder[0]);
        vector<int> La, Lb, Ra, Rb;
        int pos = -1;
        for (int i = 0;i < inorder.size();i++)
        {
            if (inorder[i] == preorder[0]) {
                pos = i;
                break;
            }
            La.push_back(inorder[i]);
        }

        for (int i = pos + 1;i < inorder.size();i++)
        {
            Lb.push_back(inorder.size());
        }

        for (int i = 1;i < 1 + pos;i++)
        {
            Ra.push_back(preorder[i]);
        }

        for (int i = 1 + pos;i < preorder.size();i++)
        {
            Rb.push_back(preorder[i]);
        }

        root->left = buildTree(La, Ra);
        root->right = buildTree(Lb, Rb);
        return root;
	}

    //452
	bool cmp(const vector<int>& a, const vector<int>& b)
	{
		return a[0] < b[0];
	}
    int id = 0;
	int findMinArrowShots(vector<vector<int>>& points) {


		if (points.size() <= 1)return points.size();
		int pos = 0;
		double min_start = (double)INT_MAX + 1;
		double a = (double)INT_MIN - 1, b = (double)INT_MIN - 1;
		int size = points.size();

		sort(points.begin(), points.end(), cmp);

		for (int j = 0;j < size;j++)
		{
			if (points[j][0] <= b)
			{
				if (b > points[j][1])
					b = points[j][1];
			}
			else
			{
				b = points[j][1];
				id++;
			}
			a = points[j][0];
		}
		return id;
	}

    //621
	bool cmp2(const int& a, const int& b)
	{
		return a < b;
	}
	
	int findContentChildren(vector<int>& g, vector<int>& s) {
		sort(g.begin(), s.end(), cmp2);
		sort(s.begin(), s.end(), cmp2);

		int p = 0, q = 0;
		int num = 0;

		while (p < g.size())
		{
			while (q < s.size())
			{
				if (s[q] >= g[p])
				{
					num++;
					q++;
					break;
				}
				q++;
			}
			p++;
		}
		return num;
	}

	
	string predictPartyVictory(string senate) {
		int R = 0, D = 0;
		vector<int> Power(senate.size(), 1);
		do {
			for (int i = 0;i < senate.size();i++)
			{
				if (Power[i] == 1)
				{
					if (senate[i] == 'D')
					{
						if (R > 0)
						{
							R--;
							Power[i] = 0;
						}
						else D++;
					}
					if (senate[i] == 'R')
					{
						if (D > 0)
						{
							D--;
							Power[i] = 0;
						}
						else R++;
					}
				}
			}
		} while (R != 0 && D != 0);

		if (R == 0)return "Dire";
		else return "Radiant";
	}


	string removeDuplicates(string S) {
		if (S.length() <= 1)return S;



		stack<char> st;

		for (int i = 0;i < S.length() - 1;i++)
		{
			if (S[i] == S[i + 1])
				i++;
			else
			{
				if (!st.empty() && st.top() == S[i])
				{
					st.pop();
				}
				else
				{
					st.push(S[i]);
				}
			}
		}

		if (!st.empty() && st.top() == S[S.length() - 1])
			st.pop();
		else
			st.push(S[S.length() - 1]);

		string result;

		while (!st.empty())
		{
			result += st.top();
			st.pop();
		}

		reverse(result.begin(), result.end());
		
		return result;
	}

	string longestPalindrome(string s) {
		if (s.size() <= 1)return s;

		vector<vector<int>> dp(s.length(), vector<int>());
		for (int i = 0;i < s.length();i++)
		{
			dp[i].resize(s.length());
			dp[i][i] = 1;
		}

		int L=0, R=0;
		int max = 1;

		for (int i = 1;i < s.length();i++)
		{
			for (int j = i - 1;j >= 0;j--)
			{
				if (s[i] == s[j])
				{
					if (i - 1 < j + 1 || dp[i - 1][j + 1])
					{
						dp[i][j] = 1;
						if (max < i - j + 1)
						{
							max = i - j + 1;
							L = j;
							R = i;
						}
					}
				}
			}
		}

		return s.substr(L, R);

	}


	int jump(vector<int>& nums) {
		int pos = 0;
		int times = 0;
		while (pos < nums.size() - 1)
		{
			int max = 0;
			for (int i = pos + 1;i <= pos + nums[pos];i++)
			{
				if (i + nums[i] > max)max = i+nums[i];
			}
			pos += max;
			times++;
		}
		return times;
	}

	int uniquePaths(int m, int n) {
		vector<vector<int>> dp(m + 1, vector<int>());
		for (vector<int> a : dp)
		{
			a.resize(n + 1);
		}

		dp[1][0] = 1;

		for (int i = 1;i <= m;i++)
		{
			for (int j = 1;j <= n;j++)
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m][n];

	}

	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		vector<vector<int>> dp(obstacleGrid.size() + 1, vector<int>(obstacleGrid[0].size() + 1, 0));
		dp[1][0] = 1;

		for (int i = 1;i <= obstacleGrid.size();i++)
		{
			for (int j = 1;j <= obstacleGrid[0].size();j++)
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				if (obstacleGrid[i - 1][j - 1] == 1)dp[i][j] = 0;
			}
		}
		return dp[obstacleGrid.size()][obstacleGrid[0].size()];
	}
	#define  MY_MAX(A,B) A>B?B:A
	int minPathSum(vector<vector<int>>& grid) {
		vector<vector<int>> dp(grid.size() + 1, vector<int>(grid[0].size() + 1, 0));

		for (int i = 1;i <= grid.size();i++)
		{
			for (int j = 1;j <= grid[0].size();j++)
			{
				dp[i][j] = grid[i - 1][j - 1] + MY_MAX(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		return dp[grid.size()][grid[0].size()];
	}
	int maxV(vector<int>& prices, int fee, int L, int R)
	{
		if (R <= L)return 0;
		int max = 0;
		int R_pos = 0;

		for (int i = L;i <= R;i++)
		{
			if (prices[i] > max)
			{
				max = prices[i];
				R_pos = i;
			}
		}

		int min = INT_MAX;
		int L_pos = 0;
		for (int i = 0;i < R_pos - 1;i++)
		{
			if (min < prices[i])
			{
				min = prices[i];
				L_pos = i;
			}
		}

		int v = max - min - fee;
		if (v < 0)return maxV(prices, fee, R_pos + 1, R);
		return v + maxV(prices, fee, L, L_pos - 1) + maxV(prices, fee, R_pos + 1, R);
	}

	int maxProfit(vector<int>& prices, int fee) {
		return maxV(prices, fee, 0, prices.size() - 1);
	}

};


void main()
{
    Solution* a = new Solution();
    vector<int> list = { 1,3,1,4 };
	int b = a->uniquePaths(3, 4);
	cout << b << endl;
}