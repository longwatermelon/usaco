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

const int N=1e5;
int n,k,l;
int c[N+1];

void solve() {
    sort(c+1,c+1+n,greater<int>());
    vec<ll> pre(n+1);
    for (int i=1; i<=n; ++i) pre[i]=pre[i-1]+c[i];

    int ans=0, left=n;
    for (int i=1; i<=n; ++i) {
        while (c[left]<i) left--;

        if (c[i]>=i) {
            // no citations needed to reach h-index of i
            ans=max(ans,i);
        } else {
            // need citations
            ll cnt=ll(i)*(i-left)-(pre[i]-pre[left]);
            if (ll(k)*l>=cnt && k>=i-c[i]) {
                ans=i;
            } else {
                break;
            }
        }
    }

    printf("%d\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>k>>l;
    for (int i=1; i<=n; ++i) cin>>c[i];
    c[0]=INT_MAX;
    solve();
}
