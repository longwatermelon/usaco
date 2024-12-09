#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

// graph vertices 1..n
// v[i]=component i's vertices
// g[u]=ind of graph that vert u is in
void dsumk(int n, vec<vec<int>> &vt, vec<int> &id) {
    vt=vec<vec<int>>(n+1);
    id=vec<int>(n+1);

    for (int u=1; u<=n; ++u) {
        vt[u]={u};
        id[u]=u;
    }
}

// update dsu w/ edge u<->v
void dsuup(int u, int v, vec<vec<int>> &vt, vec<int> &id) {
    if (id[u]!=id[v]) {
        if (sz(vt[id[u]])>sz(vt[id[v]])) {
            swap(u,v);
        }

        // merge u to v
        int src=id[u];
        for (int x:vt[src]) {
            id[x]=id[v];
            vt[id[v]].push_back(x);
        }
        vt[src].clear();
    }
}

int n,m;

vec<vec<int>> vt;
vec<int> id;

// min cost to connect components x,y
ll mncost(int x, int y) {
    if (sz(vt[x])>sz(vt[y])) {
        swap(x,y);
    }

    vt[y].push_back(1e6);
    vec<int> &a=vt[x], &b=vt[y];
    ll ans=INT64_MAX;
    for (int j=0; j<sz(a); ++j) {
        int lo=-1, hi=sz(b)-1;
        while (lo+1<hi) {
            int i=(lo+hi)/2;
            if (b[i]<=a[j]) lo=i;
            else hi=i;
        }

        ans=min(ans, (ll)min(lo==-1 ? (int)1e6 : a[j]-b[lo], b[lo+1]-a[j]));
    }
    vt[y].pop_back();

    return ans*ans;
}

void solve() {
    for (int i=1; i<=n; ++i) {
        sort(all(vt[i]));
    }

    // id[1]->id[n]
    ll ans=mncost(id[1], id[n]);

    // id[1]->x->id[n]
    for (int x=1; x<=n; ++x) {
        if (x==id[1] || x==id[n] || empty(vt[x])) continue;

        ll cost=mncost(id[1],x) + mncost(x,id[n]);
        ans=min(ans,cost);
    }

    // ans
    printf("%lld\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin>>t;
    while (t--) {
        cin>>n>>m;
        dsumk(n,vt,id);

        for (int i=1; i<=m; ++i) {
            int u,v; cin>>u>>v;
            dsuup(u,v,vt,id);
        }

        solve();
    }
}
