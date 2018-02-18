---
title: '网络流学习笔记'
date: 2017-12-14
tags:
  - 网络流
  - TODO
---

网络流的学习笔记
<!-- more -->

# Dinic 模板
``` cpp
//const int MAX=1020;
const int INF=0x3f3f3f3f;
struct Edge{
  int u,v,cap,flow;
};

struct Dinic{
  int n,m,s,t;
  VR<Edge> edge;
  VR<int> G[MAX];
  int cur[MAX],d[MAX];
  bool vis[MAX];
  int q[MAX],head,tail;

  void clear(int n=MAX-1){
    edge.clear();
    FORR(i,0,n) G[i].clear();
  }
  void addEdge(int u, int v, int cap){
    edge.push_back((Edge){u,v,cap,0});
    edge.push_back((Edge){v,u,0,0});
    m=edge.size();
    G[u].push_back(m-2);
    G[v].push_back(m-1);
  }
  bool bfs(){
    MST(vis,0);
    head=tail=0;
    q[tail++]=s; d[s]=0; vis[s]=1;
    while(head<tail){
      int u=q[head++];
      FOR(i,0,G[u].size()){
        Edge & e=edge[G[u][i]];
        if(!vis[e.v] && e.cap>e.flow){
          vis[e.v]=1;
          d[e.v]=d[u]+1; q[tail++]=e.v;
        }
      }
    }
    return vis[t];
  }
  int dfs(int u, int a){
    if(u==t || !a) return a;
    int ans=0,f;
    for(int &i=cur[u];i<G[u].size();i++){
      Edge & e=edge[G[u][i]];
      if(d[e.v]==d[u]+1 && (f=dfs(e.v,min(a,e.cap-e.flow)))>0){
        e.flow+=f; edge[G[u][i]^1].flow-=f;
        ans+=f; a-=f;
        if(!a) break;
      }
    }
    return ans;
  }
  int MF(int s_, int t_){
    s=s_,t=t_;
    int ans=0;
    while(bfs()){
      MST(cur,0); ans+=dfs(s,INF);
    }
    return ans;
  }
};
```

# 无源无汇有容量上下界网络的可行流
在网络中，没有源点和汇点，且每条边不仅有容量上界 c ，还有容量下界 b ，求出该网络中的可行流。

建立一个源点 s 和汇点 t ，对每条的边 u->v ，建立 s->v、u->t 容量为 b 的边，u->v 容量为 c-b 的边，最后跑一次普通的最大流即可。
当且仅当每条 s->u（或u->t）的边都满载，才有可行流。

例题：[ZOJ 2314](https://thebesttv.github.io/2017/12/16/ZOJ_2314_Reactor_Cooling/)

# 有源有汇有容量上下界网络的可行流
非常类似于之前的无源无汇，建立超级源点 ss 和超级汇点 tt ，对于所有边都改为 ss->v, u->tt, u->v 的三条边。并且一定要**建立一条 t->s 的容量为 INF 的边**，否则流量不能平衡。

例题：[ZOJ 3229]()

# 最大权闭合子图

最大权闭合子图适用于一种需要先决条件才能获得收益的问题。

问题原型：给定 $n$ 个方案和 $m$ 个物品，第 $i$ 个方案有 $a\_i$ 的收益，第 $i$ 个物品要花费 $b\_i$ 元。每个方案都有一定的先决条件，要求拥有集合 $S\_i$ 中的所有物品才能选择该方案。（每个物品只需有一个）求解最大的收益。

建立模型：
- 从 S 向每个方案 $i$ 连接容量为 $a\_i$ 的边
- 从每个物品 $i$ 向 T 连接容量为 $b\_i$ 的边
- 从每个方案 $i$ 向 $S\_i$ 的所有物品连接容量为 INF 的边

答案即为 sum{ai} - 最小割

分析：
首先，任意割的每一条边都只能为 S->Xi 或 Yi->T ，即要么在左边，要么在右边，不可能在中间容量为 INF 的边上。
- 若割选择 S->Xi ，则表示不选方案 $i$ ，因为最终答案会减去这条边的容量，即 $a\_i$ ；
- 若割选择 Yi->T ，则表示购买物品 $i$ ，为选择方案作出准备。最终答案会减去 $b\_i$ ，但也许可以通过选择更多的方案来弥补这一损失。

而割又保证不会有 Xi->Yj 的边，那么就保证了被选择的方案一定满足其先决条件。
既然每个割都是一个正确解，那么最小割即为最优解。
