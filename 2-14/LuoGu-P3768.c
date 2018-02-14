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

const int MAX=5000000;
const int MAX_=MAX+20;
LL n,MOD,REV;
int prime[MAX],mu[MAX_],phi[MAX_],tail;
LL f[MAX];
bool vis[MAX_];
map<LL,LL> mp;

inline void ex_gcd(LL a, LL b, LL &d, LL &x, LL &y){
  if(!b) { d=a; x=1; y=0; }
  else { ex_gcd(b,a%b,d,y,x); y-=x*(a/b); }
}
inline LL get(LL n){
  LL d,x,y; ex_gcd(n,MOD,d,x,y);
  return (x+MOD)%MOD;
}
inline LL g(LL n){
  n%=MOD;
  return (n*n+n)/2%MOD;
}
inline LL h(LL n){
  n%=MOD;
  return n*(n+1)%MOD*(2*n%MOD+1)%MOD *REV %MOD;
}

void init(){
  mu[1]=1; phi[1]=1;
  FORR(i,2,MAX){
    if(!vis[i]){
      prime[tail++]=i;
      mu[i]=-1; phi[i]=i-1;
    }
    FOR(j,0,tail){
      int t=i*prime[j];
      if(t>MAX) break;
      vis[t]=1;
      if(i%prime[j]==0){
        mu[t]=0;
        phi[t]=phi[i]*prime[j];
        break;
      }else{
        mu[t]=-mu[i];
        phi[t]=phi[i]*(prime[j]-1);
      }
    }
  }
  FORR(i,1,MAX) f[i] = ( 1LL*i*i%MOD*phi[i]%MOD + f[i-1] ) %MOD;
}

LL S(LL n){
  if(n<=MAX) return f[n];
  if(mp.count(n)) return mp[n];
  LL a=g(n); a=a*a%MOD;
  for(LL i=2,j;i<=n;i=j+1){
    j=n/(n/i);
    a = ( a - S(n/i)*( (h(j)-h(i-1)+MOD)%MOD )%MOD + MOD ) %MOD;
  }
  return mp[n]=a;
}

int main(void){
  scanf("%lld%lld",&MOD,&n);
  init(); REV=get(6);
  LL ans=0;
  for(LL i=1,j;i<=n;i=j+1){
    j=n/(n/i);
    LL t=g(n/i); t=t*t%MOD;
    ans = ( ans + t*(S(j)-S(i-1)+MOD)%MOD )%MOD;
  }

  printf("%lld\n",ans);

  return 0;
}

/*
const int MAX=1000020;
const int MAX_=MAX+20;
int n; LL MOD;
int prime[MAX],mu[MAX_],tail;
LL h[MAX_];
bool vis[MAX_];

LL g(LL n){
  return (n*n+n)/2%MOD;
}

void init(){
  mu[1]=1;
  FORR(i,2,MAX){
    if(!vis[i]){
      prime[tail++]=i;
      mu[i]=-1;
      //h[i]=(i-1)%MOD;
    }
    FOR(j,0,tail){
      int t=i*prime[j];
      if(t>MAX) break;
      vis[t]=1;
      if(i%prime[j]==0){
        mu[t]=0;
        //h[t]=1LL*prime[j]*mu[i]%MOD;
        break;
      }else{
        mu[t]=-mu[i];
        //h[t]=1LL*(prime[j]-1)*h[i]%MOD;
      }
    }
  }

  FORR(i,1,n){
    for(int j=i,cnt=1;j<=n;j+=i,cnt++){
      h[j] = ( h[j] + i*mu[cnt]%MOD ) %MOD;
    }
  }
  FORR(i,1,MAX) h[i] = ( 1LL*i*i%MOD*h[i]%MOD + h[i-1] )%MOD;
}

int main(void){
  scanf("%lld%d",&MOD,&n);
  init();
  LL ans=0;
  for(int i=1,j;i<=n;i=j+1){
    j=n/(n/i);
    LL t=g(n/i); t=t*t%MOD;
    ans = ( ans + t*(h[j]-h[i-1]+MOD)%MOD )%MOD;
  }

  printf("%lld\n",ans);

  return 0;
}
*/

/*
const int MAX=1000020;
const int MAX_=MAX+20;
int n; LL MOD;
int prime[MAX],mu[MAX_],h[MAX_],tail;
bool vis[MAX_];

LL g(LL n){
  return (n*n+n)/2%MOD;
}

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
        mu[t]=0;
        break;
      }else{
        mu[t]=-mu[i];
      }
    }
  }

  FORR(i,1,n){
    for(int j=i,cnt=1;j<=n;j+=i,cnt++){
      h[j] += i*mu[cnt];
    }
  }
  FORR(i,1,MAX) h[i] = h[i]*i%MOD*i%MOD;
}

int main(void){
  scanf("%lld%d",&MOD,&n);
  init();
#ifdef DEBUG
  FORR(i,1,10) printf("  h[%d]: %d\n",i,h[i]);
#endif

  LL ans=0;
  FORR(d,1,n){
    LL tans = d*d%MOD*g(n/d)%MOD*g(n/d)%MOD;
    LL sum=0;
    FORR(i,1,d) if(d%i==0){
      sum = ( sum + i*mu[d/i]%MOD ) %MOD;
    }
    ans = (ans + tans*sum%MOD)%MOD;
  }
  printf("%lld\n",ans);

  ans=0;
  FORR(d,1,n){
    ans = ( ans + g(n/d)*g(n/d)%MOD*h[d]%MOD )%MOD;
  }
  printf("%lld\n",ans);

  return 0;
}
*/
