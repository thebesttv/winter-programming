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

const int MAXN=120, MAXV=MAXN<<1, MAXE=MAXV*MAXV;
const int INF=0x3f3f3f3f;
int n,m,S=0,T=MAXV-1;
char t1[20],t2[20];
bool vis[MAXN];
struct Node{
  char s[20];
  int num;

  bool operator < (const Node &b) const {
    return strcmp(s,b.s)<0;
  }
}node[MAXN];
set<Node> st;

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

void insert(char *s, int num){
  node[num].num=num; strcpy(node[num].s,s);
  st.insert(node[num]);
}
int getNum(char *s){
  Node t; strcpy(t.s,s);
  set<Node>::iterator it = st.find(t);
  return (*it).num;
}

int main(void){
  scanf("%d%d",&n,&m);
  FORR(i,1,n){
    scanf("%s",t1); insert(t1,i);
    mf.addEdge(i,i+n,((i==1 || i==n) ? 2 : 1),-1);
  }
  mf.addEdge(S,1,2,0); mf.addEdge(n+n,T,2,0);
  FORR(i,1,m){
    scanf("%s%s",t1,t2);
    int u=getNum(t1), v=getNum(t2);
    if(u>v) swap(u,v);  //<b> 防止出现负环 </b>
    //mf.addEdge(u+n,v,1,0);
    mf.addEdge(u+n,v,INF,0);
  }

  LL flow,cost; mf.MCMF(S,T,flow,cost);
#ifdef DEBUG
  printf("  flow: %lld, cost: %lld\n",flow,cost);
#endif
  if(flow<2) printf("No Solution!\n");
  else{
    printf("%lld\n",-2-cost);
    int u=1+n;
    while(u!=(n<<1)){
      printf("%s\n",node[u-n].s);
      FOR(i,0,mf.G[u].size()){
        Edge &e=mf.edge[mf.G[u][i]];
        if(e.cap>0 && e.v<=n && e.v!=S && !e.cost && e.flow>0){
          vis[e.v]=1; u=e.v+n; break;
        }
      }
    }
    printf("%s\n",node[n].s); vis[n]=0;
    stack<int> st2; u=1+n;
    while(u!=(n<<1)){
      st2.push(u-n);
      FOR(i,0,mf.G[u].size()){
        Edge &e=mf.edge[mf.G[u][i]];
        if(e.cap>0 && e.v<=n && e.v!=S && !e.cost && e.flow>0 && !vis[e.v]){
          u=e.v+n; break;
        }
      }
    }
    while(!st2.empty()) {printf("%s\n",node[st2.top()].s); st2.pop();}
  }

  return 0;
}
