#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> T cdiv(T a, T b) {return a/b+(sig(a)/sig(b)==1 && a%b);}
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}};
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}};
#define PTX x
#define PTY y
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

/*
    this solution still fails on some test cases


    optimal to milk in ascending order of a_i
    for each query, binary search to find new position k in sorted array
    casework (k<i and k>i)
*/

const int N=1.5e5;
int n;
ll a[N+1], p[N+1], s[N+1];

void solve(int i, ll j) {
    int lo=0, hi=n+1;
    while (lo+1<hi) {
        int k=(lo+hi)/2;
        if (a[k]>j) hi=k;
        else lo=k;
    }
    int k=lo;

    ll ans;
    if (k>i) {
        ans=p[i-1]+(p[k]-p[i])-(s[k]-s[i]) + j*k + p[n]-p[k];
    } else {
        ans=p[k] + j*(k+1) + (p[i-1]-p[k])+(s[i-1]-s[k]) + p[n]-p[i];
    }

    printf("%lld\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>a[i];
    a[0]=INT_MIN;
    vec<int> ord(n+1);
    for (int i=1; i<=n; ++i) ord[i]=i;
    sort(all1(ord),[](int i, int j){return a[i]<a[j];});
    vec<int> to(n+1);
    for (int i=1; i<=n; ++i) to[ord[i]]=i;

    sort(a+1,a+1+n);
    for (int i=1; i<=n; ++i) {
        p[i]=p[i-1] + a[i]*i;
        s[i]=s[i-1] + a[i];
    }

    int q; cin>>q;
    while (q--) {
        int i,j;
        cin>>i>>j;
        solve(to[i],j);
    }
}
