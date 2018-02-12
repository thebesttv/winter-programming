---
title: '[UVA 11637] Garbage Remembering Exam'
date:  2018-02-12 17:38
tags:
  - 概率
  - 期望
  - 期望的线性性质
---

# 题目大意

给定一个长 $n$ 的环，其中所有元素有序。对这 $n$ 个环上的元素随机建立一条长 $n$ 的链。对于元素$a$和$b$，若它们在环上的距离和它们在链上的距离都不超过 $k$ ，则称$a$和$b$都是无效的。求平均有多少个无效的元素。
<!-- more -->

# 解题报告

正难则反，转化为求平均的有效元素，然后用 $n$ 减去它即可。

$$ ans = E \left(\sum 链上元素有效 \right) = \sum E(链上元素i有效) $$

```
     A1 <-  B1  i  B2  ->  A2
   ------|------x------|-------->
```

对于链上的第 i 个元素，其对应的环上元素的左右各有 $k$ 个不能靠近的元素，它们都要放到A1和A2组成的区间中，而剩下的 $n-2k-1$ 个元素则放入剩下的空位中。假设A1和A2共能放入x个元素，有
\begin{split}
  E(i) &= \frac { A\_{x}^{2k} \cdot A\_{n-2k-1}^{n-2k-1} } {A\_{n-1}^{n-1}} \\\\
       &= \frac { x! \cdot (n-2k-1)! } { (x-2k)! \cdot (n-1)! } \\\\
\end{split}
而 $x$ 的计算比较简便，两边分别计数即可：
$$ x = max(i-k-1,0) + max(n-i-k,0) $$

但如果只是这样，每计算一个 $E(i)$ 就要花 $O(k)$ 的时间，总的复杂度会变成 $O(nk)$，需要优化对 $E(i)$ 的求解。
对于 $E(i)$ 的推到式，两边同取 $ln$ ，有
  $$ ln(E(i)) = ln(x!) - ln(x-2k)! + ln(n-2k-1)! - ln(n-1)! $$
这样一来，只需初始化 $ln(1:k)$ ，就可以实现 $O(1)$ 求 $E(i)$ 。
初始化时，有 $ ln(x!) = ln(x) + ln(x-1)! $ 。

ps: 还有一个要注意的坑点，当 $n=1$ 时，答案一定是 $0$ 。

代码
``` cpp
const int MAX=100020;
int n,k;
long double lf[MAX];  // lf[i] = log(i!)

//期望的线性性质 E(a+b) = E(a) + E(b)
// E( sum{队列中的第i个单词是无效的期望} ) = sum{ E(i) }

int main(void){
  FOR(i,2,MAX) lf[i] = lf[i-1] + log(i);
  int kase=0;
  while(~scanf("%d%d",&n,&k) && n){
    double ans=0;
    if(n==1) ans=0; //<b> </b>
    else{
      FORR(i,1,n){
        int x = max(i-1-k,0) + max(n-i-k,0);
        if(x < 2*k) continue;
        double t = lf[x] - lf[x-2*k] + lf[n-1-2*k] - lf[n-1];
        ans += exp(t);  // exp(t) = e^t
      }
      ans = n-ans;
    }
    printf("Case %d: %.4lf\n",++kase,ans);
  }

  return 0;
}
```
