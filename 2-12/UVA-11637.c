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

const int MAX=100020;
int n,k;
long double lf[MAX];  // lf[i] = log(i!)

//期望的线性性质 E(a+b) = E(a) + E(b)
// E( sum{队列中的第i个单词是无效的期望} ) = sum{ E(i) }

int main(void){
  FOR(i,2,MAX) lf[i] = lf[i-1] + log(i);
  int kase=0;
  while(~scanf("%d%d",&n,&k) && n){
    double ans=0;
    if(n==1) ans=0; //<b> </b>
    else{
      FORR(i,1,n){
        int x = max(i-1-k,0) + max(n-i-k,0);
        if(x < 2*k) continue;
        double t = lf[x] - lf[x-2*k] + lf[n-1-2*k] - lf[n-1];
        ans += exp(t);  // exp(t) = e^t
      }
      ans = n-ans;
    }
    printf("Case %d: %.4lf\n",++kase,ans);
  }

  return 0;
}
