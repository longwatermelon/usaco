#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

const int N=1e5;
int n;
struct pt_t {int x,y;} pt[N+1];

vec<int> adj[N+1];
bool vis[N+1];

void dfs(int u) {
    if (vis[u]) return;
    vis[u]=true;

    for (int v:adj[u]) {
        dfs(v);
    }
}

void solve() {
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            if (i==j) continue;

            if (pt[i].x<=pt[j].x && pt[i].y<=pt[j].y) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    int ans=0;
    for (int u=1; u<=n; ++u) {
        if (vis[u]) continue;
        ans++;
        dfs(u);
    }

    printf("%d\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("moop.in","r",stdin);
    freopen("moop.out","w",stdout);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>pt[i].x>>pt[i].y;
    solve();
}
