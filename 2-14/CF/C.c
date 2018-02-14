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

const int MAX=2020;
int n,cnt1[MAX],cnt2[MAX];

int main(void){
  scanf("%d",&n);
  FORR(i,1,n){
    scanf("%d",&a[i]);
    cnt1[i]=(a[i]==1)+cnt1[i-1];
    cnt2[i]=(a[i]==2)+cnt2[i-1];
  }
  int ansMax=max(cnt1[n],cnt2[n]);
  FORR(l,1,n) FORR(r,l+1,n){
    ansMax = max(  );
  }

  return 0;
}
