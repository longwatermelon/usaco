#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> T cdiv(T a, T b) {return a/b+(sig(a)/sig(b)==1 && a%b);}

const int N=2e5;
ll n,q;
ll x[N+1];
ll a,b;

ll p[N+1], s[N+2];

// waste when y=x[i]
ll waste(ll i) {
    return x[i]*(i*a - (n-i)*b) + b*(p[n]-p[i]) - a*p[i];
}

void solve() {
    sort(x+1,x+1+n);

    for (int i=1; i<=n; ++i) p[i]=p[i-1]+x[i];
    s[n+1]=0;
    for (int i=n; i>=1; --i) s[i]=s[i+1]+x[i];

    while (q--) {
        cin>>a>>b;
        ll l=(b*n-a)/(a+b);
        ll r=cdiv(b*(n+1), a+b);

        ll mnw=INT64_MAX;
        for (ll i=max(1ll,l); i<=min(r,n); ++i) {
            ll w=waste(i);
            mnw=min(mnw,w);
        }

        printf("%lld\n", mnw);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>x[i];
    cin>>q;
    solve();
}
