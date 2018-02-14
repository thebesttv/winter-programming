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

const int MAX=1000000,MAX_=1000020;
const int MOD=1e9+7;
int REV2,REV6;
int n,mu[MAX_],prime[MAX],tail;
bool vis[MAX_]; LL f[MAX_];
map<int,LL> mp;

LL sh(LL n){
  n%=MOD;
  LL t1 = n*(n+1)%MOD*(2*n%MOD+1)%MOD;
  t1 = t1*REV6%MOD;
  LL t2 = (n*n%MOD+n)%MOD*3%MOD*REV2%MOD;
  return (t1-t2+MOD+n*2)%MOD;
}
void init(){
  mu[1]=1;
  FORR(i,2,MAX){
    if(!vis[i]) prime[tail++]=i, mu[i]=-1;
    FOR(j,0,tail){
      int t=i*prime[j];
      if(t>MAX) break;
      vis[t]=1;
      if(i%prime[j]==0){
        mu[t]=0; break;
      }else{
        mu[t]=-mu[i];
      }
    }
  }
  FORR(i,1,MAX){
    LL th = (1LL*i*i%MOD - 3LL*i%MOD + 2 + MOD)%MOD;
    //LL th=(sh(i)-sh(i-1)+MOD)%MOD;
    for(int j=i,cnt=1;j<=MAX;j+=i,cnt++)
      f[j] = ( f[j] + mu[cnt]*th%MOD )%MOD;
  }
  FORR(i,2,MAX) f[i]=(f[i]+f[i-1])%MOD;
}
void ex_gcd(LL a, LL b, LL &d, LL &x, LL &y){
  if(!b) { d=a; x=1; y=0; }
  else { ex_gcd(b,a%b,d,y,x); y-=x*(a/b); }
}
LL get(LL a){
  LL d,x,y; ex_gcd(a,MOD,d,x,y);
  return (x+MOD)%MOD;
}
LL S(int n){
  if(n<=MAX) return f[n];
  if(mp.count(n)) return mp[n];
  LL a=sh(n);
  for(int i=2,j;i<=n;i=j+1){
    j=n/(n/i);
    a = ( a - S(n/i)*(j-i+1)%MOD + MOD )%MOD;
  }
  return mp[n]=a;
}

int main(void){
  REV2=get(2); REV6=get(6); init();
  int T; scanf("%d",&T);
  while(T--){
    scanf("%d",&n);
    printf("%lld\n",S(n));
  }

  return 0;
}
