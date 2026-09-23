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
    // cin >> T;
    rep(i,0,T) testcase();
    return 0;
}

struct UF {
    vi e;
    UF(int n) : e(n,-1) {}
    bool same(int a, int b) { return find(a)==find(b); }
    int size(int x) { return -e[find(x)];}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]);}
    bool join(int a, int b){
        a = find(a), b = find(b);
        if(a==b) return false;
        if(e[a]>e[b]) swap(a,b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

void testcase(){
    int n,m;
    cin>>n>>m;
    vector<pii> es;
    UF uf(n);
    rep(i,0,m){
        int a,b; char c;
        cin>>a>>b>>c;
        a--; b--;
        if(c=='o') uf.join(a,b);
        else es.emplace_back(a,b);
    }

    if(uf.size(0)==n){
        cout<<"No\n";
        return;
    }

    vector<vector<int>> g(n);
    for(auto& [a,b] : es){
        a = uf.find(a);
        b = uf.find(b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> col(n,-1);
    rep(i,0,n)if(i==uf.find(i) && col[i]==-1){
        auto dfs = [&](auto dfs, int v, int c) -> bool {
            if(col[v]!=-1 && col[v]!=c) return false;
            if(col[v]!=-1) return true;
            if(col[v]==-1) col[v] = c;
            for(int u : g[v]){
                if(!dfs(dfs,u,c^1)) return false;
            }
            return true;
        };
        if(!dfs(dfs,i,0)){
            cout<<"No\n";
            return;
        }
    }
    cout<<"Yes\n";
    return;
}