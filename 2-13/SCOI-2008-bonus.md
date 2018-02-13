---
title: '[SCOI 2008] 奖励关'
date:  2018-02-13 17:51
tags:
  - 概率
  - 期望
---

# 题目大意

有 $n$ 种物品，每种物品都有一个可正可负可为零的价值，且选取第 $i$ 种物品要满足它的先决条件：在选取之前已拥有集合 $Si$ 中的所有物品。
有 $k$ 轮，每轮随机给出一个物品，你可以决定是否拿取。询问采取最优策略时能够得到的期望价值。
<!-- more -->

# 解题报告

这是一道类似于 [UVA 10900] 的题，不过缺少了连续概率使得它非常友善 XD

考虑若当前拥有的物品集合为 $S$ ，在某轮中，给出了第 $i$ 种物品：
- 首先判断当前是否满足它的先决条件，若不满足则直接决策不拿。
- 若它的价值非负，则决策拿了一定不会更坏。
- 若它的价值为负，若在之前已经拿取过同种物品，则决策不拿一定不会更坏。
- 若之前未拿取过同种物品，则要判断，拿和不拿的收益哪个更大就决策哪个。

可以看出这又是一个逆序递推的过程。
令 $f[i,S]$ 表示当前在第 $i$ 轮已经决策好，在决策前拥有的物品集合为 $S$ 时，在之后 $n-i$ 轮能获得的的期望价值，则需要枚举每一种可能得到的物品，对于第 $j$ 种物品，依旧如上方一样：
- 若不能选取该物品，则 $f[i,S] += f[i+1,S]$
- 否则，当它的价值非负时，选取更好，即 $f[i,S] += a[i] + f[i+1, S \cup {j} ]$
- 否则，若之前已拿过它，则不选，$f[i,S] += f[i+1,S]$
- 否则，判断拿取（得到 $a[i] + f[i+1, S \cup {j} ]$的价值）和不拿取（得到 $f[i+1,S]$的价值）哪个更好决策哪个。

好吧还是用代码实现比较清晰……
``` cpp
FORR(i,1,n){
  if((S & req[i])==req[i]){
    if(a[i]>=0) ans += f(cur+1,S|(1<<i))+a[i];
    else{
      if((S&(1<<i))==0){ //分数为负且未吃过
        ans += max( f(cur+1,S|(1<<i))+a[i], f(cur+1,S));
      }else ans+=f(cur+1,S);  //<b> </b>
    }
  }else ans+=f(cur+1,S);      //<b> </b>
}
```

采用记忆化搜索，答案即为 $f[0,0]$ 。要注意的就是每次决策都要考虑完整，不能“不拿就不决策”。

代码
``` cpp
const int MAXK=120;
const int MAXN=20;
int n,k,a[MAXN],req[MAXN];
double check_f[MAXK][1<<16];
bool vis[MAXK][1<<16];

double f(int cur, int S){ //当前在第 cur 次投掷已经决策完，决策前吃过的物品集合为 S
  if(cur==k) return 0;
  if(vis[cur][S]) return check_f[cur][S];
  double &ans=check_f[cur][S]; vis[cur][S]=1;
  FORR(i,1,n){
    if((S & req[i])==req[i]){
      if(a[i]>=0) ans += f(cur+1,S|(1<<i))+a[i];
      else{
        if((S&(1<<i))==0){ //分数为负且未吃过
          ans += max( f(cur+1,S|(1<<i))+a[i], f(cur+1,S));
        }else ans+=f(cur+1,S);  //<b> </b>
      }
    }else ans+=f(cur+1,S);      //<b> </b>
  }
  ans/=n;
  return ans;
}

int main(void){
  scanf("%d%d",&k,&n);
  int t;
  FORR(i,1,n){
    scanf("%d%d",&a[i],&t);
    while(t){
      req[i]|=1<<t;
      scanf("%d",&t);
    }
  }

  printf("%.6lf\n",f(0,0));

  return 0;
}
```
