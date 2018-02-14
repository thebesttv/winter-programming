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

const int MAX=150020;
const int SIZ=400;
int n,m,siz,a[MAX];
int b[SIZ][SIZ];

int main(void){
  scanf("%d%d",&n,&m); siz=sqrt(n);
  FORR(i,1,n) scanf("%d",&a[i]), b[1][0]+=a[i];
  FORR(p,2,siz) FORR(i,1,n)
    b[p][i%p]+=a[i];
  int ch,x,y;
  while(m--){
    do ch=getchar(); while(ch!='A' && ch!='C');
    scanf("%d%d",&x,&y);
    if(ch=='A'){
      if(x<=siz) printf("%d\n",b[x][y]);
      else{ //O(sqrt(n))
        int sum=0;
        for(int i=y;i<=n;i+=x) sum+=a[i];
        printf("%d\n",sum);
      }
    }else{
      FORR(p,1,siz) b[p][x%p] += y-a[x];  //O(sqrt(n))
      a[x]=y;
    }
  }

  return 0;
}

/*
const int MAX=150020;
int n,m,a[MAX];
int b[20][20];

int main(void){
  scanf("%d%d",&n,&m);
  FORR(i,1,n) scanf("%d",&a[i]),b[1][0]+=a[i];
  FORR(i,2,10) FORR(j,1,n)
    b[i][j%i]+=a[j];
  int ch,x,y;
  while(m--){
    do ch=getchar(); while(ch!='A' && ch!='C');
    scanf("%d%d",&x,&y);
    if(ch=='A'){
      if(x<=10) {printf("%d\n",b[x][y]); continue;}
      int sum=0;
      for(int i=y;i<=n;i+=x) sum+=a[i];
      printf("%d\n",sum);
    }else{
      FORR(i,1,10) b[i][x%i] += y-a[x];
      a[x]=y;
    }
  }
  return 0;
}
*/
