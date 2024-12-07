#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
#define cmax(x,y) x=max(x,y)
template <typename T> using vec=vector<T>;
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}};

const int N=2000;
int n,a,b;
int p[N+1], c[N+1], x[N+1];

void solve() {
    vec3<int> dp(n+1,a+1,b+1,INT_MIN);
    dp[0][0][0]=0;
    for (int i=0; i<=n-1; ++i) {
        for (int y=0; y<=a; ++y) {
            for (int z=0; z<=b; ++z) {
                if (dp[i][y][z]==INT_MIN) continue;

                // no include i+1
                cmax(dp[i+1][y][z], dp[i][y][z]);

                // include i+1
                for (int w=0; w<=(b-z)/x[i+1]; ++w) {
                    if (w>c[i+1] || y+c[i+1]-w>a) continue;
                    cmax(dp[i+1][y+c[i+1]-w][z+w*x[i+1]], dp[i][y][z]+p[i+1]);
                }
            }
        }
    }

    int ans=INT_MIN;
    for (int y=0; y<=a; ++y) {
        for (int z=0; z<=b; ++z) {
            ans=max(ans,dp[n][y][z]);
        }
    }

    printf("%d\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>a>>b;
    for (int i=1; i<=n; ++i) cin>>p[i]>>c[i]>>x[i];
    solve();
}
