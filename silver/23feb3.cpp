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
struct edge_t {int v; ll t0,t1;};

/*
    dfs on earliest edge by end time for each adjacent vertex
    don't dfs if can't get to edge faster than already tracked
    **optimization to pass tc 14-20**: sort edges in descending order by start time for early break in adjacency list loop
*/

const int N=2e5;
int n,m;
int a[N+1];
vec<edge_t> adj[N+1];

vec<ll> dp; // vec(n+1)

void dfs(int u, ll t) {
    set<int> s; // fringe
    for (edge_t e:adj[u]) {
        if (t<=e.t0) {
            if (e.t1<dp[e.v]) {
                dp[e.v]=min(dp[e.v], e.t1);
                s.insert(e.v);
            }
        } else {
            break;
        }
    }

    for (int v:s) {
        dfs(v, dp[v]+a[v]);
    }
}

void solve() {
    dp=vec<ll>(n+1,INT64_MAX);
    dp[1]=0;
    dfs(1,0);

    for (int i=1; i<=n; ++i) {
        printf("%lld\n", dp[i]==INT64_MAX?-1:dp[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>m;
    for (int i=1; i<=m; ++i) {
        int u,t0,v,t1; cin>>u>>t0>>v>>t1;
        adj[u].push_back({v,t0,t1});
    }
    for (int i=1; i<=n; ++i) {
        sort(all(adj[i]), [](edge_t x, edge_t y){return x.t0>y.t0;});
    }

    for (int i=1; i<=n; ++i) cin>>a[i];
    solve();
}
