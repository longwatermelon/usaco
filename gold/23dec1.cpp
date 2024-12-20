#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

const int N=750;
int n;
int a[N+1][N+1];

int k[N+1];
bool r[N+1][N+1];

void solve() {
    int ans=0;
    for (int i=n-1; i>=1; --i) {
        k[i]=1;
        for (int j=1; j<=n-i; ++j) {
            // add routes cnt
            k[i+j]=0;
            for (int x=i; x<=i+j-1; ++x) {
                if (!r[i+j][x]) {
                    k[i+j]^=k[x];
                }
            }

            // rm i->i+j if needed
            if (k[i+j]==a[i][j]) {
                ans++;
            } else {
                k[i+j]^=1;
                r[i+j][i]=true;
            }
        }
    }

    printf("%d\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n-1; ++i) {
        for (int j=1; j<=n-i; ++j) {
            char c; cin>>c;
            a[i][j]=c-'0';
        }
    }

    solve();
}
