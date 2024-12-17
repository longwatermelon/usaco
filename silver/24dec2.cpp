#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

const int N=1e5, K=1e5;
int n,k;
ll x[N+1];
struct in_t {ll l,r,t;} in[K+1];
ll s[K+1];

// return i for x[i]<=val<x[i+1]
int binsearch(ll val) {
    int lo=0, hi=n+1;
    while (lo+1<hi) {
        int i=(lo+hi)/2;
        if (x[i]<=val) lo=i;
        else hi=i;
    }

    return lo;
}

void solve() {
    // sort ascending by l_i
    sort(in+1,in+1+k,[](in_t &a, in_t &b){return a.l<b.l;});
    // sort ascending by x_i
    sort(x+1,x+1+n);

    // surplus vals
    // for (int i=1; i<=k; ++i) {
    //     s[i]=0;
    //     for (int j=1; j<=n; ++j) {
    //         if (in[i].l<=x[j] && x[j]<=in[i].r) {
    //             s[i]++;
    //         }
    //     }

    //     s[i]-=in[i].t;
    //     // printf("surplus %d=%lld\n", i,s[i]);
    // }
    for (int i=1; i<=k; ++i) {
        int il=binsearch(in[i].l), ir=binsearch(in[i].r);
        if (x[il]!=in[i].l) il++;
        int inside=ir-il+1;
        s[i]=inside-in[i].t;
    }

    // removing trees
    auto tcmp=[](int a, int b){return in[a].r<in[b].r;};
    multiset<int,decltype(tcmp)> t(tcmp); // interval indices by ascending r endp
    multiset<ll> st; // surplus vals
    int j=1; // cur interval ind
    ll acc=0; // # removed so far
    // multiset<ll> done;
    for (int i=1; i<=n; ++i) {
        // push all l[j]<=x[i]
        while (j<=k && in[j].l<=x[i]) {
            t.insert(j);
            s[j]+=acc;
            st.insert(s[j]);
            j++;
        }

        // assert(sz(t)==sz(st));

        // remove all r<x[i]
        while (!empty(t) && in[*begin(t)].r<x[i]) {
            // erase corresponding surplus
            // done.insert(*st.find(s[*begin(t)])-acc);
            int prev=sz(st);
            st.erase(st.find(s[*begin(t)]));
            assert(sz(st)==prev-1);
            t.erase(begin(t));
        }

        // assert(sz(t)==sz(st));

        // remove tree i?
        if (empty(st) || *begin(st)-acc>0) {
            // printf("remove tree %lld\n", x[i]);
            acc++;
        }
    }

    // for (ll si:done) printf("- %lld\n", si);
    // for (ll si:st) printf("- %lld\n", si-acc);
    ll ans=acc;
    printf("%lld\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin>>t;
    while (t--) {
        cin>>n>>k;
        for (int i=1; i<=n; ++i) cin>>x[i];
        x[0]=-1e10;
        for (int i=1; i<=k; ++i) cin>>in[i].l>>in[i].r>>in[i].t;

        solve();
    }
}
