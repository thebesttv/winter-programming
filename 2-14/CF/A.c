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

const int MAX=100;
int n,m; LL a[MAX],b[MAX];

int main(void){
  scanf("%d%d",&n,&m);
  FORR(i,1,n) cin >> a[i];
  FORR(i,1,m) cin >> b[i];

  LL ansMin=1LL<<62;
  FORR(k,1,n){  //选a[k]
    LL tMax=-(1LL<<62);
    FORR(i,1,n) if(i!=k) FORR(j,1,m)  //在剩下的中选出最大的
      tMax=max(tMax,a[i]*b[j]);
    ansMin=min(ansMin,tMax);
  }
  cout << ansMin << endl;

  return 0;
}

/*
const int MAX=100;
int n,m; LL a[MAX],b[MAX];

int main(void){
  scanf("%d%d",&n,&m);
  FORR(i,1,n) cin >> a[i];
  FORR(i,1,m) cin >> b[i];
  sort(a+1,a+1+n); sort(b+1,b+1+m);
  
  LL ans;
  LL t1 = a[1]*b[1], t2 = a[n]*b[m];
  if(t1>t2){  //拿掉 a[1]
    ans = max( a[2]*b[1], a[2]*b[m] );
    ans = max( ans, max( a[n]*b[1], a[n]*b[m] ) );
  }else if(t1<t2){  //拿掉 a[n]
    ans = max( a[1]*b[1], a[1]*b[m] );
    ans = max( ans, max( a[n-1]*b[1], a[n-1]*b[m] ) );
  }else{
    ans = max( a[2]*b[1], a[2]*b[m] );
    ans = max( ans, max( a[n]*b[1], a[n]*b[m] ) );
    ans = max( ans, max( a[1]*b[1], a[1]*b[m] ) );
    ans = max( ans, max( a[n-1]*b[1], a[n-1]*b[m] ) );
  }

  cout << ans << endl;

  return 0;
}
*/
