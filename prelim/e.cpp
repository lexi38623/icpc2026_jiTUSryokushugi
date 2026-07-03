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
    int n; cin >> n;
    if(n == 0) return false;
    vector<ll> a(n),b(n);
    vector<pair<ll,ll>> c,d;
    rep(i,0,n){
        cin >> a[i] >> b[i];
        if(b[i] == 0) c.push_back({a[i],0});
        else d.push_back({a[i],b[i]});
    }
    sort(all(c));
    sort(all(d));
    if(d.size() == 0){
        ll ans=0;
        rep(i,0,n) ans+=a[i];
        cout << ans << "\n";
        return true;
    }

    ll gem=0;
    rep(i,0,n)gem+=b[i];
    if(gem>=n-1){
        cout << d[0].first << "\n";
        return true;
    }

    ll ans = LINF;
    rep(x,1,d.size()+1){
        ll now = 0;
        ll k = gem-(d.size()-x);
        rep(i,0,x) now += d[i].first;
        if(c.size()>k){
            rep(i,0,c.size()-k) now += c[i].first;
        }
        chmin(ans,now);
    }
    cout<<ans<<"\n";
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(solve()) {}
    return 0;
}
