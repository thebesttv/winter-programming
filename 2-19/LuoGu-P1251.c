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

const int MAXN=2020;
const int MAXV=MAXN<<1, MAXE=MAXN*6;
const int INF=0x3f3f3f3f;
int N,p,m,f,n,s,S=0,T=MAXV-1;

struct Edge{
  int u,v,cap,flow,cost;
};
struct NF{
  int s,t;
  Edge edge[MAXE<<1];
  VR<int> G[MAXV]; int tail;
  int d[MAXV],a[MAXV],p[MAXV];
  bool inq[MAXV];

  void addEdge(int u, int v, int cap, int cost){
    edge[tail++]=(Edge){u,v,cap,0,cost};
    edge[tail++]=(Edge){v,u,0,0,-cost};
    G[u].push_back(tail-2);
    G[v].push_back(tail-1);
  }
  void MCMF(int s, int t, LL &flow, LL &cost){
    this->s=s; this->t=t; flow=cost=0;
    while(SPFA(flow,cost));
  }
  bool SPFA(LL &flow, LL &cost){
    MST(d,0x3f); MST(inq,0);
    queue<int> q; q.push(s);
    d[s]=0, a[s]=INF, inq[s]=1, p[s]=0;
    while(!q.empty()){
      int u=q.front(); q.pop();
      inq[u]=0;
      FOR(i,0,G[u].size()){
        Edge &e=edge[G[u][i]];
        if(d[e.v]>d[u]+e.cost && e.cap>e.flow){
          d[e.v]=d[u]+e.cost;
          a[e.v]=min(a[u],e.cap-e.flow);
          p[e.v]=G[u][i];
          if(!inq[e.v]) q.push(e.v), inq[e.v]=1;
        }
      }
    }
    if(d[t]==INF) return false;
    flow+=a[t]; cost+=1LL*a[t]*d[t];
    for(int u=t;u!=s;u=edge[p[u]].u){
      edge[p[u]].flow+=a[t];
      edge[p[u]^1].flow-=a[t];
    }
    return true;
  }
}mf;

int main(void){
  scanf("%d",&N);
  FORR(i,1,N){
    int r; scanf("%d",&r);
    mf.addEdge(S,i,r,0);
    mf.addEdge(i+N,T,r,0);
  }
  scanf("%d%d%d%d%d",&p,&m,&f,&n,&s);
  FORR(i,1,N){
    mf.addEdge(S,i+N,INF,p);
    if(i+1<=N) mf.addEdge(i,i+1,INF,0);
    if(i+m<=N) mf.addEdge(i,i+m+N,INF,f);
    if(i+n<=N) mf.addEdge(i,i+n+N,INF,s);
  }
  LL flow,cost; mf.MCMF(S,T,flow,cost);
  printf("%lld\n",cost);

  return 0;
}
