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
#define PTX l
#define PTY r
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

/*
    always possible to swap ordering of two adjacent characters ===> string ordering doesn't matter
    parity of difference in counts between any two characters are always the same ===> invariant probably
    in the end, C-O parity=1, C-W parity=1, O-W parity=1 (1 C, 0 O, 0 W)
    each operation decreases two parities both by 2, or a single parity by 2
    first check in if statement is actually redundant
*/

int n;
string s;
int q;
vec<pt_t> qu;

void solve() {
    vec2<int> pre(256,n+1);
    for (int i=1; i<=n; ++i) {
        for (char c:"COW") {
            pre[c][i]=pre[c][i-1] + (s[i]==c);
        }
    }

    for (auto &[l,r]:qu) {
        int cntc=pre['C'][r]-pre['C'][l-1],
            cnto=pre['O'][r]-pre['O'][l-1],
            cntw=pre['W'][r]-pre['W'][l-1];

        int p1=cntc-cnto, p2=cntc-cntw, p3=cnto-cntw;
        if ((p1-1 + p2-1 + p3)%4==0 && p1%2 && p2%2 && p3%2==0) {
            putchar('Y');
        } else {
            putchar('N');
        }
    }
    putchar('\n');
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>s;
    n=sz(s);
    s.insert(begin(s),' ');
    cin>>q;
    for (int i=1; i<=q; ++i) {
        pt_t pt; cin>>pt.l>>pt.r;
        qu.push_back(pt);
    }
    solve();
}
