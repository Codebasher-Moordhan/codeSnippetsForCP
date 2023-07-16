#include <bits/stdc++.h>
using namespace std;
//Range Sum Query
class SGLazy{
    public:
    vector<int> seg,lazy;
    SGLazy(int n){
        seg.resize(4*n+1),lazy.resize(4*n+1,0);
    }
    void build(int in,int low,int high,int arr[]){
        if(low==high){
            seg[in]=arr[low];
            return;
        }
        int mid=(low+high)/2;
        build(2*in+1,low,mid,arr),build(2*in+2,mid+1,high,arr);
        seg[in]=seg[2*in+1]+seg[2*in+2];
    }
    void updateRange(int in,int low,int high,int l,int r,int val){
        if(lazy[in]!=0){
            seg[in]+=(high-low+1)*lazy[in];
            //If no children, then the range will be (a,a), hence no propagation
            //If there are children , then the limit will be (a,b), hence propagation occurs downwards
            if(low!=high) lazy[2*in+1]+=lazy[in],lazy[2*in+2]+=lazy[in];
            lazy[in]=0;
        }
        if(high<l||r<low) return;
        if(l<=low&&r>=high){
            seg[in]+=(high-low+1)*val;
            if(low!=high) lazy[2*in+1]+=val,lazy[2*in+2]+=val;
            return;
        }
        int mid=(low+high)>>1;
        updateRange(2*in+1,low,mid,l,r,val),updateRange(2*in+2,mid+1,high,l,r,val);
        seg[in]=seg[2*in+1]+seg[2*in+2];
    }       
    int query(int in,int low, int high, int l,int r){
        //Same as update
        if(lazy[in]!=0){
            seg[in]+=(high-low+1)*lazy[in];
            //If no children, then the range will be (a,a), hence no propagation
            //If there are children , then the limit will be (a,b), hence propagation occurs downwards
            if(low!=high) lazy[2*in+1]+=lazy[in],lazy[2*in+2]+=lazy[in];
            lazy[in]=0;
        }
        if(high<l||r<low) return 0;
        if(l<=low&&r>=high) return seg[in];
        int mid=(low+high)>>1;
        query(2*in+1,low,mid,l,r),query(2*in+2,mid+1,high,l,r);
        return seg[2*in+1]+seg[2*in+2];
    }
};