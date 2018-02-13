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

const int MAX=1020;
const int INF=0x3f3f3f3f;
int n,m,s,t,d[MAX][MAX];
int to[MAX][MAX]; // to[i][j]: 从 i 到 j ，走一步能走到的最近点（序号最小）
VR<int> G[MAX];
double check_f[MAX][MAX];
bool vis[MAX][MAX];

double f(int s, int t){
  if(s==t) return 0.0;
  if(vis[s][t]) return check_f[s][t];
  double &a=check_f[s][t]; vis[s][t]=1;
  if(d[s][t]<=2) a=1.0;
  else{
    int v=to[to[s][t]][t]; a=f(v,t);
    FOR(i,0,G[t].size()) a+=f(v,G[t][i]);
    a = a/(1+G[t].size()) + 1.0;
  }
  return a;
}

int main(void){
  MST(d,0x3f);
  scanf("%d%d%d%d",&n,&m,&s,&t);
  FORR(i,1,n) d[i][i]=0;
  int u,v;
  while(m--){
    scanf("%d%d",&u,&v);
    d[u][v]=d[v][u]=1;
    G[u].push_back(v); G[v].push_back(u);
  }
  // Floyd
  ROR(k,n,1) FORR(i,1,n) if(d[i][k]<INF) FORR(j,1,n)
    d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
  // init to
  FORR(i,1,n) FORR(j,1,n){
    if(d[i][j]<=1) to[i][j]=j;
    else FORR(k,1,n) if(d[i][k]==1 && d[i][j]==d[i][k]+d[k][j]){
      to[i][j]=k; break;
    }
  }

  printf("%.3lf\n",f(s,t));

  return 0;
}

/*
const int MAX=1020;
const int INF=0x3f3f3f3f;
int n,m,s,t,d[MAX][MAX];
int to[MAX][MAX];
VR<int> G[MAX];
double check_f[MAX][MAX];
bool vis[MAX][MAX];

double f(int s, int t){
  if(s==t) return 0.0;
  if(vis[s][t]) return check_f[s][t];
  double &a=check_f[s][t]; vis[s][t]=1;
  if(d[s][t]<=2) a=1.0;
  else{
    int v=to[s][t]; a=f(v,t);
    FOR(i,0,G[t].size()) a+=f(v,G[t][i]);
    a = a/(1+G[t].size()) + 1.0;
  }
  return a;
}

int main(void){
  MST(d,0x3f);
  scanf("%d%d%d%d",&n,&m,&s,&t);
  FORR(i,1,n) d[i][i]=0;
  int u,v;
  while(m--){
    scanf("%d%d",&u,&v);
    d[u][v]=d[v][u]=1;
    G[u].push_back(v); G[v].push_back(u);
  }
  // Floyd
  FORR(k,1,n) FORR(i,1,n) if(d[i][k]<INF) FORR(j,1,n)
    d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
  // init to
  //FORR(i,1,n) FORR(j,1,n){
  //  if(d[i][j]<=2) to[i][j]=j;
  //  else FORR(k,1,n) if(d[i][k]==2 && d[i][j]==d[i][k]+d[k][j]){
  //    to[i][j]=k; break;
  //  }
  //}
  FORR(i,1,n) FORR(j,1,n){
    if(d[i][j]<=1) to[i][j]=j;
    else{
      FORR(k,1,n) if(d[i][k]==1 && d[i][j]==d[i][k]+d[k][j]){ //走第一步
        to[i][j]=k; break;
      }
      int t=to[i][j];
      FORR(k,1,n) if(d[t][k]==1 && d[t][j]==d[t][k]+d[k][j]){ //走第二步
        to[i][j]=k; break;
      }
    }
  }
#ifdef DEBUG
  FORR(i,1,n) FORR(j,1,n) printf("  f(%d,%d): %lf\n",i,j,f(i,j));
#endif

  printf("%.3lf\n",f(s,t));

  return 0;
}
*/
