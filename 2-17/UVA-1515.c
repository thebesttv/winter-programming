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

const int MAX=60;
const int MAX_NODE=MAX*MAX;
const int INF=0x3f3f3f3f;
int n,m,d,b,f,s,t;
int num[MAX][MAX];
bool G[MAX][MAX];
char t1[MAX];
int to[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

struct MF{
  int s,t;
  struct Edge{
    int u,v,cap,flow;
  }edge[MAX_NODE<<3];
  VR<int> G[MAX_NODE]; int tail;
  int d[MAX_NODE],cur[MAX_NODE];

  void clear(){
    s=t=tail=0; FOR(i,0,MAX_NODE) G[i].clear();
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
  int T; scanf("%d",&T);
  while(T--){
    mf.clear();
    scanf("%d%d",&m,&n);
    scanf("%d%d%d",&d,&f,&b);
    int tail=1; s=0, t=n*m+10;
    int ans=0;
    FORR(i,1,n){
      scanf("%s",t1+1);
      FORR(j,1,m){
        if(i==1 || i==n || j==1 || j==m){
          //if(t1[j]=='.') {t1[j]='#'; ans+=f; mf.addEdge(s,tail,INF);}
          //else mf.addEdge(s,tail,d);
          if(t1[j]=='.') {t1[j]='#'; ans+=f;}
          mf.addEdge(s,tail,INF);
        }else{
          if(t1[j]=='#') mf.addEdge(s,tail,d);
          else mf.addEdge(tail,t,f);
        }
        G[i][j]=(t1[j]=='.');
        num[i][j]=tail++;
      }
    }
    FORR(i,1,n) FORR(j,1,m) FOR(k,0,4){
      int tx=i+to[k][0];
      int ty=j+to[k][1];
      if(tx<1 || tx>n || ty<1 || ty>m) continue;
      mf.addEdge(num[i][j],num[tx][ty],b);
    }


    ans+=mf.maxFlow(s,t);
    printf("%d\n",ans);
  }

  return 0;
}
