#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

#define int ll

const ll MD=1e9+7;
ll modpow(ll x, ll p) {
    assert(p>=0);
    return p==0 ? 1 : ((ll)modpow(((ll)x*x)%MD,p/2)*(p%2?x:1))%MD;
}

int n,m,q;

void solve() {
    // setup indices sweepline
    map<int,int> freq;
    for (int i=1; i<=m; ++i) {
        int l,r; cin>>l>>r;
        freq[l]++;
        freq[r+1]++;
    }

    vec<int> inds;
    for (auto &[i,f]:freq) {
        if (f%2) {
            inds.push_back(i);
        }
    }

    // create blocks
    vec<int> blks;
    blks.push_back(inds[0]-1);
    for (int i=0; i<sz(inds)-1; ++i) {
        blks.push_back(inds[i+1]-inds[i]);
    }
    blks.push_back(n+1-inds.back());

    // pre, suf
    vec<ll> pre1(sz(blks)), pre(sz(blks)), suf(sz(blks));
    pre[0]=blks[0];
    pre1[0]=blks[0];
    for (int i=1; i<sz(blks); ++i) {
        pre[i] = pre[i-1]+blks[i];
        pre1[i] = pre1[i-1];
        if (i%2==0) {
            pre1[i] += blks[i];
        }
    }
    suf.back() = blks.back();
    for (int i=sz(inds)-2; i>=0; --i) {
        suf[i] = suf[i+1]+blks[i];
    }

    // queries
    while (q--) {
        int l,r,k; cin>>l>>r>>k;

        // find index i s.t. pre[i] < l <= pre[i+1]
        int lo=-1, hi=sz(blks);
        while (lo+1<hi) {
            int i = (lo+hi)/2;
            if (l<=pre[i]) hi=i;
            else lo=i;
        }
        int il = hi;

        // find index i s.t. pre[i-1] < r <= pre[i]
        lo=0;
        hi=sz(blks);
        while (lo+1<hi) {
            int i = (lo+hi)/2;
            if (r<=pre[i]) hi=i;
            else lo=i;
        }
        int ir = hi;

        // answer query
        int prevfst = blks[il], prevlst = blks[ir];
        blks[il] = pre[il]-l+1;
        blks[ir] = r-pre[ir-1];
        int sum1=0, sum0=0;
        for (int i=il; i<=ir; ++i) {
            if (i%2) {
                sum1+=blks[i];
            }
        }

        ll ans=0;
        int sufsum=0;
        for (int i=ir; i>=il-1; --i) {
            if (sum1+sufsum>=k) {
                ans += modpow(2, min(sum1,k)+sufsum)-1 - (modpow(2, sufsum)-1);
                break;
            }

            if (i%2==0) {
                sum0+=blks[i];
                if (i+1<=ir) {
                    ans += modpow(2, sufsum)-1 - (modpow(2, sufsum-blks[i+1])-1);
                    // sufsum1 += blks[i+1];
                }
            } else {
                sum1 -= blks[i];
            }
            sufsum+=blks[i];
        }

        blks[il] = prevfst;
        blks[ir] = prevlst;
        printf("%lld\n", ans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>m>>q;
    solve();
}
