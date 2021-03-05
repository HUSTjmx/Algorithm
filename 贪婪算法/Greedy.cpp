#include<iostream>
#include<vector>
#include<array>
#include <algorithm>
using namespace std;

// ´òÓ¡Êý×é
void PrintListInGreedy(vector<int> & list)
{
    for (int i = 0;i < list.size();i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
}

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
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
		return a > b;
	}
	int leastInterval(vector<char>& tasks, int n) {
		vector<int> list(26, 0);
		vector<int> start(n, 0);

		for (int i = 0;i < tasks.size();i++)
		{
			list[tasks[i] - 'A']++;
		}
		sort(list.begin(), list.end(), cmp2);


		for (int i = 0;i < n;i++)
			start[i] = i;

		int id = 1;
		int pos = -1;
		int fx = 1;
		for (int i = 0;i < 26;i++)
		{
			if (list[i] == 0)break;
			start[0] = start[0] + list[i] * n + 1;
			sort(start.begin(), start.end(), cmp2);
			//cout << pos << ":" << pos << endl;
		}

		sort(start.begin(), start.end(), cmp2);

		return start[0] - 1;
	}
};



void main()
{
    Solution* a = new Solution();
    vector<vector<int>> list = { {1,3},{1,4} };
    int b = a->findMinArrowShots(list);
    cout << b << endl;
}