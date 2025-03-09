#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {
    vec2()=default;
    vec2(int n, int m, T val=T()) : vector<vector<T>>(n,vector<T>(m,val)) {}
    void assign(int n, int m, T val = T()) {
        this->vector<vector<T>>::assign(n, vector<T>(m, val));
    }
};

const int N=2e5;
const ll INF=1e18;
int n;
int a[N+1];
ll c[N+1];

vec<bool> vis;
vec2<ll> dp;
vec<vec<int>> in;
vec<bool> cycle;
vec<int> rem;

// find cycle, put in path. no cycle ==> path empty
void dfs(int u, vec<int> &path) {
    if (vis[u]) {
        auto it = find(all(path),u);
        // no cycle, or cycle is self loop?
        if (it==end(path) || next(it)==end(path)) {
            path.clear();
            return;
        }

        path = vec<int>(it,end(path));
        return;
    }
    vis[u]=true;

    path.push_back(u);
    return dfs(a[u],path);
}

// update u's dp from in[u]
void update_dp(int u) {
    if (empty(in[u])) {
        dp[u][0]=0;
        return;
    }

    // no edges from parents
    ll sum=0;
    for (int v:in[u]) {
        sum += min(dp[v][0],dp[v][1])+c[v];
        sum = min(sum,INF);
    }
    dp[u][0] = min(dp[u][0], sum);

    // (potentially) some edges from parents
    sum=0;
    bool kept=false;
    for (int v:in[u]) {
        if (dp[v][0] < dp[v][1]+c[v]) {
            sum += dp[v][0];
            kept=true;
        } else {
            sum += dp[v][1]+c[v];
        }

        // sum += dp[v][0];
        sum = min(sum,INF);
    }
    dp[u][kept] = min(dp[u][kept], sum);
}

void solve() {
    dp.assign(n+1,2, INF);

    // construct in
    in.assign(n+1, {});
    for (int u=1; u<=n; ++u) {
        if (u==a[u]) continue;
        in[a[u]].push_back(u);
    }

    // setup sources
    set<int> pq;
    for (int u=1; u<=n; ++u) {
        // source vertex?
        if (empty(in[u])) {
            pq.insert(u);
            dp[u][0]=0;
        }
    }

    // find cycles
    cycle.assign(n+1, false);
    vis.assign(n+1, false);
    vec<vec<int>> cycles;
    for (int u=1; u<=n; ++u) {
        if (vis[u]) continue;
        vec<int> path;
        dfs(u,path);

        if (!empty(path)) {
            for (int v:path) cycle[v]=true;
            cycles.push_back(path);
        }
    }

    // bfs from sources
    ll ans=0;
    rem.assign(n+1,0);
    for (int u=1; u<=n; ++u) rem[u]=sz(in[u]);
    while (!empty(pq)) {
        // extract next, ensure we should act on it
        int u = *begin(pq);
        pq.erase(begin(pq));
        if (cycle[u] || rem[u]) continue;

        // update dp[u]
        update_dp(u);

        // push into pq
        rem[a[u]]--;
        if (a[u]==u) {
            ans += min(dp[u][0],dp[u][1]);
        } else {
            pq.insert(a[u]);
        }
    }

    // cycle dp
    for (auto &path : cycles) {
        // pretend edge is missing in cycle
        in[path[0]].erase(find(all(in[path[0]]), path.back()));

        ll mnansdif=INF;
        // fill out dp along cycle (force removal of u->a[u])
        update_dp(path[0]);
        update_dp(path[1]);
        dp[path[1]][1]=INF;
        for (int i=2; i<sz(path); ++i) {
            update_dp(path[i]);
        }
        mnansdif = min(dp[path.back()][0], dp[path.back()][1]+c[path.back()]);

        // reset dp values
        for (int u:path) {
            dp[u]={INF,INF};
        }

        // force keep of u->a[u]
        update_dp(path[0]);
        update_dp(path[1]);
        dp[path[1]][0]=INF;
        for (int i=2; i<sz(path); ++i) {
            update_dp(path[i]);
        }
        mnansdif = min(mnansdif, min(dp[path.back()][0]+c[path.back()], dp[path.back()][1]+c[path.back()]));

        // extract final answer for this component
        assert(mnansdif<INF);
        ans += mnansdif;
    }

    // ans
    printf("%lld\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>a[i];
    for (int i=1; i<=n; ++i) cin>>c[i];

    solve();
}
