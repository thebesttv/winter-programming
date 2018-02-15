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

const int MAX=1000000;
const int MAX_=MAX+20;
const LL MOD=1000000007;
int n,k,l,r;
int mu[MAX_],prime[MAX],tail;
bool vis[MAX_];
map<int,LL> mp;

void init(){
  mu[1]=1;
  FORR(i,2,MAX){
    if(!vis[i]){
      prime[tail++]=i;
      mu[i]=-1;
    }
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
  FORR(i,2,MAX) mu[i]+=mu[i-1];
}
LL S(LL n){
  if(n<=MAX) return mu[n];
  if(mp.count(n)) return mp[n];
  LL a=1;
  for(LL i=2,j;i<=n;i=j+1){
    j=n/(n/i);
    a = ( a - S(n/i)*(j-i+1)%MOD + MOD )%MOD;
  }
  return mp[n]=a;
}
LL pow_mod(LL n, LL a){
  if(!a) return 1;
  if(a==1) return n%MOD;
  LL ans=pow_mod(n,a>>1);
  ans=ans*ans%MOD;
  if(a&1) ans=ans*n%MOD;
  return ans;
}
LL f(LL n, LL l, LL r){ // f(n,1,l,r)
  LL ans=0; l-=1;
  //FORR(i,1,r) ans = ( ans + mu[i]*pow_mod( r/i - (l-1)/i ,n)%MOD ) %MOD;
  for(LL i=1,j;i<=r;i=j+1){
    j=r/(r/i);
    if(l/i) j=min(j,l/(l/i));
    //ans = ( ans + (mu[j]-mu[i-1]+MOD)%MOD*pow_mod( r/i - l/i , n )%MOD ) %MOD;
    ans = ( ans + (S(j)-S(i-1)+MOD)%MOD * pow_mod(r/i-l/i,n) %MOD ) %MOD;
  }

  return ans;
}

int main(void){
  init(); scanf("%d%d%d%d",&n,&k,&l,&r);
  printf("%lld\n",f(n,ceil(1.0*l/k),r/k));

  return 0;
}
