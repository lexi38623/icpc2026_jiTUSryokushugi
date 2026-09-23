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


template<class E,class V,E (*merge)(E,E),E (*e)(),E (*put_edge)(V,int),V (*put_vertex)(E,int)>
struct RerootingDP{
    struct edge{
        int to,idx,xdi;
    };
    RerootingDP(int n_=0) : n(n_),inner_edge_id(0){
        es.resize(2*n-2);
        start.resize(2*n-2);
        if(n == 1) es_build();
    }
    void add_edge(int u,int v,int idx,int xdi){
        start[inner_edge_id]=u;
        es[inner_edge_id]={v,idx,xdi};
        inner_edge_id++;
        start[inner_edge_id]=v;
        es[inner_edge_id]={u,xdi,idx};
        inner_edge_id++;
        if(inner_edge_id == 2*n-2){
            es_build();
        }
    }
    vector<V> build(int root_ = 0){
        root=root_;
        vector<V> subdp(n); subdp[0]=put_vertex(e(),0);
        outs.resize(n);
        vector<int> geta(n+1,0);
        for(int i=0;i<n;i++) geta[i+1]=start[i+1]-start[i]-1;
        geta[root+1]++;
        for(int i=0;i<n;i++) geta[i+1]+=geta[i];
        auto dfs=[&](auto sfs,int v,int f) -> void{
            E val=e();
            for(int i=start[v];i<start[v+1];i++){
                if(es[i].to == f){
                    swap(es[start[v+1]-1],es[i]);
                }
                if(es[i].to == f) continue;
                sfs(sfs,es[i].to,v);
                E nval=put_edge(subdp[es[i].to],es[i].idx);
                outs[geta[v]++]=nval;
                val=merge(val,nval);
            }
            subdp[v]=put_vertex(val,v);
        };
        dfs(dfs,root,-1);
        return subdp;
    }
    vector<V> reroot(){
        vector<E> reverse_edge(n);
        reverse_edge[root]=e();
        vector<V> answers(n);
        auto dfs=[&](auto sfs,int v) -> void{
            int le=outs_start(v);
            int ri=outs_start(v+1);
            int siz=ri-le;
            vector<E> rui(siz+1);
            rui[siz]=e();
            for(int i=siz-1;i>=0;i--){
                rui[i]=merge(outs[le+1],rui[i+1]);
            }
            answers[v]=put_vertex(merge(rui[0],reverse_edge[v]),v);
            E lui=e();
            for(int i=0;i<siz;i++){
                V rdp=put_vertex(merge(merge(lui,rui[i+1]),reverse_edge[v]),v);
                reverse_edge[es[start[v]+i].to]=put_edge(rdp,es[start[v]+i].xdi);
                lui=merge(lui,outs[le+i]);
                sfs(sfs,es[start[v]+i].to);
            }
        };
        dfs(dfs,root);
        return answers;
    }
    private:
    int n,root,inner_edge_id;
    vector<E> outs;
    vector<edge> es;
    vector<int> start;
    int outs_start(int v){
        int res=start[v]-v;
        if(root < v) res++;
        return res;
    }
    void es_build(){
        vector<edge> nes(2*n-2);
        vector<int> nstart(n+2,0);
        for(int i=0;i<2*n-2;i++) nstart[start[i]+2]++;
        for(int i=0;i<n;i++) nstart[i+1]+=nstart[i];
        for(int i=0;i<2*n-2;i++) nes[nstart[start[i]+1]++]=es[i];
        swap(es,nes);
        swap(start,nstart);
    }
};

struct S{
    ll m1,m2,m3;
};
S merge(S a,S b){
    vector<ll> x={a.m1,a.m2,a.m3};
    x.push_back(b.m1);
    sort(rall(x));
    return {x[0],x[1],x[2]};    
}
S e(){
    return {-INF,-INF,-INF};
}
S put_edge(S v,int i){
    v.m1++;
    v.m2++;
    v.m3++;
    return v;
}
S put_vertex(S e,int i){
    if(e.m1<0) e.m1=0;
    return e;
}

void testcase(){
    int n; cin >> n;
    RerootingDP<S,S,merge,e,put_edge,put_vertex> g(n);
    vector<vector<int>> to(n);
    rep(i,0,n-1){
        int u,v; cin >> u >> v;
        u--,v--;
        g.add_edge(u,v,i,i);
        to[u].push_back(v);
        to[v].push_back(u);
    }

    g.build();
    ll ans=0;
    bool ch=false;
    rep(i,0,n){
        if(to[i].size()>=3) ch=true;
    }
    if(!ch){
        cout << n-1 << "\n";
        return;
    }

    auto G=g.reroot();
    rep(i,0,n)if(G[i].m3>0){
        chmax(ans,2*n-(G[i].m1+G[i].m2+G[i].m3+2));
        cout << "i:" << i << "\n";
        cout << G[i].m1 << " " << G[i].m2 << " " << G[i].m3 << "\n";
    }
    cout << ans << "\n";

    return;
}
