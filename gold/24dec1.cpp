#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> void vprint(T st, T nd) {auto it=st;while (next(it)!=nd){cout<<*it<<' ';it=next(it);}cout<<*it<<'\n';}

const int N=1e5;
int n;
int a[N+1];

vec<int> nxt[N+1];
vec<int> ind[N+1];
set<int> lb; // labels
int freq[N+1]; // L -> frequency of label L in a

// subtasks 1-2
// void solve() {
//     for (int i=1; i<=n; ++i) {
//         lb.insert(a[i]);
//     }

//     for (int L:lb) {
//         int r=n+1;
//         nxt[L]=vec<int>(n+1);
//         for (int i=n; i>=0; --i) {
//             nxt[L][i]=r;
//             if (a[i]==L) {
//                 r=i;
//             }
//         }
//     }

//     vec<int> ans(n+1);
//     for (int x=1; x<=n; ++x) {
//         for (int L:lb) {
//             int i=nxt[L][0];
//             while (i<=n) {
//                 i=nxt[L][min(i+x,n)];
//                 ans[x]++;
//             }
//         }
//     }

//     for (int x=1; x<=n; ++x) {
//         printf("%d\n", ans[x]);
//     }
// }

// subtask 3
int f(int L, int x) {
    int res=1, r=ind[L][0]+x+1;
    for (int i:ind[L]) {
        if (i>=r) {
            r=i+x+1;
            res++;
        }
    }

    return res;
}

void solve() {
    int sq=20;

    // find all existing labels
    for (int i=1; i<=n; ++i) {
        lb.insert(a[i]);
        freq[a[i]]++;
        ind[a[i]].push_back(i);
    }

    // construct nxt
    for (int L:lb) {
        if (freq[L]>=sq) {
            int r=n+1;
            nxt[L]=vec<int>(n+1);
            for (int i=n; i>=0; --i) {
                nxt[L][i]=r;
                if (a[i]==L) {
                    r=i;
                }
            }
        }
    }

    // construct dif arr
    vec<int> d(n+2);
    for (int L:lb) {
        if (freq[L]<sq) {
            for (int g=1; g<=freq[L] && f(L,1)>=g; ++g) {
                int lo=0, hi=n+1;
                while (lo+1<hi) {
                    int x=(lo+hi)/2;
                    if (f(L,x)>=g) lo=x;
                    else hi=x;
                }

                if (hi<=n) {
                    d[hi]--;
                }
            }
        } else {
            for (int x=1; x<=n; ++x) {
                int i=nxt[L][0];
                while (i<=n) {
                    i=nxt[L][min(i+x,n)];
                    d[x]++;
                    d[x+1]--;
                }
            }
        }
    }

    // ans
    int ans=0;
    for (int L:lb) {
        if (freq[L]<sq) {
            ans+=f(L,1);
        }
    }

    for (int x=1; x<=n; ++x) {
        ans+=d[x];
        printf("%d\n", ans);
    }
    // vprint(all1(d));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) cin>>a[i];
    solve();
}
