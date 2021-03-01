#include<iostream>
#include<vector>
#include<array>

using namespace std;

// 打印数组
void PrintListInGreedy(vector<int> & list)
{
    for (int i = 0;i < list.size();i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
}

class Solution {
public:

    //983 数组形式的整数加法
    vector<int> addToArrayForm(vector<int>& A, int K) {
        int add = 0;
        int pos = A.size() - 1;
        vector<int> temp;

        while (K > 0 && pos >= 0)
        {
            int a = K % 10;
            temp.push_back((A[pos] + a + add) % 10);
            add = (A[pos] + a + add) / 10;
            K = K / 10;
            pos--;
        }

        while (K > 0)
        {
            temp.push_back((add + K % 10) % 10);
            add = (add + K % 10) / 10;
            K = K / 10;
        }

        while (pos >= 0)
        {
            temp.push_back((A[pos] + add) % 10);
            add = (add + A[pos]) / 10;
            pos--;
        }

        reverse(temp.begin(), temp.end());
        return temp;
    }

    //55 跳跃游戏
    bool canJump(vector<int>& nums) {
        if (nums.size() == 1)return true;
        int max_step = 0;
        for (int i = 0;i < nums.size();i++)
        {
            if (nums[i] == 0 && max_step <= i && i != nums.size() - 1)return false;
            if (i + nums[i] > max_step)max_step = i + nums[i];
        }
        return true;
    }

    //134 加油站
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = cost.size();
        int pos = -1;
        int temp = 0;
        int last_cost = 0;
        int start = -1;

        vector<int> piece_sum;

        for (int i = 0;i < len;i++)
        {
            gas[i] = gas[i] - cost[i];
            if (gas[i] < 0 && start < 0)start = (i + 1) % len;
        }
        if (start == -1)return 0;

        for (int i = 0;i < len;i++)
        {
            int j = (start + i) % len;
            if (gas[j] > 0 && temp == 0)
            {
                pos = j;
                if (pos != 0)last_cost = gas[i - 1];
                else last_cost = gas[len - 1];
            }
            temp += gas[i];
            if (temp < 0)
            {
                piece_sum.push_back(temp);
                temp = 0;
            }
        }
        
        for (int i = 0;i < piece_sum.size();i++)
        {
            temp += piece_sum[i];
            if (i != piece_sum.size() && temp < 0)return -1;
        }

        return pos;
    }

    //316
    int findMinPos(string s)
    {
        int pos = 0;
        char c = 'z';
        for (int i = 0;i < s.length();i++)
        {
            if (s[i] < c) {
                c = s[i];
                pos = i;
            }
        }
        return pos;
    }
    void solve(string& s)
    {
        if (s.length() < 2)return;
        int pos = findMinPos(s);
        string a = s.substr(0, pos);
        string b = s.substr(pos + 1, s.length() - pos - 1);
        cout << s <<":"<< a << " + " <<s[pos]<<" + "<< b << " " << endl;
        solve(a);
        solve(b);
        cout << s << ":" << a << " + " << s[pos] << " + " << b << " " << endl;
        while (b.find(s[pos]) != b.npos)
        {
            b.erase(b.find(s[pos]));
        }

        string temp = s[pos] + b;

        if (a.length() >= 1)
        {
            for (int i = a.length() - 1;i >= 0;i--)
            {
                if (temp.find(a[i]) == temp.npos)
                {
                    temp = a[i] + temp;
                }
                else if (a[i]<temp[0])
                {
                    temp.erase(temp.find(a[i]));
                    temp = a[i] + temp;

                }
            }
        }
        s = temp;
    }

    string removeDuplicateLetters(string s) {

        solve(s);

        return s;
    }

    //376 摆动序列
    int wiggleMaxLength(vector<int>& nums) {

        if (nums.size() <= 1)return nums.size();

        int key = 0;
        int sum = 0;

        for (int i = 1;i < nums.size();i++)
        {
            int temp = nums[i] - nums[i - 1] > 0 ? 1 : nums[i] - nums[i - 1] < 0 ? -1 : 0;

            if (temp == 0)
            {
                sum++;
            }

            else if (temp * key > 0)
            {
                sum++;
            }
            else
            {
                key = temp;
            }
        }

        return nums.size() - sum;
    }

    //402 移掉K位数字
    string removeKdigits(string num, int k) {
        if (num.length() <= k)return '0';
        if (k == 0)return num;

        for (int i = 0;i < num.size() - 1;i++)
        {
            if (k == 0)
            {
                result[i] += num[i];
            }
            else if (num[i] < num[i + 1]) {
                result += num[i];
            }
            else
            {
                k--;
            }
        }
        return result;
        
    }
    
};

void main()
{
    Solution* a = new Solution();
    vector<int> list = { 1,3,1,4 };
    string s = "abacb";
    string b=a->removeDuplicateLetters(s);
    cout << b << endl;
}