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

const int MAX=1120;
const int INF=0x3f3f3f3f;
int n,s,t,S=0,T=MAX-1;
bool vis[MAX],stat[MAX];  //从 s->t 遍历一遍后的结果，stat: 每个点是否有障碍物
int d[MAX]; bool inq[MAX];

struct Edge2{
  int v,next;
}edge[MAX<<1];
int se[MAX],tail=1;
void addEdge(int u, int v){
  edge[tail]=(Edge2){v,se[u]}; se[u]=tail++;
}
struct NF{
  int s,t,tail;
  struct Edge{
    int u,v,cap,flow,cost;
  }edge[MAX<<3];
  VR<int> G[MAX];
  int p[MAX],a[MAX],d[MAX];

  void addEdge(int u, int v, int cap, int cost){
    edge[tail++]=(Edge){u,v,cap,0,cost};
    edge[tail++]=(Edge){v,u,0,0,-cost};
    G[u].push_back(tail-2);
    G[v].push_back(tail-1);
  }
  bool SPFA(int &flow, int &cost){
    MST(d,INF); MST(inq,0);
    queue<int> q; q.push(s), inq[s]=1, d[s]=0;
    p[s]=0; a[s]=INF; //<b> </b>
    while(!q.empty()){
      int u=q.front(); q.pop();
      inq[u]=0; //<b> </b>
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
    flow+=a[t]; cost+=a[t]*d[t];
    for(int u=t;u!=s;u=edge[p[u]].u){
      edge[p[u]].flow+=a[t];
      edge[p[u]^1].flow-=a[t];
    }
    return true;
  }
  void MCMF(int s, int t, int &flow, int &cost){
    flow=cost=0; this->s=s; this->t=t;
    while(SPFA(flow,cost));
  }
}mf;

void SPFA(int s){
  MST(inq,0); MST(d,0x3f);
  queue<int> q; q.push(s); inq[s]=1, d[s]=0;
  while(!q.empty()){
    int u=q.front(); q.pop();
    inq[u]=0;
    for(int i=se[u];i;i=edge[i].next){
      Edge2 &e=edge[i]; inq[e.v]=0;
      if(d[e.v]>d[u]+1){
        d[e.v]=d[u]+1;
        if(!inq[e.v]) q.push(e.v), inq[e.v]=1;
      }
    }
  }
}
bool mark(int u){
  vis[u]=1; if(u==t) return true;
  for(int i=se[u];i;i=edge[i].next){
    Edge2 &e=edge[i];
    if(d[e.v]==d[u]+1 && !vis[e.v]){
      vis[e.v]=1;
      if(mark(e.v)) return true;
      vis[e.v]=0;
    }
  }
  return false;
}

int main(void){
  scanf("%d%d%d",&n,&s,&t); s++,t++;
  int x,k,sum=0;
  FORR(i,1,n){
    scanf("%d%d",&x,&k); stat[i]=!x;
    while(k--) scanf("%d",&x), mf.addEdge(i,x+1,INF,1), addEdge(i,x+1);
  }
  SPFA(s); mark(s);
  FORR(i,1,n){
    if(stat[i]) mf.addEdge(S,i,1,0), sum++;
    if(!vis[i]) mf.addEdge(i,T,1,0);  //<b> 不是 else if </b>
  }
  int flow,cost; mf.MCMF(S,T,flow,cost);
  if(flow<sum) printf("No solution！\n");
  else printf("%d\n",cost+d[t]);

  return 0;
}
