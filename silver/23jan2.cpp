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

const int N=1500;
int n;
int c[N+2][N+2];

int cnt[N+1][N+1];

int solve(int i, int j) {
    int costchg=0; // cost change

    int row=i, col=j;
    while (row<=n && col<=n) {
        (c[row][col]=='R'?col:row)++;
        cnt[row][col]-=cnt[i][j];
    }
    costchg-=c[row][col]*cnt[i][j];

    row=i, col=j;
    c[row][col]=c[row][col]=='R'?'D':'R';
    while (row<=n && col<=n) {
        (c[row][col]=='R'?col:row)++;
        cnt[row][col]+=cnt[i][j];
    }
    costchg+=c[row][col]*cnt[i][j];

    return costchg;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for (int i=1; i<=n+1; ++i) {
        for (int j=1; j<=n+1; ++j) {
            if (i==n+1 && j==n+1) break;
            if (i==n+1 || j==n+1) {
                cin>>c[i][j];
            } else {
                char x; cin>>x;
                c[i][j]=x;
            }
        }
    }

    int cost=0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            int row=i, col=j;
            while (row<=n && col<=n) {
                cnt[row][col]++;
                (c[row][col]=='R'?col:row)++;
            }
            cost+=c[row][col];
        }
    }
    printf("%d\n", cost);

    int q; cin>>q;
    while (q--) {
        int i,j; cin>>i>>j;
        cost+=solve(i,j);
        printf("%d\n", cost);
    }
}
