/*贪心算法*/
//排队打水问题分析
/*
有n个人排队到r个水龙头前去打水，他们装满水桶的时间分别为t1，t2，t3···，tn，打水时间均为整数且各不相等，应该如何安排他们的打水顺序才能使他们话费的总时间最少
每个人打水时间=排队时间+装满水时间
（假设排队切换等其他过程均不耗费时间）
要求程序：
输入：有两行，第一行为两个整数，分别是n和r，即人数和水龙头数（1<=n<=500)(1<=r<=100)
第二行为n个整数t1，t2，t3，···，tn（1<=ti<=1000).百诺是每个人装满水桶的时间
输出：1行，一个正整数，表示他们花费的最少总时间
*/
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    int a[510] = {0};
    int a,r,n,s = 0;
    cin >> n >> r;
    for ( int i = 0; i <= n; i++)
    {
        cin >> a[i];
    }
    sort(a+1,a+n+1);
    for ( i = 0; i <= n; i++)
    {
        if (i>=r+1)
        {
            a[i] = a[i] + a[i-r];
        }
        s = s + a[i];
    }
    cout << s;
    return 0;
}
//练习
/*
N为旅行者在夜里过桥需要借助手电筒。但N个人中只有一个手电筒，而且过桥同时只能让两人过，
每个人单独过桥所需时间已知，但如果两个人同时过桥则所需时间是走得慢点那个人单独过桥所需时间
设计一个方案，让这N个人尽快过桥，计算这个N个人过桥最短时间
比如：有甲乙丙丁四个人，他们过河所需时间分别是1，2，5，10
让最快的2个人先过桥，然后让跑的最快的人回去接剩下的人
先让甲乙过去（2分钟），甲回来（1分钟），甲丙过去（5分钟）
甲回来（1分钟），甲丁过去（10分钟），总共需要19分钟
输入：第一行N（表示有N个人要过河）
     第二行是N个整数S，表示这N个人过河所需时间（0<S<100)
输出：所有人过河的最短时间
样例输入：4
        1 2 5 10
样例输出：17
*/
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//函数计算所有人过桥的最短时间
int shortestTinme(int n, vector<int>& times){
    //将vector times排序
    sort(times.begin(), times.end());
    //变量用于储存所有人过桥的总时间
    int totalTime = 0;

    //贪心策略：选择最优的成对过桥
    while (n > 3)
    {
        //计算两个不同选择的时间
        int option1 = times[0] + 2 * times[1] + times[n - 1];
        int option2 = 2 * times[0] + times[n - 2] + times[n - 1];
        //选择较小时间的选项并且累加总时间
        totalTime += min(option1, option2);
        //调整剩余人数
        n -= 2;
    }
    //根据总人数剩余情况处理剩下的人（2或者3人）
    if (n == 2)
    {
        totalTime += times[1];
    }
    else if (n == 3)
    {
        totalTime += times[0] + times[1] + times[2];
    }
    //返回计算出的总时间
    return totalTime;
}
int main(){
    //输入人数和各自所需时间
    int n;
    cin >> n;

    vector<int> times(n);
    for (int i = 0; i < n; i++)
    {
        cin >> times[i];
    }
    //调用函数计算出最短时间
    int result = shortestTinme(n, times);
    cout << result << endl;

    return 0;
}