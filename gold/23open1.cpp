#include <bits/stdc++.h>
#define bool int
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> bool ckmin(T &a, T b) {return b<a ? a=b, true : false;}
template <typename T> bool ckmax(T &a, T b) {return b>a ? a=b, true : false;}

/*
    The key point here is that the reverse bfs (simulating exiting stalls) is
    the same as the forward bfs (simulating entering stalls).

    In reverse bfs, suppose we want to exit stall i. We must have collected a key
    of color c_i thus far and be able to be inside stall i at the same time, which means
    we can only consider key colors from stalls which we were able to exit from previously. Notice that
    we also can consider temporarily owning key color f_i for this check on stall i, since collecting
    the key in stall i allows us to own it while also being inside stall i afterwards.

    The bfs queue consists of the outermost stalls which are still exitable, while the fringe outside
    the queue consists of the stalls which we can enter but not exit out of (in context of the reverse
    process).

    *IMPORTANT*: In the reverse process, the only requirement for FJ to travel from stall i->j is that
    he can exit stall i, with no constraint regarding j.

    The forward process is requiring key color c_i to enter stall i, so the reverse process is requiring
    key color c_i to exit stall i. In the reverse process, the important part is being able to
    exit from the stall you just entered, rather than getting into the stall in the first place.
*/

int n,m;
vec<int> c,s,f;
vec<vec<int>> adj;

vec<bool> have,vis;

// compute have, vis
void bfs() {
    have.assign(n+1,false);
    vis.assign(n+1,false);

    queue<int> q;
    q.push(1);

    have[s[1]]=true;
    vis[1]=true;

    vec<vec<int>> defer(n+1);

    function<void(int)> visit = [&](int u) {
        if (have[c[u]]) {
            q.push(u);
            have[s[u]]=true;
            vis[u]=true;

            vec<int> ls=defer[s[u]];
            defer[s[u]].clear();
            for (int v:ls) {
                if (!vis[v]) visit(v);
            }
        } else {
            defer[c[u]].push_back(u);
        }
    };

    while (!empty(q)) {
        int u=q.front();
        q.pop();

        for (int v:adj[u]) {
            if (vis[v]) continue;
            visit(v);
        }
    }
}

// req vis to decide which stalls to visit
void bfs2() {
    have.assign(n+1,false);

    queue<int> q;
    q.push(1);

    have[f[1]]=true;
    vis[1]=true;

    vec<vec<int>> defer(n+1);

    function<void(int)> visit = [&](int u) {
        if (have[c[u]] || c[u]==f[u]) {
            q.push(u);
            have[f[u]]=true;
            vis[u]=true;

            vec<int> ls=defer[f[u]];
            defer[f[u]].clear();
            for (int v:ls) {
                if (!vis[v]) visit(v);
            }
        } else {
            defer[c[u]].push_back(u);
        }
    };

    while (!empty(q)) {
        int u=q.front();
        q.pop();

        for (int v:adj[u]) {
            if (vis[v]) continue;
            visit(v);
        }
    }
}

void solve() {
    bfs();

    for (int u=1; u<=n; ++u) {
        if (vis[u]) continue;
        if (s[u]!=f[u]) {
            puts("NO");
            return;
        }
    }

    for (int u=1; u<=n; ++u) vis[u]=!vis[u];
    bfs2();

    bool ans=count(all1(vis),false)==0;
    puts(ans?"YES":"NO");
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int _; cin>>_;
    while (_--) {
        cin>>n>>m;
        c.assign(n+1,0);
        for (int i=1; i<=n; ++i) cin>>c[i];
        s.assign(n+1,0);
        for (int i=1; i<=n; ++i) cin>>s[i];
        f.assign(n+1,0);
        for (int i=1; i<=n; ++i) cin>>f[i];

        adj.assign(n+1,{});
        for (int i=1; i<=m; ++i) {
            int u,v; cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        solve();
    }
}
