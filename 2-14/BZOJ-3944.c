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

const int MAX=2000000, MAX_=2000020;
int n;
int mu[MAX_],phi[MAX_],prime[MAX],tail;
bool vis[MAX_];
LL cf1[MAX_]; int cf2[MAX_];
map<int,LL> mp1;
map<int,int> mp2;

void init(){
  mu[1]=1; phi[1]=1;
  FORR(i,2,MAX){
    if(!vis[i]){
      prime[tail++]=i;
      mu[i]=-1;
      phi[i]=i-1;
    }
    FOR(j,0,tail){
      int t=i*prime[j];
      if(t>MAX) break;
      vis[t]=1;
      if(i%prime[j]==0){
        mu[t]=0;
        phi[t]=prime[j]*phi[i];
        break;
      }else{
        mu[t]=-mu[i];
        phi[t]=(prime[j]-1)*phi[i];
      }
    }
  }
  FORR(i,1,MAX) cf1[i]=phi[i]+cf1[i-1], cf2[i]=mu[i]+cf2[i-1];
}
void f(int n, LL &a1, int &a2){
  if(n<=MAX) {a1=cf1[n]; a2=cf2[n]; return;}
  if(mp1.count(n)) {a1=mp1[n]; a2=mp2[n]; return;}
  a1 = (1LL*n*n+n)/2; a2=1;
  LL t1; int t2;
  for(LL i=2,j;i<=n;i=j+1){
    j=n/(n/i); f(n/i,t1,t2);
    a1 -= t1*(j-i+1);
    a2 -= t2*(j-i+1);
  }
  mp1[n]=a1; mp2[n]=a2;
}

int main(void){
  init();
  int T; scanf("%d",&T);
  while(T--){
    scanf("%d",&n);
    LL a1; int a2; f(n,a1,a2);
    printf("%lld %d\n",a1,a2);
  }

  return 0;
}



/*
const int MAX=2000000, MAX_=2000020;
int n,lim;
int mu[MAX_],phi[MAX_],prime[MAX],tail;
bool vis[MAX_];
LL cf1[MAX_]; int cf2[MAX_];
map<int,LL> mp1;
map<int,int> mp2;

void init(){
  mu[1]=1; phi[1]=1;
  FORR(i,2,MAX){
    if(!vis[i]){
      prime[tail++]=i;
      mu[i]=-1;
      phi[i]=i-1;
    }
    FOR(j,0,tail){
      int t=i*prime[j];
      if(t>MAX) break;
      vis[t]=1;
      if(i%prime[j]==0){
        mu[t]=0;
        phi[t]=prime[j]*phi[i];
        break;
      }else{
        mu[t]=-mu[i];
        phi[t]=(prime[j]-1)*phi[i];
      }
    }
  }
  FORR(i,1,MAX) cf1[i]=phi[i]+cf1[i-1], cf2[i]=mu[i]+cf2[i-1];
}
LL f1(int n){
  if(n<=lim) return cf1[n];
  if(mp1.count(n)) return mp1[n];
  LL a = (1LL*n*n+n)/2;
  //FORR(i,2,n) a-=f1(n/i);
  for(LL i=2,j;i<=n;i=j+1){
    j=n/(n/i);
    a -= f1(n/i)*(j-i+1);
  }
  return mp1[n]=a;
}
int f2(int n){
  if(n<=lim) return cf2[n];
  if(mp2.count(n)) return mp2[n];
  int a=1;
  //FORR(i,2,n) a-=f2(n/i);
  for(LL i=2,j;i<=n;i=j+1){
    j=n/(n/i);
    a -= f2(n/i)*(j-i+1);
  }
  return mp2[n]=a;
}

int main(void){
  init();
  int T; scanf("%d",&T);
  while(T--){
    scanf("%d",&n); lim=pow(n,2.0/3);
    printf("%lld %d\n",f1(n),f2(n));
  }

  return 0;
}
*/
