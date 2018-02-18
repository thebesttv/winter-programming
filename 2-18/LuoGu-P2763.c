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

const int MAXV=1120, MAXE=20+1000+1000*20;
const int INF=0x3f3f3f3f;
int n,k,S=0,T=MAXV-1;

struct Edge{
  int u,v,cap,flow;
};
struct MF{
  int s,t;
  Edge edge[MAXE<<1];
  VR<int> G[MAXV]; int tail;
  int d[MAXV],cur[MAXV];

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

int main(void){
  scanf("%d%d",&k,&n);
  int t,p,sum=0;
  FORR(i,1,k) scanf("%d",&t), mf.addEdge(S,i,t), sum+=t;
  FORR(i,1,n){
    mf.addEdge(i+k,T,1);
    scanf("%d",&p);
    while(p--) scanf("%d",&t), mf.addEdge(t,i+k,1);
  }

  if(mf.maxFlow(S,T)<sum) {printf("No Solution!\n"); return 0;}
  FORR(i,1,k){
    printf("%d:",i);
    FOR(j,0,mf.G[i].size()){
      Edge &e=mf.edge[mf.G[i][j]];
      if(e.v>k && e.v!=T && e.cap && e.flow>0) printf(" %d",e.v-k);
    }
    printf("\n");
  }

  return 0;
}
