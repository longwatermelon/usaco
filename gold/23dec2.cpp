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
vec<int> adj[N+1], radj[N+1];
map<int, map<int,int>> l;
int out[N+1];

int len[N+1]; // u -> optimal path length for ans
int nxt[N+1]; // u -> vertex which u points to on optimal path
ll sum[N+1]; // u -> optimal path label sum
int rnk[N+1];
vec<int> cand[N+1];

void solve() {
    // find sinks
    vec<int> vt;
    for (int u=1; u<=n; ++u) {
        if (out[u]==0) {
            vt.push_back(u);
        }
    }

    // bfs
    while (!empty(vt)) {
        // construct vt', find candidate vals
        vec<int> vtp; // vt'
        for (int u:vt) {
            for (int p:radj[u]) {
                cand[p].push_back(u);
                out[p]--;
                if (out[p]==0) {
                    vtp.push_back(p);
                }
            }
        }

        // find optimal path for each parent
        for (int p:vtp) {
            vec<int> &s=cand[p];

            // sort(all(s),[p](int x, int y){return len[x]==len[y] ? (l[p][x]==l[p][y] ? rnk[x]<rnk[y] : l[p][x]<l[p][y]) : len[x]>len[y];});
            sort(all(s), [p](int x, int y){return vec<int>{-len[x], l[p][x], rnk[x]} < vec<int>{-len[y], l[p][y], rnk[y]};});
            nxt[p]=s[0];
            sum[p]=sum[nxt[p]]+l[p][nxt[p]];
            len[p]=len[nxt[p]]+1;
        }

        vt=vtp;
        sort(all(vt),[](int u, int v){return vec<int>{l[u][nxt[u]], rnk[nxt[u]]} < vec<int>{l[v][nxt[v]], rnk[nxt[v]]};});
        for (int i=0; i<sz(vt); ++i) {
            rnk[vt[i]]=i;
        }
    }

    for (int u=1; u<=n; ++u) {
        printf("%d %lld\n", len[u], sum[u]);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>m;
    for (int i=1; i<=m; ++i) {
        int a,b; cin>>a>>b;
        cin>>l[a][b];
        adj[a].push_back(b);
        radj[b].push_back(a);
        out[a]++;
    }

    solve();
}
