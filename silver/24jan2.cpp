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
    assign each leaf to one potion
    try to choose deepest potion for each leaf
*/

const int N=1e5;
int n;
int p[N+1];

vec<int> adj[N+1];
int q[N+1];
vec<int> s; // leaves
int ucnt[N+1]; // ucnt[u]=# u-leaves
int cnt[N+1]; // # potions in each room

void dfs_init(int u, int qu) {
    q[u]=qu;
    for (int v:adj[u]) {
        if (v==qu) continue;
        dfs_init(v,u);
    }

    if (sz(adj[u])==1 && adj[u][0]==qu) {
        s.push_back(u);
        ucnt[u]++;
    }
}

void solve() {
    // parents, leaves
    dfs_init(1,0);

    // potion counts
    for (int i=1; i<=sz(s); ++i) {
        cnt[p[i]]++;
    }

    // move leaves up
    int ans=0;
    while (!empty(s)) {
        vec<int> sp;
        for (int u:s) {
            int d=min(cnt[u],ucnt[u]);
            cnt[u]-=d;
            ucnt[u]-=d;
            ans+=d;

            // for leaves which weren't assigned
            if (ucnt[u]>0) {
                sp.push_back(q[u]);
                ucnt[q[u]]+=ucnt[u];
                ucnt[u]=0;
            }
        }

        s=sp;
    }

    printf("%d\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>p[i];
    for (int i=1; i<=n-1; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    solve();
}
