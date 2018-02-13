---
title: '[JSOI 冬令营] D6T1 白日梦'
date:  2018-02-13 17:17
tags:
  - 概率
  - 期望
---

# 题目大意

你被扔到一个岛上住 $n+1$ 天（编号从$0$到$n$），每天要么是晴天，要么刮台风。第 $0$ 天一定是晴天。对于第 $i$ 天，若是晴天，则有 $p$ 的概率会变天，使得接下来 $m$ 天都刮台风，但第 $i+m+1$ 天一定转晴。
每天，若是晴天，则一定能抓到 $a$ 只猎物；若刮台风，则有 $1-d$ 的可能抓到 $b$ 只猎物，有 $d$ 的可能抓到 $c$ 只猎物。求出第 $1$ 天到第 $n$ 天猎物总量的期望。
给出的所有小数都是在模 $998244353$ 的意义下的，答案也需取模。
<!-- more -->

若小数 $a$ 写成 $\frac{x}{y}$ 的形式，则给出的数 $ a' = x \times y^{-1} $ ，其中 $y^{-1}$ 表示 $y$ 在模意义下的逆元。

# 解题报告

一开始到剩余系就方了，不过其实剩余系在这里并没有太大影响。
对于小数 $ a = \frac{x}{y} $ ，有 $ 1 - a = \frac{y-x}{y} = ( y - x ) \times y^{-1} = 1 - a + MOD $ 。于是就可以欢乐地切题了 XD

首先，和的期望等于期望的和，于是 $ ans = \sum\_{i=1}^{n} E(i) $ 。
令 $P[i][0/1]$ 表示在第 i 天，岛上天气为晴/刮台风的可能，考虑用 $P[i][0]$ 更新其后继状态：
  $$ P[i][0] \to P[(i+1) : (i+m)][1] += P[i][0] \times p, P[i+m+1][0] += P[i][0] \times p $$
  $$ P[i][0] \to P[i+1][0] += P[i][0] \times (1-p) $$
答案为
  $$ \sum\_{i=1}^{n} P[i] \cdot a + (1-P[i]) ( (1-d) \cdot b + d \cdot c ) \,\, mod \,\, 998244353 $$

然而这样 $O(mn)$ 会直接T……考试的时候就是这样，50多个人里十几个 AC ，就我一个 $50$ ……

考虑对于任意 $i$ ，始终有 $P[i][1] = 1-P[i][0]$ ，那么就可以去掉 $P[i][1]$ 。
令 $P[i]$ 表示岛上第 $i$ 天为晴天的可能，则
  $$ P[i] \to P[i+1+m] += P[i] \times p $$
  $$ P[i] \to P[i+1] += P[i] \times (1-p) $$
这样就可以不T了。

代码
``` cpp
const LL MOD=998244353;
const int MAX=1000020;
LL n,m,p,d,a,b,c;
LL f[MAX];

int main(void){
  scanf("%lld%lld",&n,&m);
  scanf("%lld%lld",&p,&d);
  scanf("%lld%lld%lld",&a,&b,&c);
  
  f[0]=1;
  FOR(i,0,n){
    f[i+1] = ( f[i+1] + (1+MOD-p)*f[i]%MOD )%MOD;
    if(i+m+1<=n) f[i+m+1] = ( f[i+m+1] + p*f[i]%MOD )%MOD;
  }

  LL ans=0;
  FORR(i,1,n) ans = ( ans + f[i]*a%MOD + ( (1+MOD-f[i]) *  ( (1+MOD-d)*b%MOD + d*c%MOD )%MOD )%MOD )%MOD;
  printf("%lld\n",ans);

  return 0;
}
```
