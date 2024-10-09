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
    root at 1, track how many bales each subtree needs
    for each vertex, sort adjacent ascending in order of need (extra --> not enough) to process subtrees in correct order (don't transfer bales we don't have)
    after processing each subtree, excess should end up at root which can be picked up by subtree parent and distributed to deficient vertices
*/

const int N=2e5;
int n;
ll h[N+1];

vec<int> adj[N+1];
ll need[N+1];
ll target;

void dfs_need(int u, int p) {
    need[u]=target-h[u];

    for (int v:adj[u]) {
        if (v==p) continue;
        dfs_need(v,u);
        need[u]+=need[v];
    }
}

struct mv_t {int u,v; ll cnt;};
void dfs(int u, int p, vec<mv_t> &ans) {
    for (int v:adj[u]) {
        if (v==p) continue;

        // tranfer for child's need
        if (need[v]>0) {
            ans.push_back({u,v,need[v]});
            h[u]-=need[v];
            h[v]+=need[v];
        }
        dfs(v,u,ans);

        // transfer extra to par
        if (h[v]>target) {
            ans.push_back({v,u,h[v]-target});
            h[u]+=h[v]-target;
            h[v]=target;
        }
    }
}

void solve() {
    target=accumulate(h+1,h+1+n,0ll)/n;
    dfs_need(1,0);

    // from extra to need
    for (int u=1; u<=n; ++u) {
        sort(all(adj[u]),[](int i, int j){return need[i]<need[j];});
    }
    vec<mv_t> ans;
    dfs(1,0,ans);

    printf("%d\n", sz(ans));
    for (auto &mv:ans) {
        printf("%d %d %lld\n", mv.u, mv.v, mv.cnt);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>h[i];
    for (int i=1; i<=n-1; ++i) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve();
}
