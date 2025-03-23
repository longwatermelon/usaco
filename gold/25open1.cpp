#include <bits/stdc++.h>
#define bool int
using namespace std;
using ll=long long;
#define sign(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> bool ckmin(T &a, T b) {return b<a ? a=b, true : false;}
template <typename T> bool ckmax(T &a, T b) {return b>a ? a=b, true : false;}

const ll M=1e9+7;
ll modpow(ll x, ll p) {assert(p>=0);return p==0?1:((ll)modpow(((ll)x*x)%M,p/2)*(p&1?x:1))%M;}
ll modinv(ll x) {return modpow(x,M-2);}

vec<ll> F,IF; // fac, inv fac
ll comb(ll n, ll r) {
    if (n<r) return 0;
    return ((F[n]*IF[r])%M*IF[n-r])%M;
}

ll k,n,l;
string t;

void solve() {
    ll c=1;
    ll cnto=0;
    for (int i=n; i>=1; --i) {
        if (t[i]=='O') cnto++;
        else if (t[i]=='M') {
            (c*=comb(cnto,k))%=M;
            cnto-=k;
        }
    }

    ll ans=modpow(c,l);
    printf("%lld\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    F.resize(1e6+1);
    IF.resize(1e6+1);
    F[0]=1;
    IF[0]=modinv(1);
    for (int x=1; x<=1e6; ++x) {
        F[x]=((ll)F[x-1]*x)%M;
        IF[x]=modinv(F[x]);
    }

    cin>>k>>n>>l;
    cin>>t;
    t.insert(begin(t),' ');

    solve();
}
