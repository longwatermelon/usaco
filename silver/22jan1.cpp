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
    go x->y
    get to x<y with div and +1 greedily
    reduce adds by pushing behind multiplications
    try all possible number of divs until x=1 to create more multiplication buffer
*/

int n;
ll x,y;

void solve() {
    // divs
    int div=0;
    while (x>y) {
        if (x%2) x++;
        else x/=2;
        div++;
    }

    int ans=INT_MAX;
    while (x>1) {
        // mul, add
        int mul=log2((float)y/x);
        ll add=y-x*(1<<mul);

        // reduce add
        int d=0;
        for (int i=1; i<=mul; ++i) {
            d+=add%2;
            add/=2;
        }
        d+=add;
        ans=min(ans,div+mul+d);

        // try next iter of x
        if (x%2) {
            div++;
            x++;
        }
        div++;
        x/=2;
    }

    if (ans==INT_MAX) ans=0;
    printf("%d\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n; ++i) {
        cin>>x>>y;
        solve();
    }
}
