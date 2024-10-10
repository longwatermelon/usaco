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
    check relative ordering of all character pairs (x,y), ok[x][y]=same
    also check if each restricted character has same counts in both strings
    if all character pairs (x,y) in query string r satisfy ok[x][y] and same counts, ans=Y else N
*/

const int Q=1e5;
int n;
string s,t;
int q;
string qu[Q+1];

bool ok[256][256];
int cnts[256], cntt[256];

vec<int> freqs(string str, char x, char y) {
    vec<int> res={0};
    int l=min(find(all1(str),x)-begin(str),find(all1(str),x)-begin(str));
    for (int i=l; i<=n; ++i) {
        if (str[i]==str[l]) {
            // is cur character
            res.back()++;
        } else if (str[i]==x || str[i]==y) {
            // is other character
            res.push_back(1);
            l=i;
        }
    }

    return res;
}

void solve() {
    for (int i=1; i<=n; ++i) {
        cnts[(int)s[i]]++;
        cntt[(int)t[i]]++;
    }

    memset(ok,true,sizeof(ok));
    for (int x='a'; x<='r'; ++x) {
        for (int y=x+1; y<='r'; ++y) {
            ok[x][y]=freqs(s,x,y)==freqs(t,x,y);
        }
    }

    for (int _=1; _<=q; ++_) {
        string r=qu[_];
        vec<bool> in(256,false); // included in s,t
        for (char c:r) in[c]=true;

        bool ans=true;
        // check relative ordering
        for (int x='a'; x<='r'; ++x) {
            for (int y=x+1; y<='r'; ++y) {
                if (in[x] && in[y]) {
                    ans&=ok[x][y];
                }
            }
        }

        // check counts
        for (int x='a'; x<='r'; ++x) {
            if (in[x])
                ans&=cnts[x]==cntt[x];
        }

        putchar(ans?'Y':'N');
    }
    putchar('\n');
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>s>>t;
    n=sz(s);
    s.insert(begin(s),' ');
    t.insert(begin(t),' ');

    cin>>q;
    for (int i=1; i<=q; ++i) cin>>qu[i];
    solve();
}
