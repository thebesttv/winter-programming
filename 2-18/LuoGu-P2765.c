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

const int MAXV=1600, MAXV_=MAXV*2+20;
const int MAXE=MAXV*MAXV;
const int INF=0x3f3f3f3f;
int k,s=0,t=MAXV_-1;
bool vis[MAXV];

struct Edge{
  int u,v,cap,flow;
};
struct MF{
  int s,t,lim,ans;
  Edge edge[MAXE<<1];
  VR<int> G[MAXV_]; int tail;
  int d[MAXV_],cur[MAXV_];

  void clear(int n){
    s=t=tail=0; FORR(i,0,n) G[i].clear();
  }
  void addEdge(int u, int v, int cap){
    edge[tail++]=(Edge){u,v,cap,0};
    edge[tail++]=(Edge){v,u,0,0};
    G[u].push_back(tail-2);
    G[v].push_back(tail-1);
  }
  int maxFlow(int s, int t, int lim){
    this->s=s; this->t=t; this->lim=lim;
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
        if(e.v-MAXV>lim && e.v!=t) break;
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
      if(e.v-MAXV>lim && e.v!=t) {i=G[u].size(); break;}
      if(d[e.v]==d[u]+1 && e.cap>e.flow && (f=dfs(e.v,min(a,e.cap-e.flow)))>0){
        sum+=f; a-=f;
        e.flow+=f; edge[G[u][i]^1].flow-=f;
        if(!a) break;
      }
    }
    return sum;
  }
  void clearFlow(){
    FOR(i,0,tail) edge[i].flow=0;
    ans=0;  //<b> </b>
  }
}mf;

void init(){
  FORR(i,1,MAXV) mf.addEdge(s,i,1), mf.addEdge(i+MAXV,t,1);
  
  int n=2,n2;
  while((n2=n*n)){
    int l=max(n2-MAXV,1);
    int r=n2>>1; if((r<<1)==n2) r--;
    if(l>r) break;
    FORR(i,l,r) mf.addEdge(i,MAXV+n2-i,1);
    n++;
  }
}

void dfs(int u){
  printf("%d ",u); vis[u]=1;
  FOR(i,0,mf.G[u].size()){
    Edge &e=mf.edge[mf.G[u][i]];
    if(e.cap>0 && e.v>MAXV && e.v!=t && e.flow>0){
      dfs(e.v-MAXV); break;
    }
  }
}

int main(void){
  init(); scanf("%d",&k);
  
  int ans=-1;
  FORR(i,11,MAXV){
    int cut=mf.maxFlow(s,t,i);
    if(i-cut>k) break;
    else ans=i;
  }
  mf.clearFlow();
  mf.maxFlow(s,t,ans);
  printf("%d\n",ans);
  FORR(i,1,ans) if(!vis[i]){
    dfs(i); printf("\n");
  }

  return 0;
}

/*
const int MAXV=1600, MAXV_=MAXV*2+20;
const int MAXE=MAXV*MAXV;
const int INF=0x3f3f3f3f;
int k,s=0,t=MAXV_-1;
bool vis[MAXV];

struct Edge{
  int u,v,cap,flow;
};
struct MF{
  int s,t,lim,ans;
  Edge edge[MAXE<<1];
  VR<int> G[MAXV_]; int tail;
  int d[MAXV_],cur[MAXV_],from[MAXV_],tfrom[MAXV_];

  void clear(int n){
    s=t=tail=0; FORR(i,0,n) G[i].clear();
  }
  void addEdge(int u, int v, int cap){
    edge[tail++]=(Edge){u,v,cap,0};
    edge[tail++]=(Edge){v,u,0,0};
    G[u].push_back(tail-2);
    G[v].push_back(tail-1);
  }
  int maxFlow(int s, int t, int lim){
    this->s=s; this->t=t; this->lim=lim;
    bfs(); MST(cur,0);
    ans+=dfs(s,INF);
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
          if(e.v!=t && e.v-MAXV>lim) break;
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
      if(e.v!=t && e.v-MAXV>lim) {i=G[u].size(); break;}
      if(d[e.v]==d[u]+1 && e.cap>e.flow && (f=dfs(e.v,min(a,e.cap-e.flow)))>0){
        sum+=f; a-=f;
        e.flow+=f; edge[G[u][i]^1].flow-=f;
        if(!a) break;
      }
    }
    return sum;
  }
  void clearFlow(){
    FOR(i,0,tail) edge[i].flow=0;
    ans=0;
  }
}mf;

void init(){
  //先连st
  FORR(i,1,MAXV) mf.addEdge(s,i,1), mf.addEdge(i+MAXV,t,1);
  
  int n=2,n2;
  while((n2=n*n)){
    int r=n2>>1; if(r*2==n2) r--;
    if(max(n2-MAXV,1)>r) break;
    FORR(i,max(n2-MAXV,1),r){
      mf.addEdge(i,MAXV+n2-i,1);
    }
    n++;
  }
}

void dfs(int u){
  printf("%d ",u); vis[u]=1;
  FOR(i,0,mf.G[u].size()){
    Edge &e=mf.edge[mf.G[u][i]];
    if(e.cap>0 && e.v>MAXV && e.v!=t && e.flow>0){
      dfs(e.v-MAXV); break;
    }
  }
}

int main(void){
  init();
  scanf("%d",&k);
  
  int ans=-1;
  FORR(i,11,MAXV){
    int cut=mf.maxFlow(s,t,i);
    if(i-cut>k) break;
#ifdef DEBUG
    printf("  find %d\n",i);
#endif
    ans=i;
  }
  mf.clearFlow();
  mf.maxFlow(s,t,ans);
  printf("%d\n",ans);
  FORR(i,1,ans) if(!vis[i]){
    dfs(i); printf("\n");
  }

  return 0;
}
*/
