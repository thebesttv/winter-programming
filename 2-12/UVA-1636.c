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

const int MAX=120;
int n,n0,k; //n: 总数，n0: 0的个数，k: 00的个数
char t1[MAX];

int main(void){
  while(~scanf("%s",t1)){
    n=strlen(t1); n0=k=0;
    FOR(i,0,n){
      if(t1[i]=='0'){
        n0++;
        if(i+1<n && t1[i+1]=='0') k++;
      }
    }
    if(t1[n-1]=='0' && t1[0]=='0') k++;
    double shoot = 1.0*k/n0;
    double rotate = 1.0*n0/n;
    printf("%s\n", shoot == rotate ? "EQUAL" : (shoot > rotate ? "SHOOT" : "ROTATE") );
  }

  return 0;
}
