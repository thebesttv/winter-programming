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

const int MAXK=120;
const int MAXN=20;
int n,k,a[MAXN],req[MAXN];
double check_f[MAXK][1<<16];
bool vis[MAXK][1<<16];

double f(int cur, int S){ //当前在第 cur 次投掷已经决策完，决策前吃过的物品集合为 S
#ifdef DEBUG
  FOR(i,0,cur) printf("  ");
  printf("in f(%d,%d)\n",cur,S);
#endif
  if(cur==k) return 0;
  if(vis[cur][S]) return check_f[cur][S];
  double &ans=check_f[cur][S]; vis[cur][S]=1;
  //FORR(i,1,n) if((S & req[i])==req[i]){
  //  if(a[i]>=0) ans += f(cur+1,S|(1<<i))+a[i];
  //  else if((S&(1<<i))==0){ //分数为负且未吃过
  //    ans += max( f(cur+1,S|(1<<i))+a[i], f(cur+1,S));
  //  }
  //}
  FORR(i,1,n){
    if((S & req[i])==req[i]){
      if(a[i]>=0) ans += f(cur+1,S|(1<<i))+a[i];
      else{
        if((S&(1<<i))==0){ //分数为负且未吃过
          ans += max( f(cur+1,S|(1<<i))+a[i], f(cur+1,S));
        }else ans+=f(cur+1,S);  //<b> </b>
      }
    }else ans+=f(cur+1,S);  //<b> </b>
  }
  ans/=n;
#ifdef DEBUG
  FOR(i,0,cur) printf("  ");
  printf("f(%d,%d): %lf\n",cur,S,ans);
#endif
  return ans;
}

int main(void){
  scanf("%d%d",&k,&n);
  int t;
  FORR(i,1,n){
    scanf("%d%d",&a[i],&t);
    while(t){
      req[i]|=1<<t;
      scanf("%d",&t);
    }
  }

  printf("%.6lf\n",f(0,0));

  return 0;
}
