#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sig(x) (x<0?-1:1)
#define sz(x) ((int)size(x))
#define all(x) begin(x),end(x)
#define all1(x) begin(x)+1,end(x)
template <typename T> T fdiv(T a, T b) {return a/b-(sig(a)/sig(b)==-1 && a%b);}
template <typename T> T cdiv(T a, T b) {return a/b+(sig(a)/sig(b)==1 && a%b);}
template <typename T> using vec=vector<T>;
template <typename T> struct vec2:vector<vector<T>> {vec2()=default;vec2(int n, int m, T val=T()):vector<vector<T>>(n,vector<T>(m,val)){}};
template <typename T> struct vec3:vector<vector<vector<T>>> {vec3()=default;vec3(int n, int m, int k, T val=T()):vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(k,val))){}};
#define PTX x
#define PTY y
struct pt_t {int PTX,PTY;bool operator==(pt_t pt2)const{return PTX==pt2.PTX&&PTY==pt2.PTY;}};

const int N=100;
int n;
ll tx,ty;
ll a[N+1], b[N+1], c[N+1];

bool ok(ll z) {
    ll mn=max(0ll,z-ty+1), mx=min(z,tx-1);
    for (int i=1; i<=n; ++i) {
        ll d=a[i]-b[i],
           r=a[i]*tx+b[i]*ty-c[i]-b[i]*z;

        if (d>0) {
            mn=max(mn, cdiv(r,d));
        } else if (d<0) {
            mx=min(mx, fdiv(r,d));
        } else { // d==0
            if (r>0) {
                return false;
            }
        }
    }

    return mn<=mx;
}

void solve() {
    ll lo=-1, hi=tx+ty-2;
    while (lo+1<hi) {
        ll z=(lo+hi)/2;
        if (ok(z)) hi=z;
        else lo=z;
    }

    ll ans=hi;
    printf("%lld\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin>>t;
    while (t--) {
        cin>>n>>tx>>ty;
        for (int i=1; i<=n; ++i) cin>>a[i]>>b[i]>>c[i];
        solve();
    }
}
