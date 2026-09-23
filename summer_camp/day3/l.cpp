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
const int INF = numeric_limits<int>::max(); const ll LINF = numeric_limits<ll>::max()/2;

// kactl
#define sz(x) (int)(x).size()
typedef vector<int> vi;

void testcase();

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int T = 1;
    // cin >> T;
    rep(i,0,T) testcase();
    return 0;
}

struct segtree {
    static constexpr ll unit = 0;
    ll f(ll a, ll b) {return max(a,b); }
    vector<ll> s; int n;
    segtree(int n, ll def = unit) : s(2*n,def),n(n) {}
    void update(int pos, ll val) {
        for(s[pos+=n]=val;pos/=2;){
            s[pos] = f(s[pos*2],s[pos*2+1]);
        }
    }
    ll query(int b, int e) { // [b,e)
        ll ra = unit, rb = unit;
        for(b+=n,e+=n;b<e;b/=2,e/=2){
            if(b%2) ra = f(ra,s[b++]);
            if(e%2) rb = f(s[--e],rb);
        }
        return f(ra,rb);
    }
};

void testcase(){
    int n,m; cin >> n >> m;
    string s; cin >> s;
    vector<pair<char,int>> rle;
    rep(i,0,n){
        if(rle.empty() || rle.back().first!=s[i]) rle.emplace_back(s[i],1);
        else rle.back().second++;
    }
    vector<set<int>> es(n+1);
    map<pair<int,int>,ll> mp;
    rep(i,0,m){
        ll x,y; cin >> x >> y;
        es[x].emplace(y);
        ll c; cin >> c;
        mp[{x,y}]+=c;
    }

    segtree dp(n+1);
    int N = rle.size();
    rep(i,1,n+1) dp.update(i,-LINF);
    int ly = 0, hy = 0, x = 0;
    rep(i,0,N){
        auto [d,c] = rle[i];
        if(d=='R'){
            rep(j,0,c){
                auto it = es[x].lower_bound(ly);
                while(it!=es[x].end() && *it<=hy){
                    dp.update(*it,dp.query(*it,*it+1)+mp[{x,*it}]);
                    it++;
                }
                x++;
            }
        }
        if(d=='U'){
            
            // auto it = es[x].lower_bound(ly+1);
            // while(it!=es[x].end() && *it<=hy){
            //     ll now = dp.query(*it,*it+1);
            //     ll next = dp.query(*it-c,*it)+mp[{x,*it}];
            //     if(next>now) dp.update(*it,next);
            //     it++;
            // }
            // ly++;
            // hy++;
        }
        if(d=='?'){
            
        }
        
    }


    // vector<pair<int,int>> range(n+1);
    // int mx=0,my=0,Mx=0,My=0;
    // rep(i,0,n){
    //     if(s[i] == 'R'){
    //         mx++;
    //         Mx++;
    //         range[mx].first=my;
    //         chmax(range[Mx].second,My);
    //     }
    //     else if(s[i] == 'U'){
    //         my++;
    //         My++;
    //         chmax(range[Mx].second,My);
    //     }
    //     else{
    //         mx++;
    //         range[mx].first=my;
    //         My++;
    //         chmax(range[Mx].second,My);
    //     }
    // }
    // cout << mx << " " << my << "\n";
    // cout << Mx << " " << My << "\n";
    // chmin(range[mx].first,my);
    // chmax(range[Mx].second,My);
    // rep(i,Mx,mx+1) chmax(range[i].second,My-(i-Mx));

    // rep(i,0,n+1){
    //     cout << range[i].first << " " << range[i].second << "\n";
    // }
    // for(auto [x,y]:st){
    //     cout << "[" << x << "," << y << "]\n";
    //     if(range[x].first>y || range[x].second<y) continue;
    //     else{
    //         ll tmp=dp.query(range[x].first,y+1)+mp[{x,y}];
    //         chmax(tmp,dp.query(y,y+1));
    //         dp.update(y,tmp);
    //     }
    //     cout << "dp:";
    //     rep(j,0,n+1){
    //         cout << dp.query(j,j+1) << " ";
    //     }
    //     cout << "\n";
    // }
    // ll ans=0;
    // rep(i,0,n+1) chmax(ans,dp.query(i,i+1));
    // cout << ans << "\n";

    return;
}