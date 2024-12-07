#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}};
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}};
#define PTX x
#define PTY y
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

const int N=1000;
int n,k;
int b[N+1];

void solve() {
    int ans=0;
    for (int x=1; x<=1000; ++x) {
        multiset<int,greater<int>> s;
        for (int i=1; i<=n; ++i) s.insert(b[i]);

        // elsie's
        bool ok=true;
        for (int i=1; i<=k/2; ++i) {
            int val=*begin(s);
            s.erase(begin(s));
            if (val<x) {
                ok=false;
                break;
            }

            s.insert(val-x);
        }
        if (!ok) break;

        // bessie's
        int cnt=0;
        for (int i=1; i<=k/2; ++i) {
            int val=*begin(s);
            s.erase(begin(s));

            int d=min(val,x);
            cnt+=d;
            s.insert(val-d);
        }

        // ans
        ans=max(ans,cnt);
    }

    printf("%d\n", ans);
}

signed main() {
    /* freopen("berries.in","r",stdin); */
    /* freopen("berries.out","w",stdout); */

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>k;
    for (int i=1; i<=n; ++i) cin>>b[i];
    solve();
}
