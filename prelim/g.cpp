#include <iostream>
#include <iomanip>
#include <algorithm>
#include <array>
#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <numeric>
#include <random>
#include <functional>
#include <cctype>
#include <cmath>
#include <complex>
#include <ctime>
#include <cassert>
using namespace std;
#define rep(i,l,r) for(auto i = (l); i < (r); ++i)
#define drep(i,l,r) for(auto i = (r)-1; i >= (l); --i)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
using uint = unsigned int; using ll = long long; using ull = unsigned long long;
using pii = pair<int,int>; using pli = pair<ll,int>; using pil = pair<int,ll>; using pll = pair<ll,ll>;
template<class T, class U> inline bool chmin(T& a, const U& b) { if (a > b) { a = b; return true; } return false; }
template<class T, class U> inline bool chmax(T& a, const U& b) { if (a < b) { a = b; return true; } return false; }
const int INF = numeric_limits<int>::max(); const ll LINF = numeric_limits<ll>::max();

// #include <atcoder/fenwicktree>
// #include <atcoder/segtree>
// #include <atcoder/lazysegtree>
// #include <atcoder/string>
// #include <atcoder/math>
// #include <atcoder/convolution>
#include <atcoder/modint>
// #include <atcoder/dsu>
// #include <atcoder/maxflow>
// #include <atcoder/mincostflow>
// #include <atcoder/scc>
// #include <atcoder/twosat>
using namespace atcoder;
using mint = atcoder::modint998244353;

bool solve() {
    int n,m; cin >> n >> m;
    if(n == 0) return false;

    vector<string> s(n);
    rep(i,0,n) cin >> s[i];

    vector dp1(n,vector<mint>(m));
    vector dp2(n,vector<mint>(m));
    vector rdp1(n,vector<mint>(m));
    vector rdp2(n,vector<mint>(m));

    dp1[0][0]=1;
    dp2[n-1][0]=1;
    rep(i,0,n)rep(j,0,m){
        if(s[i][j] == '#') continue;
        if(i && s[i-1][j] == '.') dp1[i][j]+=dp1[i-1][j];
        if(j && s[i][j-1] == '.') dp1[i][j]+=dp1[i][j-1];
    }
    for(int i=n-1;i>=0;i--)rep(j,0,m){
        if(s[i][j] == '#') continue;
        if(i<n-1)dp2[i][j]+=dp2[i+1][j];
        if(j)dp2[i][j]+=dp2[i][j-1];
    }

    rdp1[n-1][m-1]=1;
    rdp2[0][m-1]=1;
    for(int i=n-1;i>=0;i--)for(int j=m-1;j>=0;j--){
        if(s[i][j] == '#') continue;
        if(i<n-1) rdp1[i][j]+=rdp1[i+1][j];
        if(j<m-1) rdp1[i][j]+=rdp1[i][j+1];
    }
    rep(i,0,n)for(int j=m-1;j>=0;j--){
        if(s[i][j] == '#') continue;
        if(i) rdp2[i][j]+=rdp2[i-1][j];
        if(j<m-1) rdp2[i][j]+=rdp2[i][j+1];
    }

    mint ans=0;
    ans+=dp1[n-1][m-1]*dp2[0][m-1];

    auto dist=[](int i,int j,int x,int y) -> int{
        return abs(i-x)+abs(j-y);
    };
    rep(i,0,n)rep(j,0,m){
        if(s[i][j] == '#') continue;
        if((dist(0,0,i,j) == dist(n-1,0,i,j)) || (dist(0,0,i,j)-1 == dist(n-1,0,i,j))){
            ans-=dp1[i][j]*dp2[i][j]*rdp1[i][j]*rdp2[i][j];
            if(j) ans+=dp1[i][j-1]*dp2[i][j-1]*rdp1[i][j]*rdp2[i][j];
        }
    }
    cout << ans.val() << "\n";

    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(solve()) {}
    return 0;
}
