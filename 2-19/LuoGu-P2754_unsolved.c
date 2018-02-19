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

const int MAXN=14+2, MAXM=20, MAXT=1000+1;
const int MAXV=MAXN*MAXT+20, MAXE=MAXT*(MAXM+2)+MAXV+20;
const int INF=0x3f3f3f3f;
int n,m,k,S=MAXV-2,T=MAXV-1;

struct Edge{
  int u,v,cap,flow,cost;
};
struct NF{
  int s,t,lim;
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
  void MCMF(int s, int t, LL &flow, LL &cost, int lim){
    this->s=s; this->t=t; this->lim=lim;
    //while(SPFA(flow,cost));
    SPFA(flow,cost);
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
        if(d[e.v]>d[u]+e.cost && e.cap>e.flow && e.v%MAXT<=lim){
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

inline int get(int i, int j){
  return i*MAXT+j;
}

int main(void){
  scanf("%d%d%d",&n,&m,&k);
  mf.addEdge(S,0,k,0);
  int l=(n+1)*MAXT; mf.addEdge(l+0,T,INF,0);
  FOR(i,1,MAXT){
    //mf.addEdge(get(n+1,i),T,INF,0);
    mf.addEdge(l+i,T,INF,0);
    FORR(j,0,n){
      //mf.addEdge(i-1,i,INF,1);
      //mf.addEdge(l+i-1,l+i,INF,1);
      mf.addEdge(get(j,i)-1,get(j,i),INF,1);  //等待
    }
  }
  FORR(i,1,m){
    int h,r,x[40]; scanf("%d%d",&h,&r);
    FOR(i,0,r) scanf("%d",&x[i]);
    FOR(i,0,MAXT-1) mf.addEdge(get(x[i%r],i),get(x[(i+1)%r],i+1),h,1);  //转移
  }
  
  LL flow=0,cost=0;
  FOR(i,1,MAXT){
    mf.MCMF(S,T,flow,cost,i);
    if(flow>=k) break;
  }
//printf("  flow: %lld, cost: %lld\n",flow,cost);

  printf("%lld\n", flow<k ? 0 : cost );

  return 0;
}
