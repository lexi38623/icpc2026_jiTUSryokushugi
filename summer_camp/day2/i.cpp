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
#define rep(i,l,r) for(auto i = (l); i < (r); ++i)
#define drep(i,l,r) for(auto i = (r)-1; i >= (l); --i)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
using namespace std;
using uint = unsigned int; using ll = long long; using ull = unsigned long long;
using pii = pair<int,int>; using pli = pair<ll,int>; using pil = pair<int,ll>; using pll = pair<ll,ll>;
template<class T> using Pq = priority_queue<T>; template<class T> using pQ = priority_queue<T, vector<T>, greater<T>>;
template<class T, class U> inline bool chmin(T& a, const U& b) { if (a > b) { a = b; return true; } return false; }
template<class T, class U> inline bool chmax(T& a, const U& b) { if (a < b) { a = b; return true; } return false; }
inline void yesno(bool p) { if (p) cout << "Yes\n"; else cout << "No\n"; }
const int INF = numeric_limits<int>::max(); const ll LINF = numeric_limits<ll>::max();

// kactl
#define sz(x) (int)(x).size()
typedef vector<int> vi;

void testcase();

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int T = 1;
    cin >> T;
    rep(i,0,T) testcase();
    return 0;
}

struct Tree {
    static constexpr ll unit = 0;
    ll f(ll a, ll b) { return max(a,b); };
    vector<ll> s; ll n;
    Tree(ll n=0,ll def=unit) : s(2*n,def), n(n) {}
    void update(ll pos, ll val){
        for(s[pos+=n]=val;pos/=2;)
            s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    ll query(ll b, ll e) { // [b,e)
        ll ra = unit, rb = unit;
        for(b+=n,e+=n;b<e;b/=2,e/=2){
            if(b%2) ra = f(ra,s[b++]);
            if(e%2) rb = f(s[--e],rb);
        }
        return f(ra,rb);
    }
};

void testcase(){
    ll n,m,k;
    cin>>n>>m>>k;
    vector<ll> p(n);
    rep(i,0,n)cin>>p[i];
    vector<ll> s(n+1,0);
    rep(i,0,n) s[i+1] = s[i]+p[i];
    vector<pii> lr(m);
    for(auto& [l,r] : lr)cin>>l>>r, l--;
    sort(all(lr),[](pii a, pii b){
        if(a.second!=b.second) return a.second < b.second;
        return a.first < b.first;
    });

    Tree dp(n+1);
    for(auto [l,r] : lr){
        dp.update(r,dp.query(0,l+1)+(s[r]-s[l]));
    }

    ll ans = dp.query(0,n+1);
    ans *= k;
    cout<<ans<<'\n';
    // rep(i,0,n+1)cout<<dp.query(i,i+1)<<" \n"[i==n];
    return;
}