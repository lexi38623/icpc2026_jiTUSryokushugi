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
// #include <atcoder/modint>
// #include <atcoder/dsu>
// #include <atcoder/maxflow>
// #include <atcoder/mincostflow>
// #include <atcoder/scc>
// #include <atcoder/twosat>
// using namespace atcoder;
// using mint = atcoder::modint998244353;

bool solve() {
    ll s,k; cin >> s >> k;
    if(s == 0) return false;
    if(k == 1){
        cout << s << "\n";
        return true;
    }
    if(k>s*s+1){
        k-=s*s+2;
        ll p=k/(2*s)+1; // p段目
        if(k%2 == 0){
            cout << s+p << "\n";
        }
        else{
            k/=2;
            cout << k%s+1 << "\n";
        }
        return true;
    }

    auto judge = [&](ll x) -> bool {
        return 2*s*x-x*x >= k;
    };

    k--;
    ll l = 0, r = s;
    while(r-l>1){
        ll mid = (l+r)/2;
        if(judge(mid)) r = mid; else l = mid;
    }
    // r段目にある
    k -= 2*s*l-l*l;
    // r段目の行のk番目が答え
    if(k%2==0){
        cout<<r<<"\n";
        return true;
    }
    cout<<r+k/2<<"\n";
    
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(solve()) {}
    return 0;
}
