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

// 時計回り
void rotate(vector<int> &p){
    int n=p.size();
    vector<int> res(n);
    rep(i,0,n){
        res[p[i]]=n-i-1;
    }
    p=res;
}

void testcase(){
    int n; cin >> n;
    vector<int> p(n);
    rep(i,0,n){
        cin >> p[i];
        p[i]--;
    }
    int cnt=0;
    if(p[0] == n-1){
        rotate(p);
        cnt++;
    }
    else if(p[n-1] == 0){
        rotate(p);
        rotate(p);
        rotate(p);
        cnt+=3;
    }
    else if(p[n-1] == n-1){
        rotate(p);
        rotate(p);
        cnt+=2;
    }

    vector<pair<int,int>> ans;
    ans.push_back({p[0],0});
    vector<bool> seen(n,false);
    seen[0]=true;
    rep(i,1,n){
        int x=ans.back().first;
        if(x>p[i]){
            ans.push_back({x,i});
            ans.push_back({p[i],i});
            seen[i]=true;
        }
    }
    ans.emplace_back(n-1,n-1);
    drep(i,0,n){
        
    }

    return;
}