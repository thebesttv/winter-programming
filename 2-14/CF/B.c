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

int main(void){
  int n; scanf("%d",&n);
  if(n>18*2) {printf("-1\n"); return 0;}

  while(n>=2) putchar('8'), n-=2;
  if(n) putchar('6');
  putchar('\n');
}

/*
int n; char rec[40];

bool dfs(int cur, int sum){
  if(sum==n) return true;
  if(cur>=18) return false;
  if(sum+2*(18-cur)<n) return false;

  if(sum+2<=n){
    rec[cur]='8';
    if(dfs(cur+1,sum+2)) return true;
  }
  rec[cur]='4';
  if(dfs(cur+1,sum+1)) return true;
  rec[cur]=0; return false;
}

int main(void){
  scanf("%d",&n);
  if(!n) {printf("1\n"); return 0;}
  if(n>36) {printf("-1\n"); return 0;}

  dfs(0,0);
  printf("%s\n",rec);

  return 0;
}
*/

/*
const int a[10]={1,0,0,0,1,0,1,0,2,1};
int n,rec[20],tail;
int ava[]={0,4,6,8,9},tot=5;

bool dfs(int cur, int sum){
  if(sum==n) {tail=cur; return true;}
  if(cur>=18) return false;
  if((18-cur)*2+sum<n) return false;
  if(cur && sum+a[0]<=n){
    rec[cur]=0;
    if(dfs(cur+1,sum+a[0])) return true;
  }
  FOR(i,1,tot) if(sum+a[ava[i]]<=n){
    rec[cur]=ava[i];
    if(dfs(cur+1,sum+a[ava[i]])) return true;
  }
  return false;
}

int main(void){
  scanf("%d",&n);
  if(n > 18*2) {printf("%d\n",-1); return 0;}
  if(!dfs(0,0)) printf("%d\n",-1);
  else{
    FOR(i,0,tail) printf("%d",rec[i]);
    printf("\n");
  }

  return 0;
}
*/
