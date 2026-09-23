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

void testcase(){
    int n;
    cin>>n;

    string t;
    if(n&1) t = 'a';
    else t = "aa";
    int c = 0;
    rep(i,0,n/2){
        cout<<"? "<<t<<endl;
        int k;
        cin>>k;
        if(i==0) c = k;
        if(k%2==0){
            t[0] = 'b';
            t.back() = 'b';
        }
        if(i!=n/2-1) t = 'a'+t+'a';
    }
    if(n&1){
        int cnt = 0;
        for(char a : t){
            if(a=='a') cnt++;
        }
        if(c==cnt) t = 'b'+t+'b';
        else t = 'a'+t+'a';
    }
    cout<<"! "<<t<<endl;
    return;
}