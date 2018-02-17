#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<cmath>
#include<ctime>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

#define FOR(i,a,b) for(register int i=(a);i<(b);++i)
#define FORR(i,a,b) for(register int i=(a);i<=(b);++i)
#define ROR(i,a,b) for(register int i=(a);i>=(b);--i)
#define RORR(i,a,b) for(register int i=(a);i>(b);--i)
#define PQ priority_queue
#define VR vector
#define MST(a,b) memset(a,b,sizeof(a))
#define SIZ(a) sizeof(a)
#define CE() clear()
#define FGETS(s) fgets(s,sizeof(s),stdin)
#define RE register
#define FIN(s) freopen(s,"r",stdin)
#define FOUT(s) freopen(s,"w",stdout)
typedef long long LL;
typedef long long unsigned LLU;


const int MAXN=120, MAXM=520;
const int INF=0x3f3f3f3f;
int n,m,s,t;
int d[MAXN];  // d[i]=in[i]-out[i]
VR<int> G[MAXN];
stack<int> st;  //记录欧拉回路

struct Edge{
  int u,v,cap,flow;
};
struct MF{
  int s,t;
  Edge edge[(MAXM+MAXN)<<1];
  VR<int> G[MAXN]; int tail;
  int d[MAXN],cur[MAXN];

  void clear(int n){
    s=t=tail=0; FORR(i,0,n) G[i].clear();
  }
  void addEdge(int u, int v, int cap){
    edge[tail++]=(Edge){u,v,cap,0};
    edge[tail++]=(Edge){v,u,0,0};
    G[u].push_back(tail-2);
    G[v].push_back(tail-1);
  }
  int maxFlow(int s, int t){
    this->s=s; this->t=t;
    int ans=0;
    while(bfs()){
      MST(cur,0); ans+=dfs(s,INF);
    }
    return ans;
  }
  bool bfs(){
    MST(d,0);
    queue<int> q; q.push(s); d[s]=1;
    while(!q.empty()){
      int u=q.front(); q.pop();
      FOR(i,0,G[u].size()){
        Edge &e=edge[G[u][i]];
        if(!d[e.v] && e.cap>e.flow){
          d[e.v]=d[u]+1;
          q.push(e.v);
        }
      }
    }
    return d[t];
  }
  int dfs(int u, int a){
    if(!a || u==t) return a;
    int sum=0,f;
    for(int &i=cur[u];i<G[u].size();i++){
      Edge &e=edge[G[u][i]];
      if(d[e.v]==d[u]+1 && e.cap>e.flow && (f=dfs(e.v,min(a,e.cap-e.flow)))>0){
        sum+=f; a-=f;
        e.flow+=f; edge[G[u][i]^1].flow-=f;
        if(!a) break;
      }
    }
    return sum;
  }
}mf;

void euler(int u){
  FOR(i,0,G[u].size()) if(G[u][i]>0){
    int t=G[u][i]; G[u][i]=-1;
    euler(t);
  }
  st.push(u);
}

int main(void){
  int T; scanf("%d",&T);
  while(T--){
    scanf("%d%d",&n,&m); s=0, t=n+10;
    mf.clear(t); MST(d,0); FORR(i,1,n) G[i].clear();
    int u,v,ch;
    FOR(i,0,m){
      scanf("%d%d",&u,&v);
      d[v]++, d[u]--;
      do ch=getchar(); while(ch!='D' && ch!='U');
      if(ch=='D'){
        G[u].push_back(v);
      }else{
        mf.addEdge(u,v,1);
      }
    }
    bool ok=1; int sum=0;
    FORR(i,1,n){
      if(d[i]&1) {ok=0; break;}
      if(d[i]>0){
        mf.addEdge(i,t,d[i]>>1); sum+=(d[i]>>1);
      }else if(d[i]<0){
        mf.addEdge(s,i,(-d[i])>>1);
      }
    }
    if(!ok || mf.maxFlow(s,t)!=sum){
      printf("No euler circuit exist\n\n"); continue;
    }
    FORR(i,1,n) FOR(j,0,mf.G[i].size()){
      Edge &e=mf.edge[mf.G[i][j]];
      if(e.v>=1 && e.v<=n && e.cap){  // <b> e.cap </b>
        if(e.flow==0) G[i].push_back(e.v);
        else if(e.flow==1) G[e.v].push_back(i);
      }
    }
#ifdef DEBUG
    FORR(i,1,n){
      printf("%d:",i);
      FOR(j,0,G[i].size()) printf(" %d",G[i][j]);
      printf("\n");
    }
#endif
    euler(1);
    while(!st.empty()) {printf("%d ",st.top()); st.pop();} printf("\n\n");
  }

  return 0;
}
