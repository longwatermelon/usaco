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
    compute min # cycles needed for winner in each room
    one player can always maintain winning invariant: a[i]=0 (mod 4) because any a[i] mod 4 (1,2,3) has a complementary "prime" (1,2,3)
    losing player always choose P=2 because the only prime with mod 4 = 2 is 2. (2k+2 divisible by 2 for k>0)
    also optimal because a[i] decreases by at least 4 on each pair of turns by choice of player maintaining winning invariant, which this achieves.

    if a[i]!=0 (mod 4) in beginning, FJ is winning and has a chance to choose P>2 if a[i]!=2 (mod 4). split prime list by mod 4 to binary search on FJ's initial prime <= a[i].
    then both alternate choosing P=2.

    if a[i]=0 (mod 4) in beginning, FJ is losing and should choose P=2. FJ and FN alternate P=2 until a[i]=0
*/

bool prime[int(5e6)+1];
vec<int> primes[4];

void sieveofe() {
    prime[1]=false;
    fill(prime+2,prime+1+(int)5e6,true);
    for(int i=2; i*i<=5e6; ++i) {
        int j=i;
        while(i*j<5e6) {
            prime[i*j]=false;
            ++j;
        }
    }
}

const int N=2e5;
int n;
int a[N+1];

// # turns for loss on a[i]
int turns(int ai, bool &fj) {
    int r=ai%4;
    fj=r!=0;

    if (r) {
        // fj wins
        int lo=0, hi=sz(primes[r]);
        while (lo+1<hi) {
            int idx=(lo+hi)/2;
            if (primes[r][idx]<=ai) lo=idx;
            else hi=idx;
        }

        int p=primes[r][lo];
        return (ai-p)/4+1;
    } else {
        // fn wins
        return ai/4+1;
    }
}

void solve() {
    int mnturns=INT_MAX;
    bool fj=false;
    for (int i=n; i>=1; --i) {
        bool win;
        int turnsi=turns(a[i],win);
        if (turnsi<=mnturns) {
            mnturns=turnsi;
            fj=win;
        }
    }

    puts(fj?"Farmer John":"Farmer Nhoj");
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieveofe();
    primes[1]={1};
    for (int x=2; x<=5e6; ++x) {
        if (prime[x])
            primes[x%4].push_back(x);
    }

    int _; cin>>_;
    while (_--) {
        cin>>n;
        for (int i=1; i<=n; ++i) cin>>a[i];
        solve();
    }
}
