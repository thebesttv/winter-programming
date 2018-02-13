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

const int MAXT=1020;
const int MAXP=20020;
int n,t,d,a[MAXT];
bool vis[MAXP+10];
int prime[MAXP],tail;

const int BASE=100000000;
const int WIDTH=8;
struct BI{
  vector<int> v;
  int len;

  BI() {len=0;}
  BI(int n){
    while(n>BASE) v.push_back(n%BASE), n/=BASE;
    if(n) v.push_back(n);
    len=v.size();
  }
  void print(){
    printf("%d",v[len-1]);
    for(int i=len-2;i>=0;i--) printf("%08d",v[i]);
  }
};

int compare(BI & a, BI & b){
  if(a.len!=b.len) return a.len-b.len;
  else{
    for(int i=a.len-1;i>=0;i--) if(a.v[i]!=b.v[i])
      return a.v[i]-b.v[i];
  }
  return 0;
}
BI add(BI a, BI b){
  if(compare(a,b)<0) swap(a,b);
  int carry=0;
  for(int i=0;i<a.len;i++){
    a.v[i]+=carry;
    if(i<b.len) a.v[i]+=b.v[i];
    carry=a.v[i]/BASE;
    a.v[i]%=BASE;
  }
  if(carry) a.v.push_back(carry);
  a.len=a.v.size();
  return a;
}
BI mul(BI a, int b){
  long long carry=0;
  BI c;
  for(int i=0;i<a.len;i++){
    carry+=(long long)a.v[i]*b;
    c.v.push_back(carry%BASE);
    carry/=BASE;
  }
  if(carry) c.v.push_back(carry);
  c.len=c.v.size();
  return c;
}
BI mul(BI a, BI b){
  if(compare(a,b)<0) swap(a,b);
  BI c,temp; c=mul(a,b.v[0]);
  for(int i=1;i<b.len;i++){
    temp=mul(a,b.v[i]);
    for(int j=0;j<i;j++) temp.v.push_back(0);
    for(int j=temp.len-1;j>=0;j--) temp.v[j+i]=temp.v[j];
    for(int j=0;j<i;j++) temp.v[j]=0;
    temp.len+=i;
    c=add(c,temp);
  }
  return c;
}
BI pow(const BI &n, int a){  //n^a
  if(!a) return BI(1);
  if(a==1) return n;
  BI ans = pow(n,a>>1);
  ans = mul(ans,ans);
  if(a&1) ans = mul(ans,n);
  return ans;
}

struct FRAC{
  int ex1[MAXP],ex2[MAXP];
  void add(int a,int b){  //添加 a/b
    if(a!=1) add1(a);
    if(b!=1) add2(b);
  }
  void add1(int n){
    int sq=sqrt(n+0.5);
    for(int i=0;i<tail && n!=1 && prime[i]<=sq;i++){
      while(n%prime[i]==0) n/=prime[i], ex1[i]++;
    }
    if(n!=1){
      int t=lower_bound(prime,prime+tail,n)-prime;
      ex1[t]++;
    }
  }
  void add2(int n){
    int sq=sqrt(n+0.5);
    for(int i=0;i<tail && n!=1 && prime[i]<=sq;i++){
      while(n%prime[i]==0) n/=prime[i], ex2[i]++;
    }
    if(n!=1){
      int t=lower_bound(prime,prime+tail,n)-prime;
      ex2[t]++;
    }
  }
  void sim(){ //约分
    int t;
    FOR(i,0,tail){
      t=min(ex1[i],ex2[i]);
      ex1[i]-=t, ex2[i]-=t;
    }
  }
  void print(){
    BI a(1),b(1);
    FOR(i,0,tail){
      if(ex1[i]) a = mul(a, pow(BI(prime[i]),ex1[i]));
      if(ex2[i]) b = mul(b, pow(BI(prime[i]),ex2[i]));
    }
#ifdef DEBUG
    FOR(i,0,tail) if(ex1[i]) printf(" %d^%d *",prime[i],ex1[i]); printf("\n");
    FOR(i,0,tail) if(ex2[i]) printf(" %d^%d *",prime[i],ex2[i]); printf("\n");
#endif
    a.print(); printf("/"); b.print(); printf("\n");
  }
}f;

int main(void){
  FORR(i,2,MAXP){
    if(!vis[i]){
      prime[tail++]=i;
    }
    FOR(j,0,tail){
      int t=i*prime[j];
      if(t>MAXP) break;
      vis[t]=1;
      if(i%prime[j]==0) break;
    }
  }

  scanf("%d%d%d",&t,&n,&d);
  int sum=0,x,y;
  FORR(i,1,t) scanf("%d",&a[i]), sum+=a[i];
  while(n--){
    scanf("%d%d",&x,&y);
    f.add(a[y],sum);
    a[y]+=d, sum+=d;
  }
  f.sim(); f.print();

  return 0;
}

/*
const int MAX=1020;
int t,n,d,a[MAX];
const int MOD=1000007;
LLU n1=1,n2=1;

int main(void){
  scanf("%d%d%d",&t,&n,&d);
  int sum=0,x,y;
  FORR(i,1,t) scanf("%d",&a[i]), sum+=a[i];
  double ans=1;
  while(n--){
    scanf("%d%d",&x,&y);
    n1 = n1*a[y]%MOD;
    n2 = n2*sum%MOD;
    a[y]+=d, sum+=d;
  }
  printf("%llu , %llu\n",n1,n2);

  return 0;
}
*/
