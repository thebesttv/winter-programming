---
title: '[NOI 2005] 聪聪和可可'
date:  2018-02-13 16:21
tags:
  - 概率
  - 期望
  - 最短路
---

# 题目大意

给定一个无向图，一只猫和一只老鼠在图上移动。在每个单位时间内：
- 猫先移动一步，到达离老鼠最近的序号最小的点。如果还没抓到老鼠，再同样移动一步。若与老鼠相遇，则吃掉老鼠；
- 若老鼠还没被吃，则它能够向周围距离不超过 $1$ 的点（包括当前所在点）等概率地移动。

已知猫和老鼠的起点，求出猫抓到老鼠的平均消耗时间。
<!-- more -->

# 解题报告

令 $f[i][j]$ 表示猫在 $i$ 点，老鼠在 $j$ 点时，猫抓老鼠的期望消耗时间，则
  $$ f[i][j] = \sum f[g[i][j]][k] / (p+1) $$
其中 $g[i][j]$ 表示猫在 $i$ 点，老鼠在 $j$ 点，猫将会走到哪里，$p$ 表示 $j$ 周围距离为 $1$ 的节点数。显然只要 $i,j$ 不变，$g[i][j]$ 不会改变。那么就可以预处理出来。

有一个很好的办法，先 Floyd 求出最短路，令 $to[i][j]$ 表示猫在 $i$ 点，老鼠在 $j$ 点，猫**最多走一步**将会走到哪里，则当且仅当 $d[i][k]=1$ 并且 $d[i][j] = d[i][k] + d[k][j] $ 时 $to[i][j]=k$ 。这样以来，$g$ 就可以轻松确定了。

代码
``` cpp
const int MAX=1020;
const int INF=0x3f3f3f3f;
int n,m,s,t,d[MAX][MAX];
int to[MAX][MAX]; // to[i][j]: 从 i 到 j ，走一步能走到的最近点（序号最小）
VR<int> G[MAX];
double check_f[MAX][MAX];
bool vis[MAX][MAX];

double f(int s, int t){
  if(s==t) return 0.0;
  if(vis[s][t]) return check_f[s][t];
  double &a=check_f[s][t]; vis[s][t]=1;
  if(d[s][t]<=2) a=1.0;
  else{
    int v=to[to[s][t]][t]; a=f(v,t);
    FOR(i,0,G[t].size()) a+=f(v,G[t][i]);
    a = a/(1+G[t].size()) + 1.0;
  }
  return a;
}

int main(void){
  MST(d,0x3f);
  scanf("%d%d%d%d",&n,&m,&s,&t);
  FORR(i,1,n) d[i][i]=0;
  int u,v;
  while(m--){
    scanf("%d%d",&u,&v);
    d[u][v]=d[v][u]=1;
    G[u].push_back(v); G[v].push_back(u);
  }
  // Floyd
  ROR(k,n,1) FORR(i,1,n) if(d[i][k]<INF) FORR(j,1,n)
    d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
  // init to
  FORR(i,1,n) FORR(j,1,n){
    if(d[i][j]<=1) to[i][j]=j;
    else FORR(k,1,n) if(d[i][k]==1 && d[i][j]==d[i][k]+d[k][j]){
      to[i][j]=k; break;
    }
  }

  printf("%.3lf\n",f(s,t));

  return 0;
}
```
