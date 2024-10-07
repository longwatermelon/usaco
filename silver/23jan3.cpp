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
    keep going in current dir until next x.5 crossing is less than cur
*/

const int N=1e5;
int n;
int a[N];

void solve() {
    string ans(n,'R');
    for (int x=0; x<n; ++x) a[x]--;

    int x=n;
    char d='L';
    while (a[0]>0) {
        if (d=='L') {
            // change dir?
            if (x==0 || (x!=n && a[x-1]<a[x]+1)) {
                d='R';
            }
        } else { // d=='R'
            // change dir?
            if (x==n || (x!=0 && a[x]<a[x-1]+1)) {
                d='L';
            }
        }

        ans+=d;
        a[x-(d=='L')]--;
        x+=d=='L'?-1:1;
    }

    printf("%s\n", ans.c_str());
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=0; i<n; ++i) cin>>a[i];
    solve();
}
