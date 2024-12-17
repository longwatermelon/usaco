#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

const int N=5e5;
int n;
ll a[N+1];

ll pre[N+1], suf[N+2];

void solve() {
    for (int i=1; i<=n; ++i) pre[i]=pre[i-1]+a[i];
    suf[n+1]=0;
    for (int i=n; i>=1; --i) suf[i]=suf[i+1]+a[i];

    ll elsie=0;
    for (int i=1; i+(n/2+1)-1<=n; ++i) {
        elsie=max(elsie,pre[i-1]+suf[i+(n/2+1)]);
    }

    ll bessie=accumulate(a+1,a+1+n,0ll)-elsie;
    printf("%lld %lld\n", bessie, elsie);

    // int l=1, r=n;
    // ll elsie=0;
    // for (int i=1; i<=n/2-1; ++i) {
    //     if (a[l]>a[r]) {
    //         elsie+=a[l];
    //         l++;
    //     } else {
    //         elsie+=a[r];
    //         r--;
    //     }
    // }

    // ll bessie=accumulate(a+1,a+1+n,0ll)-elsie;
    // printf("%lld %lld\n", bessie,elsie);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin>>t;
    while (t--) {
        cin>>n;
        for (int i=1; i<=n; ++i) cin>>a[i];
        solve();
    }
}
