#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;

int n;
string s;

int cnt[6];

void solve() {
    ll ans=0, acc=0;
    for (int i=1; i<=n; ++i) {
        cnt[0]++;

        vec<int> dcnt(6);
        for (int j=0; j<6; ++j) {
            if (s[i]=="bessie"[j]) {
                if (j==5) acc+=cnt[j];
                dcnt[(j+1)%6]+=cnt[j];
                dcnt[j]-=cnt[j];
            }
        }

        for (int j=0; j<6; ++j) {
            cnt[j]+=dcnt[j];
        }

        ans+=acc;
    }

    printf("%lld\n", ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>s;
    n=sz(s);
    s.insert(begin(s),' ');
    solve();
}
