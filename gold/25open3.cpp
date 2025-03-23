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

int n,d,a,b;
vec<ll> m;

set<ll> pq; // values outside of b
map<int,int> freq;

void add(ll x, int cnt) {
    pq.insert(x);
    freq[x]+=cnt;
}

void solve() {
    multiset<ll> pqa;
    sort(all1(m),greater<ll>());
    for (int i=1; i<=b; ++i) {
        pqa.insert(m[i]);
    }

    for (int i=b+1; i<=a; ++i) {
        add(m[i],1);
    }
    int r=a+1;

    ll acc=0;
    for (int i=1; i<=d; ++i) {
        acc++;

        if (*prev(end(pq))+acc>*begin(pqa)) {
            ll pqatop=*begin(pqa);
            ll cur=*prev(end(pq));
            pqa.erase(begin(pqa));

            add(pqatop-acc,1);
            pqa.insert(cur+acc);
            freq[cur]--;
            if (freq[cur]==0) {
                pq.erase(pq.find(cur));

                // if (r<=n) {
                //     add(m[r],1);
                //     r++;
                // }
            }
        }
    }

    ll ans=0;
    for (ll x:pq) {
        x+=acc;
        for (int i=0; i<freq[x-acc]; ++i) {
            (ans+=(x*x)%M)%=M;
        }
    }
    for (ll x:pqa) (ans+=(x*x)%M)%=M;
    for (int i=r; i<=n; ++i) (ans+=(m[i]*m[i])%M)%=M;

    printf("%lld\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>d>>a>>b;
    m.assign(n+1,0);
    for (int i=1; i<=n; ++i) cin>>m[i];

    solve();
}
