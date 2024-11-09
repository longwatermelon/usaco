#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}};
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}};
#define PTX x
#define PTY y
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

const int N=2e5;
int n,m;
int p[N+1];
vec<int> adj[N+1];
bool open[N+1]; // u -> barn u opened?

int id[N+1]; // u -> component id vertex u is in
vec<int> g[N+1]; // i -> vertices in component i

// merge components i,j into larger component
void merge(int i, int j) {
    if (sz(g[i])<sz(g[j])) swap(i,j);

    for (int u:g[j]) {
        id[u]=i;
        g[i].push_back(u);
    }

    g[j].clear();
}

void solve() {
    // setup dsu
    for (int u=1; u<=n; ++u) {
        id[u]=u;
        g[u]={u};
    }

    // open barns in rev order
    int cnt=0;
    vec<string> ans;
    for (int i=n; i>=1; --i) {
        open[p[i]]=true;
        cnt++;

        // merge w/ adj components
        int mergecnt=0;
        for (int u:adj[p[i]]) {
            if (open[u] && id[u]!=id[p[i]]) {
                merge(id[u],id[p[i]]);
                mergecnt++;
            }
        }

        // update component cnt
        cnt-=mergecnt;
        ans.push_back(cnt==1 ? "YES":"NO");
    }

    // ans
    for (int i=sz(ans)-1; i>=0; --i)
        printf("%s\n", ans[i].c_str());
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("closing.in","r",stdin);
    freopen("closing.out","w",stdout);

    cin>>n>>m;
    for (int i=1; i<=m; ++i) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i=1; i<=n; ++i) cin>>p[i];

    solve();
}
