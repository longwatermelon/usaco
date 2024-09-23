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
#define PTY b
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

/*
    running sum difference array across k for # intervals
    create intervals [a_i+a_j, b_i+b_j] and find # intervals each k is in
    for interval [a_i+a_j, b_i+b_j], there are freq(a_i)*freq(a_j) ways to get left endpoint, freq(b_i)*freq(b_j) ways to get the right endpoint.
*/

const int N=2e5;
int n,m;
pt_t in[N+1];

void solve() {
    vec<ll> fa(m+1),fb(m+1);
    for (int i=1; i<=n; ++i) {
        fa[in[i].a]++;
        fb[in[i].b]++;
    }

    vec<ll> d(2*m+2);
    for (int x=0; x<=m; ++x) {
        for (int y=0; y<=m; ++y) {
            d[x+y]+=fa[x]*fa[y];
            d[x+y+1]-=fb[x]*fb[y];
        }
    }

    ll ans=0;
    for (int k=0; k<=2*m; ++k) {
        ans+=d[k];
        printf("%lld\n", ans);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>m;
    for (int i=1; i<=n; ++i) cin>>in[i].a>>in[i].b;
    solve();
}
