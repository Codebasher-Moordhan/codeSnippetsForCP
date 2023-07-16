#include <bits/stdc++.h>
using namespace std;
class DSU
{
    vector<int> par, rank, size;

public:
    DSU(int n)
    {
        rank.resize(n + 1, 0);
        par.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i < n; i++)
        {
            par[i] = i;
            size[i] = 1;
        }
    }
    int findUPar(int node)
    {
        if (node == par[node])
            return node;
        return par[node] = findUPar(par[node]); // Path Compression Method
    }
    void UnionByRank(int u, int v)
    {
        int up_u = findUPar(u), up_v = findUPar(v);
        if (up_u == up_v)
            return; // Smaller is connected to larger as less travel time for the nodes
        if (rank[up_u] < rank[up_v])
            par[up_u] = up_v;
        else if (rank[up_u] > rank[up_v])
            par[up_v] = up_u;
        else
        {
            par[up_u] = up_v;
            rank[up_v]++;
        }
    }
    void UnionBySize(int u, int v)
    {
        int up_u = findUPar(u), up_v = findUPar(v);
        if (up_u == up_v)
            return;
        if (size[up_u] < size[up_v])
        {
            par[up_u] = up_v;
            size[up_v] += size[up_u];
        }
        else
        {
            par[up_v] = up_u;
            size[up_u] += size[up_v];
        }
    }
};