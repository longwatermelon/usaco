#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}};
template <typename T> bool ckmin(T &a, T b) {return b<a ? a=b, true : false;}
template <typename T> bool ckmax(T &a, T b) {return b>a ? a=b, true : false;}

const int N=2e5, Q=2e5;
int n,q;
int a[N+1];
ll c[N+1];
int qu[Q+1];

// // compresses a, qu
// void coord_compress() {
//     // compute compressed
//     vec<int> b(a+1,a+n+1);
//     b.insert(end(b),qu+1,qu+q+1);
//     sort(all(b));
//     map<int,int> mp;
//     for (int i=0; i<sz(b); ++i) {
//         mp[b[i]]=i;
//     }

//     // update
//     for (int i=1; i<=n; ++i) {
//         a[i]=mp[a[i]];
//     }
//     for (int i=1; i<=q; ++i) {
//         qu[i]=mp[qu[i]];
//     }
// }

// relation of x to m
int p(int m, int x) {
    return x<m ? 0 : (x==m ? 1 : 2);
}

// cost to make a[i] relation to m equal to j
ll cost(int i, int j, int m) {
    return p(m,a[i])==j ? 0 : c[i];
}

// median
int med(int x, int y, int z) {
    return x^y^z ^ min({x,y,z}) ^ max({x,y,z});
}

void upd(int i, int m, vec2<ll> &dp) {
    if (i==0) return;
    for (int j:{0,1,2}) {
        dp[i][j]=1e15;
    }

    if (2*i>n) {
        // leaf
        for (int j:{0,1,2}) {
            dp[i][j] = cost(i,j,m);
        }
    } else {
        // not leaf
        for (int x:{0,1,2}) {
            for (int y:{0,1,2}) {
                for (int z:{0,1,2}) {
                    ckmin(dp[i][med(x,y,z)], dp[2*i][x] + dp[2*i+1][y] + cost(i,z,m));
                }
            }
        }
    }

    upd(i/2, m, dp);
}

void solve() {
    vec2<ll> dp(n+1,3,1e15);

    // init dp
    for (int i=(n+1)/2; i<=n; ++i) {
        upd(i,INT_MIN,dp);
    }

    // queries
    map<int,ll> ans;
    vec<int> m(qu+1,qu+q+1);
    sort(all(m));

    // initially all a_i>m
    auto cmp=[](int i, int j){return a[i]<a[j];};
    multiset<int,decltype(cmp)> s[3]={
        multiset<int,decltype(cmp)>(cmp),
        multiset<int,decltype(cmp)>(cmp),
        multiset<int,decltype(cmp)>(cmp),
    };
    for (int i=1; i<=n; ++i) {
        s[2].insert(i);
    }

    // process queries
    for (int k=0; k<sz(m); ++k) {
        set<int> v;
        while (!empty(s[2]) && a[*begin(s[2])] <= m[k]) {
            int x = *begin(s[2]);
            s[2].erase(begin(s[2]));
            s[1].insert(x);
            v.insert(x);
        }

        while (!empty(s[1]) && a[*begin(s[1])] < m[k]) {
            int x = *begin(s[1]);
            s[1].erase(begin(s[1]));
            s[0].insert(x);
            v.insert(x);
        }

        for (int i:v) {
            upd(i,m[k],dp);
        }
        ans[m[k]] = dp[1][1];
    }

    // print ans
    for (int i=1; i<=q; ++i) {
        printf("%lld\n", ans[qu[i]]);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>a[i]>>c[i];
    cin>>q;
    for (int i=1; i<=q; ++i) cin>>qu[i];

    solve();
}
