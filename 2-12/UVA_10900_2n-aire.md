---
title: '[UVA 10900] So you want to be a 2n-aire?'
date:  2018-02-12 15:26
tags:
  - 概率
  - 连续概率
  - 期望
  - HARD
  - TODO
---

# 题目大意

你正在玩一个游戏，一开始手中有 1 元。你可以依次回答 $n$ 个问题。对于每个问题，可以
- 放弃回答，带着手中的奖金退出游戏。
- 回答问题。如果成功，则进入下一轮，奖金加倍；如果失败，则游戏结束，你一分钱也拿不到。

若正确回答完所有 $n$ 个问题，将得到 $2^n$ 元的奖金。
对于所有问题，回答成功的概率在 $[t,1]$ 上均匀分布。
求出在最优策略下（即让奖金的期望尽量大），拿走奖金的期望。
<!-- more -->

# 解题报告

说实话这道题困扰了我好久……

首先，考虑已经正确回答了 i 个问题的情况。此时，有放弃和继续两种决策。
- 如果放弃，则可以拿到 $2^i$ 元奖金。
- 如果继续，则期望的奖金为 正确回答第 i+1 个问题的概率 * 答对第 i+1 个问题之后的最大期望奖金。

也就是说，当前的决策是受之后状态的影响的。
那么想到逆序递推。

令 $d[i]$ 表示正确回答 i 个问题之后的最大期望奖金，则
  $$ d[i] = P(放弃) \times 2^i + P(继续) \times P(正确回答第 i+1 个问题) \times d[i+1] $$
答案即为 $d[0]$ 。
因为回答对问题的可能是在 $[t,1]$ 上均匀分布的，那么可以将 $d[i]$ 看作在 $p = t \thicksim 1 $ 上的一个积分，即
  $$ d[i] = \int\_t^1 max\{ 2^i, p \times d[i+1] \} \\,{\rm d}p $$
显然，一般情况下有 $d[i]$ 先取 $2^i$ ，再取 $p \times d[i+1]$ 。那么就需要分类讨论求出 $d[i]$ 。

$ 2^i = p \times d[i+1] $ 为分界线，则令 $ p\_0 = \frac{ 2^i }{ d[i+1] } $ ，$ p\_1 = \frac{ p\_0 - t }{ 1 - t } 。
- 当 $ p < p\_0 $ 时，选择放弃，期望有 $ p\_1 \times 2^i $ 的奖金。
- 当 $ p \geq p\_0 $ 是，选择继续，期望有 $ (1 - p\_1) \frac{ 1 + p\_1 }{2} \times d[i+1] $ 的奖金。

由此得出，$ d[i] = p\_1 \times 2^i + (1 - p\_1) \frac{ 1 + p\_1 }{2} \times d[i+1] $ 。

不过我始终在这个式子上纠结。

为什么 $p\_1 = \frac{ p\_0 - t }{ 1 - t }$ 要除上 $1-t$ ？
可以这么想：回答正确的概率 $p$ 始终是在 [t,1] 上均匀分布的，无论这个区间有多长，$p$ 的个数都可以说是不变的。（当然前提是 $ t \neq 1 $）而且再看 $d[i]$ 最初的公式，$(1+p\_1)/2$ 正是正确回答问题的概率。

这篇题解可能还有许多不完善的地方，可能将来某一天回顾的时候，思路能清晰一点吧。

代码
``` cpp
const int MAX=50;
int n; double t,d[MAX];

int main(void){
  while(~scanf("%d%lf",&n,&t) && n){
    d[n] = 1<<n;

    ROR(i,n-1,0){
      double p0 = max(t, (1<<i)/d[i+1]);
      double p1 = (p0-t)/(1-t);
      d[i] = p1*(1<<i) + (1-p1)*(1+p0)/2*d[i+1];
    }

    printf("%.3lf\n",d[0]);
  }

  return 0;
}
```