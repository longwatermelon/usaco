#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}};
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}};
#define PTX x
#define PTY y
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

const int N=5e4;
int n;
pt_t c[N+1];

pair<int,int> prex[N+1], sufx[N+2]; // pre extremes, suf extremes (min,max)

// return max area saved
ll solve() {
    sort(c+1,c+1+n,[](pt_t a, pt_t b){return a.x==b.x ? a.y<b.y : a.x<b.x;});

    for (int i=1; i<=n; ++i) {
        prex[i].first=min(prex[i-1].first,c[i].y);
        prex[i].second=max(prex[i-1].second,c[i].y);
    }

    for (int i=n; i>=1; --i) {
        sufx[i].first=min(sufx[i+1].first,c[i].y);
        sufx[i].second=max(sufx[i+1].second,c[i].y);
    }

    ll ans=INT64_MAX;
    for (int i=1; i<=n; ++i) {
        ll prea=(ll)(prex[i].second-prex[i].first)*(c[i].x-c[1].x);
        ll sufa=(ll)(sufx[i+1].second-sufx[i+1].first)*(c[n].x-c[i+1].x);
        ans=min(ans,prea+sufa);
    }

    return (ll)(c[n].x-c[1].x)*(prex[n].second-prex[n].first) - ans;
}

signed main() {
    /* ios_base::sync_with_stdio(false); */
    /* cin.tie(NULL); */
    freopen("split.in","r",stdin);
    freopen("split.out","w",stdout);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>c[i].x>>c[i].y;
    prex[0]={INT_MAX,INT_MIN};
    sufx[n+1]={INT_MAX,INT_MIN};

    ll ans=solve();
    for (int i=1; i<=n; ++i) swap(c[i].x,c[i].y);
    ans=max(ans,solve());

    printf("%lld\n", ans);
}
