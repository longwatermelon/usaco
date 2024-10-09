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
    fill b in order. when determining b[i], b[1..i-1] should be set already
    for b[i], only useful information is min/max(b[j],...,b[i-1]), r[j][i], and r[j][i-1] for all j in [1,i-1].
    these are the only r values granular enough to uniquely determine something about b[i].

    r[j][i]==r[j][i-1] ===> b[i] is not a unique min or max, but we know it's in the range of [min(b[j],...,b[i-1]), max(b[j],...,b[i-1])]
        make sure to filter range to range that overlaps with all ranges
    r[j][i]!=r[j][i-1] ===> b[i] is a unique min or max. either min(b[j],...,b[i-1])-(r[j][i]-r[j][i-1]) or max(b[j],...,b[i-1])+(r[j][i]-r[j][i-1])
        make sure to filter the potential values to what's shared by all instances of this

    in the end, if no specific values b[i] can take on (possible if b[i]==b[i-1]), take lower bound. otherwise take any potential value
*/

const int N=300;
int n;
int r[N+1][N+1];

void solve() {
    vec<int> b(n+1);
    b[1]=0;
    for (int i=2; i<=n; ++i) {
        set<int,greater<int>> vals;
        int lo=-1e9, hi=1e9;

        for (int j=1; j<=i-1; ++j) {
            // looking at range [j,i]
            int premn=INT_MAX, premx=INT_MIN;
            for (int k=j; k<=i-1; ++k) {
                premn=min(premn,b[k]);
                premx=max(premx,b[k]);
            }

            if (r[j][i]==r[j][i-1]) {
                // b[i] not unique min/max
                lo=max(lo,premn);
                hi=min(hi,premx);
            } else {
                // b[i] unique min/max
                // new potential values
                set<int> valsp={
                    premx + (r[j][i]-r[j][i-1]),
                    premn - (r[j][i]-r[j][i-1]),
                };

                // intersect w/ old potential values (empty vals indicates all values)
                set<int> res;
                for (int x:valsp) {
                    if (empty(vals) || vals.find(x)!=end(vals)) {
                        res.insert(x);
                    }
                }

                // only keep vals in [lo,hi] range
                vals.clear();
                for (int x:res) {
                    if (lo<=x && x<=hi)
                        vals.insert(x);
                }
            }
        }

        b[i]=!empty(vals) ? *begin(vals) : lo;
    }

    for (int i=1; i<=n; ++i) {
        printf("%d%c", b[i], " \n"[i==n]);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) {
        for (int j=i; j<=n; ++j) {
            cin>>r[i][j];
        }
    }
    solve();
}
