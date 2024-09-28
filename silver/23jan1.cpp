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

string s,t;
int out[256];
set<int> in[256];
bool vis[256];

int dfs(int u) {
    if (vis[u] || !out[u]) return 0;
    vis[u]=true;
    return 1+dfs(out[u]);
}

void solve() {
    for (int i=0; i<sz(s); ++i) {
        if (out[(int)s[i]] && out[(int)s[i]]!=t[i]) {
            puts("-1");
            return;
        } else {
            out[(int)s[i]]=t[i];
            if (s[i]!=t[i])
                in[(int)t[i]].insert(s[i]);
        }
    }
    bool placeholder=false;
    for (char c='a'; c<='z'; ++c)
        placeholder|=sz(in[int(c)])==0 && out[int(c)]!=c;
    for (char c='A'; c<='Z'; ++c)
        placeholder|=sz(in[int(c)])==0 && out[int(c)]!=c;

    for (int u=0; u<256; ++u) {
        if (out[u]==u) out[u]=0;
    }

    int ans=0;
    // non-pure cycles
    for (char c:s) {
        if (!vis[int(c)] && empty(in[int(c)])) {
            ans+=dfs(c);
        }
    }

    // just cycles
    for (char c:s) {
        if (vis[int(c)] || !out[int(c)]) continue;
        if (!placeholder) {
            puts("-1");
            return;
        }
        ans+=dfs(c)+1;
    }

    printf("%d\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int _; cin>>_;
    while (_--) {
        cin>>s>>t;
        memset(out,0,sizeof(out));
        memset(vis,false,sizeof(vis));
        for (int u=0; u<256; ++u) in[u].clear();
        solve();
    }
}
