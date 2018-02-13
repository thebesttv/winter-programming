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

const LL MOD=998244353;
const int MAX=1000020;
LL n,m,p,d,a,b,c;
LL f[MAX];

int main(void){
  scanf("%lld%lld",&n,&m);
  scanf("%lld%lld",&p,&d);
  scanf("%lld%lld%lld",&a,&b,&c);
  
  f[0]=1;
  FOR(i,0,n){
    f[i+1] = ( f[i+1] + (1+MOD-p)*f[i]%MOD )%MOD;
    if(i+m+1<=n) f[i+m+1] = ( f[i+m+1] + p*f[i]%MOD )%MOD;
  }

  LL ans=0;
  FORR(i,1,n) ans = ( ans + f[i]*a%MOD + ( (1+MOD-f[i]) *  ( (1+MOD-d)*b%MOD + d*c%MOD )%MOD )%MOD )%MOD;
  printf("%lld\n",ans);

  return 0;
}
