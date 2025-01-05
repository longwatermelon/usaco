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
int n;
ll p[N+1], s[N+1];

int lf[N+2], rt[N+2];

// observation number when i,j cancel
ll f(int i, int j) {
    return 2ll*cdiv(p[j]-p[i], s[i]+s[j]) - (i%2);
}

void solve() {
    auto cmp=[](pair<int,int> x, pair<int,int> y){return f(x.first,x.second) < f(y.first,y.second);};
    multiset<pair<int,int>, decltype(cmp)> pq(cmp);
    for (int i=1; i<=n-1; ++i) pq.insert({i,i+1});
    for (int i=1; i<=n; ++i) {
        lf[i]=i-1;
        rt[i]=i+1;
    }

    vec<ll> ans(n+1);
    while (!empty(pq)) {
        auto [i,j]=*begin(pq);
        pq.erase(begin(pq));

        if (ans[i] || ans[j]) continue;
        // cancel i,j
        ll x=f(i,j);
        ans[i]=x;
        ans[j]=x;
        rt[lf[i]]=rt[j];
        lf[rt[j]]=lf[i];

        // new formed pair
        if (lf[i]!=0 && rt[j]!=n+1) {
            pq.insert({lf[i], rt[j]});
        }
    }

    for (int i=1; i<=n; ++i) {
        printf("%lld%c", ans[i], " \n"[i==n]);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin>>t;
    while (t--) {
        cin>>n;
        for (int i=1; i<=n; ++i) cin>>p[i];
        for (int i=1; i<=n; ++i) cin>>s[i];

        solve();
    }
}
