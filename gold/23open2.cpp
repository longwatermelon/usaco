#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> using vec=vector<T>;
template <typename T> bool ckmin(T &a, T b) {return b<a ? a=b, true : false;}
template <typename T> bool ckmax(T &a, T b) {return b>a ? a=b, true : false;}
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}void assign(int n, int m, T val = T()) {this->vector<vector<T>>::assign(n, vector<T>(m, val));}};
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}void assign(int n, int m, int k, T val = T()) {this->vector<vector<vector<T>>>::assign(n, vector<vector<T>>(m, vector<T>(k, val)));}};

const string B="bessie";
const int C=1000;
int n;
string s;
vec<int> c;

vec2<pair<int,int>> dp;
vec2<bool> ok;

void upd(pair<int,int> &p0, pair<int,int> p1) {
    if ((p1.first==p0.first && p1.second<p0.second) || (p1.first>p0.first)) {
        p0=p1;
    }
}

pair<int,int> add(pair<int,int> p0, pair<int,int> p1) {
    return {p0.first+p1.first, p0.second+p1.second};
}

// run dp
void compute_dp() {
    dp.assign(n+1,6,{-1,INT_MAX});
    dp[0][0]={0,0};

    for (int i=0; i<n; ++i) {
        for (int j=0; j<=5; ++j) {
            if (dp[i][j].first==-1) continue;

            if (j==0) upd(dp[i+1][j], dp[i][j]);
            if (j>0) upd(dp[i+1][j], add(dp[i][j],{0,c[i+1]}));
            if (s[i+1]==B[j]) upd(dp[i+1][(j+1)%6], add(dp[i][j],{j==5,0}));
        }
    }
}

void solve() {
    compute_dp();

    pair<int,int> ans=dp[n][0];
    printf("%d\n%d\n", ans.first, ans.second);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>s;
    n=sz(s);
    s.insert(begin(s),' ');
    c.assign(n+1,0);
    for (int i=1; i<=n; ++i) cin>>c[i];

    solve();
}
