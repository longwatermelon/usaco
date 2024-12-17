#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

const int N=1000, Q=2e5;
int n,q;
int r[Q+1], c[Q+1];
char t[Q+1];

char g[N+2][N+2];
bool vis[N+2][N+2];

// return true if can exit
// cnt=0 init, # vertices visited
bool dfs(int a, int b, int &cnt) {
    if (a==0 || a==n+1 || b==0 || b==n+1) return true;
    if (vis[a][b]) return false;
    vis[a][b]=true;

    if (g[a][b]=='L') {
        bool ok=dfs(a,b-1,cnt);
        if (ok) cnt++;
        return ok;
    } else if (g[a][b]=='R') {
        bool ok=dfs(a,b+1,cnt);
        if (ok) cnt++;
        return ok;
    } else if (g[a][b]=='U') {
        bool ok=dfs(a-1,b,cnt);
        if (ok) cnt++;
        return ok;
    } else if (g[a][b]=='D') {
        bool ok=dfs(a+1,b,cnt);
        if (ok) cnt++;
        return ok;
    } else {
        bool a1=dfs(a,b-1,cnt),
             a2=dfs(a,b+1,cnt),
             a3=dfs(a-1,b,cnt),
             a4=dfs(a+1,b,cnt);
        bool ok=a1||a2||a3||a4;
        if (ok) cnt++;
        return ok;
    }
}

int dfs2(int a, int b) {
    if (vis[a][b]) return 0;
    vis[a][b]=true;
    // printf("floodfill %d %d\n", a,b);

    int cnt=1<=a && a<=n && 1<=b && b<=n;
    if (1<=b && b<=n) {
        if (1<=a-1 && (!g[a-1][b] || g[a-1][b]=='D')) {
            cnt+=dfs2(a-1,b);
        }
        if (a+1<=n && (!g[a+1][b] || g[a+1][b]=='U')) {
            cnt+=dfs2(a+1,b);
        }
    }

    if (1<=a && a<=n) {
        if (1<=b-1 && (!g[a][b-1] || g[a][b-1]=='R')) {
            cnt+=dfs2(a,b-1);
        }

        if (b+1<=n && (!g[a][b+1] || g[a][b+1]=='L')) {
            cnt+=dfs2(a,b+1);
        }
    }

    return cnt;
}

void solve() {
    for (int i=1; i<=q; ++i) {
        g[r[i]][c[i]]=t[i];

        for (int a=0; a<=n+1; ++a) {
            for (int b=0; b<=n+1; ++b) {
                vis[a][b]=false;
            }
        }

        int okcnt=0;
        // dfs2(0,2);
        for (int x=1; x<=n; ++x) {
            okcnt+=dfs2(0,x)+dfs2(n+1,x)+dfs2(x,0)+dfs2(x,n+1);
            // okcnt+=dfs2(0,x);
        }
        int ans=n*n-okcnt;
        printf("%d\n", ans);

//         int ans=0;
//         for (int a=1; a<=n; ++a) {
//             for (int b=1; b<=n; ++b) {
//                 if (vis[a][b]) continue;
//                 int cnt=0;
//                 if (dfs(a,b,cnt)) {
//                     ans+=cnt;
//                 }
//             }
//         }
//         ans=n*n-ans;

//         printf("%d\n", ans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>q;
    for (int i=1; i<=q; ++i) cin>>r[i]>>c[i]>>t[i];
    solve();
}
