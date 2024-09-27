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
struct pt_t {int x,y,t;};

const int G=1e5, N=1e5;
int n,g;
pt_t a[G+1], b[N+1];

ll dist(ll x1, ll y1, ll x2, ll y2) {
    ll dx=x1-x2, dy=y1-y2;
    return dx*dx + dy*dy;
}

void solve() {
    sort(a+1,a+1+g,[](pt_t x, pt_t y){return x.t<y.t;});
    sort(b+1,b+1+n,[](pt_t x, pt_t y){return x.t<y.t;});

    int l=0, ans=0;
    for (int i=1; i<=n; ++i) {
        while (l<n && b[i].t>=a[l+1].t)
            l++;

        bool ok=false;
        if (l>0) {
            ll dprev=dist(a[l].x,a[l].y,b[i].x,b[i].y);
            ll dtprev=b[i].t-a[l].t;
            ok|=dprev>dtprev*dtprev;
        }
        if (l<n) {
            ll dnxt=dist(a[l+1].x,a[l+1].y,b[i].x,b[i].y);
            ll dtnxt=a[l+1].t-b[i].t;
            ok|=dnxt>dtnxt*dtnxt;
        }

        ans+=ok;
    }

    printf("%d\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>g>>n;
    for (int i=1; i<=g; ++i) cin>>a[i].x>>a[i].y>>a[i].t;
    for (int i=1; i<=n; ++i) cin>>b[i].x>>b[i].y>>b[i].t;
    solve();
}
