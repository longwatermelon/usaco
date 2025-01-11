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
int a[N+1];

void solve() {
    rotate(a+1, min_element(a+1,a+n+1)+1, a+n+1);
    a[0]=INT_MIN;

    // dif arr
    vec<int> stk;
    vec<ll> d(n+5);
    for (int i=n; i>=0; --i) {
        while (!empty(stk) && a[i]<=a[stk.back()]) {
            int x=stk.back();
            stk.pop_back();

            if (!empty(stk)) {
                int y=stk.back();
                d[y-(i+1)+1] -= a[x]-a[y];
            }
        }

        if (!empty(stk)) {
            int j=stk.back();
            d[j-i] += a[i]-a[j];
        }
        stk.push_back(i);
    }

    // dif arr -> loss
    vec<ll> loss(n+1); // i -> units of milk lost at minute i
    for (int i=1; i<=n; ++i) {
        loss[i]=loss[i-1]+d[i];
    }

    // ans
    ll ans=accumulate(a+1,a+n+1,0ll);
    for (int i=1; i<=n; ++i) {
        ans-=loss[i];
        printf("%lld\n", ans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>a[i];

    solve();
}
