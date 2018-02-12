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
int a,b,c,k;

inline double P(double x, double n){
  return (2*x*(n-x+1)-1)/n/n;
}

int main(void){
  int T; scanf("%d",&T);
  FORR(kase,1,T){
    scanf("%d%d%d%d",&a,&b,&c,&k);
    double px,py,pz,ans=0;
    FORR(x,1,a){
      px=P(x,a);
      FORR(y,1,b){
        py=P(y,b);
        FORR(z,1,c){
          pz=P(z,c);
          double p = px*py*pz;
          ans += ( 1 - pow(1-2*p,k) )/2;
        }
      }
    }
    printf("Case %d: %.10lf\n",kase,ans);
  }

  return 0;
}

/*
//暴力算概率、期望
const int MAX=120;
int a,b,c,k,tot;
int cnt[MAX][MAX][MAX];

void mark(int X1, int Y1, int Z1, int X2, int Y2, int Z2){
  if(X1>X2) swap(X1,X2);
  if(Y1>Y2) swap(Y1,Y2);
  if(Z1>Z2) swap(Z1,Z2);
  FORR(i,X1,X2) FORR(j,Y1,Y2) FORR(k,Z1,Z2){
    cnt[i][j][k]++;
  }
}

int main(void){
  init(); //计算ln(C(i,j))


  scanf("%d%d%d%d",&a,&b,&c,&k);

  //计算每个点被取到的概率
  FORR(X1,1,a) FORR(Y1,1,b) FORR(Z1,1,c)
  FORR(X2,1,a) FORR(Y2,1,b) FORR(Z2,1,c){
    mark(X1,Y1,Z1,X2,Y2,Z2); tot++;
  }
#ifdef DEBUG
  printf("  tot: %d\n",tot);
  FORR(i,1,a) FORR(j,1,b) FORR(k,1,c)
    printf("  (%d,%d,%d): %d, %lf\n",i,j,k,cnt[i][j][k],1.0*cnt[i][j][k]/tot);
#endif

  //计算 sum{ E(x,y,z) }
  double ans=0;
  FORR(X1,1,a) FORR(Y1,1,b) FORR(Z1,1,c){
    double p=1.0*cnt[X1][Y1][Z1]/tot;
    for(int i=1;i<=k;i+=2)
      ans += C(k,i)*pow(p,i)*pow(1-p,k-i);
  }
  printf("%lf\n",ans);

  return 0;
}
*/
