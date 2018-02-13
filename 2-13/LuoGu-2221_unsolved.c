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

const int MAX=100020;
int n,m;

LL a(LL n){
  return n*(n+1)*(2*n+1)/6;
}
LL b(LL n){
  return n*(n+1)/2;
}
LL f(LL l, LL r){
  return 2*( a(l-1)-a(r-1) + (r+l-1)*( b(r-1)-b(l-1) ) + (r-l*r)*(r-l) );
}
LLU gcd(LLU a, LLU b){
  return !b ? a : gcd(b,a%b);
}
struct ST{
  struct Node{
    LLU sum; int l,r,addVal;
    Node *lc, *rc;
    Node(LLU sum_, int l_, int r_, Node *lc_, Node *rc_):
      sum(sum_), l(l_), r(r_), lc(lc_), rc(rc_) { }

    void pushDown(){
      if(addVal){
        sum += f(l,r+1)*addVal;
        if(lc) lc->addVal+=addVal;
        if(rc) rc->addVal+=addVal;
        addVal=0;
      }
    }
  }*root;

  void build(int n){
    root = build(1,n);
  }
  Node *build(int l, int r){
    Node *p = new Node(0,l,r,NULL,NULL);
    if(l==r) return p;
    int m=(l+r)>>1;
    p->lc = build(l,m), p->rc = build(m+1,r);
    return p;
  }
  /*
  void add(Node *u, int al, int ar, int av){
    if(al<=u->l && ar>=u->r){
      u->addVal+=av; return;
    }
    u->pushDown();
    int m=(u->l + u->r)>>1;
    if(al<=m) add(u->lc,al,ar,av);
    if(m>ar)  add(u->rc,al,ar,av);
  }
  */
  void add(Node *u, int al, int ar, int v){
    if(al > u->r || ar < u->l ) return;
    else if(al <= u->l && ar >= u->r) u->addVal+=v;
    else{
      u->pushDown();  //TODO 对该区间更新
      if(u->lc) add(u->lc,al,ar,v);
      if(u->rc) add(u->rc,al,ar,v);
    }
  }
  /*
  LLU sum(Node *u, int ql, int qr){
    u->pushDown();
    if(ql<=u->l && qr>=u->r) return u->sum;
    int m=(u->l+u->r)>>1;
    LLU ans=0;
    if(ql<=m) ans+=sum(u->lc,ql,qr);
    if(m>qr)  ans+=sum(u->rc,ql,qr);
    return ans;
  }
  */
  LLU sum(Node *u, int ql, int qr){
    u->pushDown();
    if(ql > u->r || qr < u->l) return 0;
    else if(ql <= u->l && qr >= u->r) return u->sum;
    else{
      LLU ans=0;
      if(u->lc) u->lc->pushDown(), ans+=sum(u->lc,ql,qr);
      if(u->rc) u->rc->pushDown(), ans+=sum(u->rc,ql,qr);
      return ans;
    }
  }
}sg;

int main(void){
  scanf("%d%d",&n,&m);
  sg.build(n-1);
  int l,r,v,ch;
  while(m--){
    do ch=getchar(); while(ch!='C' && ch!='Q');
    if(ch=='C'){
      scanf("%d%d%d",&l,&r,&v);
      sg.add(sg.root,l,r-1,v);
    }else{
      scanf("%d%d",&l,&r);
      LLU t=sg.sum(sg.root,l,r-1), tn = (r-l)*(r-l+1);
      LLU tg = gcd(t,tn);
      printf("%lld/%lld\n",t/tg,tn/tg);
    }
  }

  return 0;
}






















/*
const int MAX=100020;
int cnt[MAX];

int f(int x, int l, int r){
  return 2*(x-l+1)*(r-x);
}

LLU a(LLU n){
  return n*(n+1)*(2*n+1)/6;
}
LLU b(LLU n){
  return n*(n+1)/2;
}
LLU test(LLU l, LLU r){
  return 2*( a(l-1)-a(r-1) + (r+l-1)*( b(r-1)-b(l-1) ) + (r-l*r)*(r-l) );
}

int main(void){
  int l,r;
  while(~scanf("%d%d",&l,&r))
    printf("%lld\n",test(l,r)*10000);

  return 0;
}
*/
