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

const int MAX=50000;
const int MAX_=50020;
int n,m,k;
int mu[MAX_],prime[MAX],tail;
bool vis[MAX_];

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
LL f(LL n, LL m){
  if(n>m) swap(n,m);
  LL ans=0;
  for(LL i=1,j;i<=n;i=j+1){
    j=min(n/(n/i),m/(m/i));
    ans+=(n/i)*(m/i)*(mu[j]-mu[i-1]);
  }
  return ans;
}

int main(void){
  init();
  int T; scanf("%d",&T);
  while(T--){
    scanf("%d%d%d",&n,&m,&k);
    printf("%lld\n",f(n/k,m/k));
  }

  return 0;
}
