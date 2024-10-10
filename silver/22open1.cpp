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
    construct directed graph w/ cows as vertices and i->a_i edge with weight v_i
    each vertex has one outgoing edge
    each connected component has one cycle
    one edge's value can't be added to result sum, choose lowest edge value
    repeatedly dfs from some random vertex which hasn't been visited yet, if detect cycle remove the minimum weight edge
*/

const int N=1e5;
int n;
ll a[N+1], v[N+1];

bool vis[N+1];

int dfs(int u, vec<int> &path) {
    if (vis[u]) {
        auto it=find(all(path),u);
        if (it!=end(path)) {
            return it-begin(path);
        }
        return -1;
    }
    vis[u]=true;
    path.push_back(u);

    return dfs(a[u],path);
}

ll contrib(vec<int> &path, int st) {
    ll mn=st==-1 ? 0 : v[*min_element(begin(path)+st,end(path),[](int i, int j){return v[i]<v[j];})];
    ll sum=accumulate(all(path),0ll,[](ll cur, int u){return cur+v[u];});
    return sum-mn;
}

void solve() {
    ll ans=0;
    for (int u=1; u<=n; ++u) {
        if (vis[u]) continue;
        vec<int> path;
        int st=dfs(u,path);
        ans+=contrib(path,st);
    }

    printf("%lld\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>a[i]>>v[i];
    solve();
}
