#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

const int N=1e5, M=1e5;
int n,m;
int f[N+1], s[N+1];

int c[M+1];

// return # cows which get pushed out
int steal(int i, int x) {
    if (c[x] && i>c[x]) {
        return -1;
    }

    int cx=c[x]; // cow which gets pushed out
    c[x]=i;

    if (!cx) {
        return 0;
    }

    if (x==f[cx]) {
        return steal(cx,s[cx]);
    }

    assert(x==s[cx]);
    return -1;
}

void solve() {
    vec<int> ans(n);
    ans[n-1]=1;
    c[f[n]]=n;

    for (int i=n-1; i>=1; --i) {
        ans[i-1]=ans[i]+1+steal(i,f[i]);
    }

    for (int x:ans) {
        printf("%d\n", x);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("cereal.in","r",stdin);
    freopen("cereal.out","w",stdout);

    cin>>n>>m;
    for (int i=1; i<=n; ++i) cin>>f[i]>>s[i];
    solve();
}
