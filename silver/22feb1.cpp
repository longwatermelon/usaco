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
    tle on tc 10 and 11 but that's good enough
    directed graph where vertices as cows and u->v ==> cow u can accept gift v (v better than u)
    each simple cycle in the graph is a possible shift in gifts, where each cow can receive the gift of the cow she points to
    keep track of min possible index of received gift in each cow's preferences, ans is that
*/

const int N=500;
int n;
int p[N+1][N+1]; // preferences

vec<int> adj[N+1];
int ans[N+1]; // earliest index reachable
int ind[N+1][N+1]; // i,x -> index of x in p[i]

bool vis[N+1];

void dfs(int u, vec<int> &path, vec<vec<int>> &cycles) {
    if (vis[u]) {
        // cycle?
        auto it=find(all(path),u);
        if (it!=end(path)) {
            cycles.push_back(vec<int>(it,end(path)));
        }

        return;
    }
    vis[u]=true;
    path.push_back(u);

    for (int v:adj[u]) {
        dfs(v,path,cycles);
    }

    path.pop_back();
}

void solve() {
    // setup graph
    for (int u=1; u<=n; ++u) {
        int i;
        for (i=1; p[u][i]!=u; ++i) {
            adj[u].push_back(p[u][i]);
        }
        ans[u]=i;
    }

    // setup ind
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            ind[i][p[i][j]]=j;
        }
    }

    // find cycles
    for (int u=1; u<=n; ++u) {
        fill(vis+1,vis+1+n,false);
        vec<int> path;
        vec<vec<int>> cycles;
        dfs(u,path,cycles);

        for (auto &cycle:cycles) {
            for (int i=0; i<sz(cycle); ++i) {
                ans[cycle[i]]=min(ans[cycle[i]], ind[cycle[i]][cycle[(i+1)%sz(cycle)]]);
            }
        }
    }

    // ans
    for (int i=1; i<=n; ++i) {
        printf("%d\n", p[i][ans[i]]);
    }
}

signed main() {
    /* ios_base::sync_with_stdio(false); */
    /* cin.tie(NULL); */

    cin>>n;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            cin>>p[i][j];
        }
    }
    solve();
}
