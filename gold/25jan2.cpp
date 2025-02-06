#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

const int N=2e5;
int n,m;
int s[N+1];

vec<int> adj[N+1];
// dsu
vec<int> vt[N+1];
int id[N+1];

vec<int> mxv[N+1];
bool vis[N+1];

void dsu_init() {
    for (int u=1; u<=n; ++u) {
        vt[u]={u};
        id[u]=u;
    }
}

// return sizes of components which merged. {0,0} if already in same component.
pair<int,int> dsu_add_edge(int u, int v) {
    if (id[u]!=id[v]) {
        pair<int,int> res = {sz(vt[id[u]]), sz(vt[id[v]])};
        if (sz(vt[id[u]]) > sz(vt[id[v]])) {
            swap(u,v);
        }

        // merge u -> v
        int src=id[u];
        for (int x:vt[src]) {
            id[x]=id[v];
            vt[id[v]].push_back(x);
        }
        vt[src].clear();

        return res;
    }

    return {0,0};
}

// # pairs given cnt nodes
ll pairs(int cnt) {
    return (ll)cnt*(cnt-1)/2;
}

int dfs(int u, vec<int> &verts) {
    verts.push_back(u);
    if (s[u]==0) return u;
    if (vis[u]) return u;
    vis[u]=true;

    int mx=u;
    for (int v:adj[u]) {
        mx=max(mx,dfs(v,verts));
    }

    return mx;
}

// reconstruct graph backwards w/ dsu, compute ans along way. return ans
vec<ll> backward() {
    dsu_init();
    vec<bool> rm(n+1, true);
    ll cnt=0; // # pairs
    vec<ll> ans(n+1);

    for (int t=n; t>=1; --t) {
        rm[t]=false;

        // if (mxv[t]) {
        for (int v:mxv[t]) {
            assert(t<=v);
            pair<int,int> p = dsu_add_edge(t,v);
            cnt += pairs(p.first+p.second) - pairs(p.first) - pairs(p.second);
        }

        // remaining normal adj merges from original graph
        for (int u:adj[t]) {
            if (rm[u]) continue;

            // try merge w/ existing nodes
            pair<int,int> p = dsu_add_edge(t,u);
            cnt += pairs(p.first+p.second) - pairs(p.first) - pairs(p.second);
        }

        ans[t]=cnt;
    }

    return ans;
}

void solve() {
    for (int u=1; u<=n; ++u) {
        if (vis[u]) continue;

        if (s[u]==1) {
            vec<int> verts;
            int mx=dfs(u,verts);
            set<int> v2(all(verts));
            for (int v:v2) {
                mxv[v].push_back(mx);
            }
        }
    }

    vec<ll> ans = backward();

    for (int t=1; t<=n; ++t) {
        printf("%lld\n", ans[t]);
    }
}

signed main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    cin>>n>>m;
    for (int i=1; i<=n; ++i) {
        char c; cin>>c;
        s[i]=c-'0';
    }

    for (int i=1; i<=m; ++i) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int u=1; u<=n; ++u) {
        sort(all(adj[u]));
    }

    solve();
}
