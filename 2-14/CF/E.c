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

const double EPS=1e-6;
int n; bool vis[1<<4];
struct Cir{
  double x,y,r,r2;
  bool isEdge(double X, double Y){
    double d = (x-X)*(x-X) + (y-Y)*(y-Y);
    return fabs(d-r2)<EPS;
  }
  bool isInside(double X, double Y){
    double d = (x-X)*(x-X) + (y-Y)*(y-Y);
    return d < r2;
  }
}c[10];
double dis(double X1, double Y1, double X2, double Y2){
  return (X1-X2)*(X1-X2) + (Y1-Y2)*(Y1-Y2);
}

int main(void){
  scanf("%d",&n);
  FOR(i,0,n) scanf("%lf%lf%lf",&c[i].x,&c[i].y,&c[i].r), c[i].r2=c[i].r*c[i].r;
  if(n==1) {printf("%d\n",2); return 0;}

  double delta=0.05;
  for(double x=-20.0;x<=20.0;x+=delta)
  for(double y=-20.0;y<=20.0;y+=delta){
    bool ok=1;
    FOR(i,0,n) if(c[i].isEdge(x,y)) {ok=0; break;}
    if(!ok) continue;
    int S=0;
    FOR(i,0,n) if(c[i].isInside(x,y)) S|=1<<i;
    vis[S]=1;
  }
  int cnt=0;
  FOR(i,0,8) if(vis[i]) cnt++;

  bool ok=1;
  FOR(i,0,n){
    if(dis(c[i].x,c[i].y,c[(i+1)%n].x,c[(i+1)%n].y) <= c[i].r+c[(i+1)%n].r ) ok=0;
  }
  if(ok) cnt++;

  printf("%d\n",cnt);

  return 0;
}
