#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> T cdiv(T a, T b) {return a/b+(sig(a)/sig(b)==1 && a%b);}

const int M=1e5;
int n,m;
struct in_t {ll a,b;} in[M+1];

bool ok(ll d) {
    ll l=0;
    ll fit=0; // max possible # cows fit onto farm
    for (int i=1; i<=m; ++i) {
        if (l>in[i].b) continue;

        ll cnt=cdiv(in[i].b-max(l,in[i].a)+1, d);
        l=max(l,in[i].a)+cnt*d;
        // l+=cnt*d;
        fit+=cnt;
    }

    return fit>=n;
}

void solve() {
    sort(in+1,in+1+m,[](in_t &x, in_t &y){return x.a<y.a;});

    ll lo=1, hi=1e18;
    while (lo+1<hi) {
        ll d=(lo+hi)/2;
        if (ok(d)) lo=d;
        else hi=d;
    }

    ll ans=lo;
    printf("%lld\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("socdist.in","r",stdin);
    freopen("socdist.out","w",stdout);

    cin>>n>>m;
    for (int i=1; i<=m; ++i) cin>>in[i].a>>in[i].b;
    solve();
}
