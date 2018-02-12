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

const int MAX=50;
int n; double t,d[MAX];

int main(void){
  while(~scanf("%d%lf",&n,&t) && n){
    d[n] = 1<<n;

    ROR(i,n-1,0){
      double p0 = max(t, (1<<i)/d[i+1]);
      double p1 = (p0-t)/(1-t);
      d[i] = p1*(1<<i) + (1-p1)*(1+p0)/2*d[i+1];
    }

    printf("%.3lf\n",d[0]);
  }

  return 0;
}
