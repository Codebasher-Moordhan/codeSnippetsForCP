#include <bits/stdc++.h>
using namespace std;
// Range Minimum Query
class SGTree
{
    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, int arr[])
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    int query(int ind, int low, int high, int l, int r)
    {
        if (high < l || r < low)
            return INT_MAX;
        else if (l <= low && high <= r)
            return seg[ind];
        int mid = (low + high) / 2;
        return min(query(2 * ind + 1, low, mid, l, r), query(2 * ind + 2, mid + 1, high, l, r));
    }
    void update(int i, int low, int high, int ind, int val, int arr[])
    {
        if (low == high)
        {
            seg[i] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (ind <= mid)
            update(2 * i + 1, low, mid, ind, val, arr);
        else
            update(2 * i + 2, mid + 1, high, ind, val, arr);
        seg[i] = min(seg[2 * i + 1], seg[2 * i + 2]);
    }
};