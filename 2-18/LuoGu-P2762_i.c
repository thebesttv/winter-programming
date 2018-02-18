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

const int MAX=120;
const int INF=0x3f3f3f3f;
int n,m,s=0,t=MAX-1;
char t1[1000];

struct Edge{
  int u,v,cap,flow;
};
struct MF{
  int s,t;
  Edge edge[(MAX*MAX)<<1];
  VR<int> G[MAX]; int tail;
  int d[MAX],cur[MAX];

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
  scanf("%d%d",&m,&n);
  int ans=0;
  FORR(i,1,m){
    do FGETS(t1); while(!isdigit(t1[0]));
    char *p=strtok(t1," \n\r");
    ans+=atoi(p);
    mf.addEdge(s,i,atoi(p));
    p=strtok(NULL," \n\r");
    while(p){
      mf.addEdge(i,m+atoi(p),INF);
      p=strtok(NULL," \n\r");
    }
  }
  FORR(i,1,n){
    int x; scanf("%d",&x);
    if(x) mf.addEdge(m+i,t,x);
  }

  ans-=mf.maxFlow(s,t);

  FORR(i,1,m) if(mf.d[i]) printf("%d ",i); printf("\n");
  FORR(i,m+1,m+n) if(mf.d[i]) printf("%d ",i-m); printf("\n");
  printf("%d\n",ans);

  return 0;
}
