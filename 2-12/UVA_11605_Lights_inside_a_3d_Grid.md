---
title: '[UVA 11605] Lights inside a 3d Grid'
date:  2018-02-12 16:39
tags:
  - 概率
  - 期望
  - 期望的线性性质
---

# 题目大意

给定一个大小为 $ N \times M \times P $ 的三维网格，每格有一个灯，初始时所有灯关闭。进行 $K$ 次操作，每次随机选择两个格子（可以重合），将以这两格为对角顶点的长方体内的所有灯的状态取反。问最终量着的灯数量的期望。
<!-- more -->

# 解题报告

每个点都是独立的，不会受到周围点的影响。

$$ ans = E \left( \sum A\_{i,j,k} \right) = \sum\_{i,j,k} E(A\_{i,j,k}) $$

只需求出每个点最终亮灯的期望即可。

设点 $A$ 被选择的概率为 $P(A)$，当且仅当 $A$ 被选择奇数次时亮灯，那么有
$$ E(A) = \sum\_{i=1,3,5,\cdots } ^ { i \leq k } C\_k^i \, P(A)^i \, (1-P(A))^{k-i} $$
可以看出这与二项式定理很像，但只有奇数项。
由
$$ ( P + (1 - P)) ^ k = \sum\_{i=0}^{k} C\_k^i \, P^i \, (1-P)^{k-i} $$
$$ - ( - P + (1 - P)) ^ k = - \sum\_{i=0}^{k} C\_k^i \,  (-1)^i \, P^i \, (1-P)^{k-i} $$
两式相加就消除了偶数项，就有
\begin{split}
  E(A) &= \frac { (P(A)+(1-P(A)))^k - (-P(A)+(1-P(A)))^k } {2} \\\\
       &= \frac {1 - (1 - 2P(A))^k } {2}
\end{split}
那么现在就只需算出 $P(A)$ 了。

因为每次选择的是一个长方体，对于每个长方体来说是等可能的，而对于每个点来说却是不等的。选择了一个矩形，等效于在X轴、Y轴、Z轴上分别选择三个区间。一个点 $A(x,y,z)$ 被选择，一定要保证 $x$ 被X轴上的区间覆盖到（$y$ 与 $z$ 亦然）。那么 $P(A\_{x,y,z}) = P(x) \cdot P(y) \cdot P(z) $，其中 $P(x)$ 为在X轴上点$x$被覆盖到的可能。

现在只需求出 $P(x)$ 即可，$P(y)$ 和 $P(z)$ 同理。
考虑一维空间上的区间选择：
  $$ a -- b -- c $$
一共有 9 种等可能的选择方法，$P(a) = P(c) = \frac{5}{9}$, $P(b) = \frac{7}{9}$ 。
可以发现，对于选择区间的端点 $x\_1,x\_2$，有
\begin{split}
  P(x) &= P(x\_1 \leq x \cap x\_2 \geq x) \cup P(x\_2 \leq x \cap x\_1 \geq x) \\\\
       &= P(x\_1 \leq x \cap x\_2 \geq x) + P(x\_2 \leq x \cap x\_1 \geq x) - P( x\_1 = x\_2 = x)\\\\
       &= 2 P(x\_1 \leq x) \cdot P(x\_2 \geq x) - P(x\_1=x) \cdot P(x\_2=x) \\\\
       &= 2 \frac { x } { n } \cdot \frac { n - x + 1 } { n } - \frac {1}{n} \cdot \frac {1}{n} \\\\
       &= \frac { 2x(n-x+1) - 1 } {n^2} \\\\
\end{split}
那么就可以求出答案了。

代码
``` cpp
int a,b,c,k;

inline double P(double x, double n){
  return (2*x*(n-x+1)-1)/n/n;
}

int main(void){
  int T; scanf("%d",&T);
  FORR(kase,1,T){
    scanf("%d%d%d%d",&a,&b,&c,&k);
    double px,py,pz,ans=0;
    FORR(x,1,a){
      px=P(x,a);
      FORR(y,1,b){
        py=P(y,b);
        FORR(z,1,c){
          pz=P(z,c);
          double p = px*py*pz;
          ans += ( 1 - pow(1-2*p,k) )/2;
        }
      }
    }
    printf("Case %d: %.10lf\n",kase,ans);
  }

  return 0;
}
```
