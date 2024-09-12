#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> T cdiv(T a, T b) {return a/b+(sig(a)/sig(b)==1 && a%b);}
template <typename T> T mod(T a, T b) {return ((a%b)+b)%b;}
template <typename T> T rmod(T a, T mn, T mx) {return mod((a-mn),(mx-mn+1))+mn;}
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}};
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}};
#define PTX x
#define PTY y
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

/*
    assume both labelled the same k-vertex cycle, so all untouched labels can be the same
    to match within the cycle, find frequency of most common index difference in mod k
*/

const int K=5e5;
int n,k;
int a[K+1], b[K+1];

int match() {
    map<int,int> ind;
    for (int i=1; i<=k; ++i)
        ind[a[i]]=i;

    map<int,int> dind;
    int mxcnt=0;
    for (int i=1; i<=k; ++i) {
        if (ind.find(b[i])!=end(ind)) {
            int d=rmod(i-ind[b[i]],1,k);
            dind[d]++;
            mxcnt=max(mxcnt,dind[d]);
        }
    }

    return mxcnt;
}

void solve() {
    // count # in cycle
    int ans=match();
    reverse(b+1,b+1+k);
    ans=max(ans,match());

    // count # outside cycle
    set<int> s;
    for (int i=1; i<=k; ++i) {
        s.insert(a[i]);
        s.insert(b[i]);
    }
    ans+=n-sz(s);

    printf("%d\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>k;
    for (int i=1; i<=k; ++i) cin>>a[i];
    for (int i=1; i<=k; ++i) cin>>b[i];
    solve();
}
