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
#define PTX a
#define PTY w
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

/*
    greedily push largest cow onto largest tower
    group towers by top weight (<=n towers)
*/

const int N=2e5;
int n,m,k;
pt_t c[N+1];

void solve() {
    sort(c+1,c+1+n,[](pt_t x,pt_t y){return x.w>y.w;});
    map<int,int> cnt; // number of towers with weight
    set<int,greater<int>> s; // tower weights
    s.insert(INT_MAX);
    cnt[INT_MAX]=m;

    ll ans=0;
    for (int i=1; i<=n; ++i) {
        while (c[i].a>0) {
            int tw=*begin(s);
            if (tw<c[i].w+k) break; // tower not heavy enough

            int d=min(c[i].a,cnt[tw]);
            c[i].a-=d;
            cnt[tw]-=d;
            cnt[c[i].w]+=d;
            if (cnt[tw]==0) s.erase(begin(s));
            s.insert(c[i].w);
            ans+=d;
        }
    }

    printf("%lld\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>m>>k;
    for (int i=1; i<=n; ++i) cin>>c[i].w>>c[i].a;
    solve();
}
