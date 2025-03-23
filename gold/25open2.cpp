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

int n,q;
vec<int> a;

vec<ll> f;
vec<set<int>> has_f; // frequency value -> elements in a which have that frequency
set<int> s;

void upd_remove(int i) {
    has_f[f[a[i]]-1].insert(a[i]);
    s.insert(f[a[i]]-1);
    has_f[f[a[i]]].erase(has_f[f[a[i]]].find(a[i]));
    if (empty(has_f[f[a[i]]])) s.erase(s.find(f[a[i]]));

    f[a[i]]--;
}

void upd_add(int i, int x) {
    has_f[f[x]+1].insert(x);
    s.insert(f[x]+1);
    has_f[f[x]].erase(has_f[f[x]].find(x));
    if (empty(has_f[f[x]])) s.erase(s.find(f[x]));

    f[x]++;
    a[i]=x;
}

void solve() {
    // prep
    f.assign(n+1,0);
    for (int i=1; i<=n; ++i) f[a[i]]++;
    has_f.assign(n+1,{});
    for (int x=1; x<=n; ++x) {
        has_f[f[x]].insert(x);
        s.insert(f[x]);
    }

    // queries
    while (q--) {
        int i,x; cin>>i>>x;

        upd_remove(i);
        upd_add(i,x);

        int ans=0;
        auto it2=begin(s);
        auto it=prev(end(s));
        if (*begin(s)==0) {
            // it++;
            it2++;
        }
        int mn=1e8;
        bool ok=true;
        while (it2!=end(s)) {
            while (ok && *it!=0 && *it2+*it>=*prev(end(s))) {
                ckmin(mn,*begin(has_f[*it]));
                if (it==begin(s)) {
                    ok=false;
                } else {
                    it--;
                }
            }

            ckmax(ans,*prev(end(has_f[*it2]))-mn);
            it2++;
        }

        it2=begin(s);
        it=prev(end(s));
        if (*begin(s)==0) {
            // it++;
            it2++;
        }
        int mx=-1e8;
        ok=true;
        while (it2!=end(s)) {
            while (ok && *it!=0 && *it2+*it>=*prev(end(s))) {
                ckmax(mx,*prev(end(has_f[*it])));
                if (it==begin(s)) {
                    ok=false;
                } else {
                    it--;
                }
            }

            ckmax(ans,mx-*begin(has_f[*it2]));
            it2++;
        }

        // it2=begin(s);
        // it=prev(end(s));
        // if (*begin(s)==0) {
        //     it2++;
        // }
        // int mx=-1e8;
        // ok=true;
        // while (it2!=end(s)) {
        //     while (ok && *it2+*it>=*prev(end(s))) {
        //         ckmax(mx,*prev(end(has_f[*it])));
        //         if (it==begin(s)) {
        //             ok=false;
        //         } else {
        //             it--;
        //         }
        //     }

        //     ckmax(ans,mx-*begin(has_f[*it2]));
        //     it2++;
        // }
        // while (it!=end(s)) {
        //     if (*it==0) it++;
        //     auto it2=begin(s);
        //     while (it2!=end(s)) {
        //         if (*it2==0) it2++;
        //         if (*it+*it2<*prev(end(s))) {
        //             it2++;
        //             continue;
        //         }
        //         ckmax(ans,*prev(end(has_f[*it2]))-*begin(has_f[*it]));
        //         it2++;
        //     }

        //     it++;
        // }

        assert(ans<=n);

        printf("%d\n", ans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>q;
    a.assign(n+1,0);
    for (int i=1; i<=n; ++i) cin>>a[i];

    solve();
}
