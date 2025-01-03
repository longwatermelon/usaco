#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

const int N=5e4;
int n,m,c,r,k;
struct edge_t {int v,l;};
vec<edge_t> adj[N+1];

set<int> vis[N+1]; // u -> set of charging stations visited u
int cnt[N+1];
struct st_t {int u,src; ll sum;};

void solve() {
    auto cmp=[](st_t x, st_t y){return vec<ll>{x.sum, x.u, x.src} < vec<ll>{y.sum, y.u, y.src};};
    set<st_t, decltype(cmp)> pq(cmp);
    for (int u=1; u<=c; ++u) {
        pq.insert({u,u,0});
    }

    while (!empty(pq)) {
        st_t top=*begin(pq);
        pq.erase(begin(pq));
        int u=top.u, src=top.src; ll sum=top.sum;

        if (cnt[u]==k || vis[u].find(src)!=end(vis[u])) {
            continue;
        }

        cnt[u]++;
        vis[u].insert(src);

        for (edge_t e:adj[u]) {
            ll sump=sum+e.l; // sum'
            if (sump>r || cnt[e.v]==k) continue;
            pq.insert({e.v, src, sump});
        }
    }

    // ans
    vec<int> ans;
    for (int u=c+1; u<=n; ++u) {
        if (cnt[u]==k) {
            ans.push_back(u);
        }
    }

    printf("%d\n", sz(ans));
    for (int u:ans) printf("%d\n", u);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>m>>c>>r>>k;
    for (int i=1; i<=m; ++i) {
        int u,v,l; cin>>u>>v>>l;
        adj[u].push_back({v,l});
        adj[v].push_back({u,l});
    }

    solve();
}
