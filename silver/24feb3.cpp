#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> T cdiv(T a, T b) {return a/b+(sig(a)/sig(b)==1 && a%b);}
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}};
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}};
#define PTX x
#define PTY y
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

/*
    first optimize for surviving; i.e. choose option which decreases Elsie's marbles least
    pass through from left to right (for lex. ordering) to change odd->even to make sequence lex. minimal
        check if possible in O(1) by keeping suffix min and accumulator for difference in marbles from switching
*/

const int M=3e5;
int n,m,k;
struct {int mxe{INT_MIN},mxo{INT_MIN},mne{INT_MAX},mno{INT_MAX};bool even(){return mxe!=INT_MIN;}bool odd(){return mxo!=INT_MIN;}} turns[M+1];

void solve() {
    vec<int> ans(m+1); // parities; 0 for even, 1 for odd
    vec<int> cnt(m+1); // # Elsie marbles at any turn

    // optimize for win first
    for (int i=1; i<=m; ++i) {
        if (turns[i].even() && turns[i].odd()) {
            // has both parities
            ans[i]=turns[i].mxo>turns[i].mxe;
            n-=min(turns[i].mxo,turns[i].mxe);
        } else if (turns[i].even()) {
            ans[i]=0;
            n+=turns[i].mne;
        } else { // odd
            ans[i]=1;
            n+=turns[i].mno;
        }

        cnt[i]=n;
        if (n<=0) {
            puts("-1");
            return;
        }
    }

    vec<int> suf(m+1);
    suf[m]=cnt[m];
    for (int i=m-1; i>=1; --i) {
        suf[i]=min(suf[i+1],cnt[i]);
    }

    // optimize for lexicographic min
    int acc=0;
    for (int i=1; i<=m; ++i) {
        // try odd->even
        if (ans[i]) {
            int d=turns[i].even() ? turns[i].mxo-turns[i].mxe : turns[i].mxo+turns[i].mno;
            acc+=d;

            if (suf[i]-acc>0) {
                // possible to switch
                ans[i]=0;
            } else {
                // don't switch
                acc-=d;
            }
        }
    }

    // ans
    for (int i=1; i<=m; ++i) {
        if (ans[i]) printf("Odd");
        else printf("Even");

        if (i<m) putchar(' ');
    }
    putchar('\n');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int _; cin>>_;
    while (_--) {
        cin>>n>>m>>k;
        for (int i=1; i<=m; ++i) {
            turns[i]={INT_MIN,INT_MIN,INT_MAX,INT_MAX};
            for (int j=1; j<=k; ++j) {
                int aij; cin>>aij;
                if (aij%2) {
                    turns[i].mno=min(turns[i].mno,aij);
                    turns[i].mxo=max(turns[i].mxo,aij);
                } else {
                    turns[i].mne=min(turns[i].mne,aij);
                    turns[i].mxe=max(turns[i].mxe,aij);
                }
            }
        }
        solve();
    }
}
