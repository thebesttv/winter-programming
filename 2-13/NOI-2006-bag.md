---
title: '[NOI 2006] 神奇的口袋'
date:  2018-02-13 16:46'
tags:
  - 概率
  - Pólya 瓦罐模型
---

# 题目大意

给定一个袋中的 $t$ 种颜色的球，颜色为 $i$ 的球有 $a\_i$ 个。每次从袋中随机摸出一个球，记录其颜色，在将它与另外 $d$ 个颜色相同的球一同放入袋中。这样以来，会产生一个颜色序列。
再给出 $n$ 个条件 $(x\_i,y\_i)$ 表示第 $x\_i$ 次摸出颜色为 $y\_i$ 的球。求出颜色序列满足所有条件的可能，并将结果以最简分数形式输出。
<!-- more -->

# 解题报告

最近好像题目越来越长了……

首先，有一个所谓的「Pólya 瓦罐模型」：
在一个瓦罐中有 $n$ 个球，其中有且仅有 $n\_1$ 个黑球，$n\_2$ 个白球。每次从中摸出一个球，在将其与另外 $r$ 个颜色相同的球重新放入罐中，可以证明：任意一次摸出黑球的可能都是 $\frac{n\_1}{n}$ ，摸出白球的可能都是 $\frac{n\_2}{n}$。
可以通过数学归纳法证明。

那么，仿佛可以自然地联想到：给定条件的 $x$ 其实是没有意义的，唯一有意义的只是 $y$ 的相对顺序。那么就可以令 $x\_i=i$ ，直接求解。

当然会需要使用高精度，可以在计算时将分子和分母分别以 $\prod p\_i^{k\_i} 的形式存储，最后化简后再用高精度乘法输出。
~~（表示直接而复制粘贴之前的模板 XD）~~

代码
``` cpp
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
```
