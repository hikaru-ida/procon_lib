#include <iostream>
#include <vector>
#include <queue>
#include <utility>


const static long long INF = 1000000000;

void warshall_floyd(std::vector< std::vector<int> > & array, int V);
void dijkstra(std::vector< std::vector<int> > & array, int s);

struct edge1 {int from, to, cost;};
struct edge2 {int to, cost;};

/* ワーシャルフロイド
 * 計算量 O(n^3)
 *
 * 引数
 * array: 隣接行列
 *    array[u][v]は辺e=(u, v)のコスト（存在しない場合はINF.
 *    ただしd[i][i]=0とする。）
 * arrayの初期化方法
 * vector< vector<int> > v(n, vector<int>(n));
 * V: 頂点の数
 *
 */
void warshall_floyd(std::vector< std::vector<int> > & array, int V) {
  for(int k=0;k<V;k++)
   for(int i=0;i<V;i++)
    for(int j=0;j<V;j++)
     array[i][j] = std::min(array[i][j], array[i][k]+array[k][j]);
}


/* ダイクストラ
 * 計算量 O(|E|log|V|)
 *
 * 引数
 * vector<edge> G[MAX_V]
 * int d[MAX_V]
 * int V
 * int s
 *
 */


void dijkstra(std::vector< std::vector<edge2> > & G, std::vector<int> & d, int V, int s) {
  std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > que;
  for(int i=0;i<V;i++) d[i] = INF;
  d[s] = 0;
  que.push(std::pair<int, int>(0, s));

  while(!que.empty()) {
    std::pair<int, int> p = que.top(); que.pop();
    int v = p.second;
    if(d[v]<p.first) continue;
    for(int i=0;i<G[v].size();i++) {
      edge2 e = G[v][i];
      if(d[e.to]>d[v]+e.cost) {
        d[e.to] = d[v] + e.cost;
        que.push(std::pair<int, int>(d[e.to], e.to));
      }
    }
  }
}


/* ダイクストラ
 * 計算量 O(|V|^2)
 */
void dijkstra2(std::vector< std::vector<int> > & cost, std::vector<int> & d, bool used[], int s, int V) {
  for(int i=0;i<V;i++) d[i] = INF;
  for(int i=0;i<V;i++) used[i] = false;
  d[s] = 0;

  while(true) {
    int v = -1;
    for(int u=0;u<V;u++) {
      if(!used[u] && (v == -1 || d[u] < d[v])) v = u;
    }
    if(v == -1) break;
    used[v] = true;
    for(int u = 0;u < V;u++) {
      d[u] = std::min(d[u], d[v] + cost[v][u]);
    }
  }
}


/* ベルマンフォード
 *
 * 計算量 O(|E||V|)
 */
void bellman_ford(std::vector<edge1> & es, std::vector<int> & d, int E, int V, int s) {
  for(int i=0;i<d.size();i++) d[i] = INF;
  d[s] = 0;
  while(true) {
    bool update = false;
    for(int i=0;i<E;i++) {
      edge1 e = es[i];
      if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
        d[e.to] = d[e.from] + e.cost;
        update = true;
      }
    }
    if(!update) break;
  }
}

  /* ベルマンフォードによる負閉路の検出
   *
   *
   */
bool find_negative_loop(std::vector<edge1> & es, std::vector<int> & d, int E, int V) {
  for(int i=0;i<d.size();i++) d[i] = 0;

  for(int i=0;i<V;i++) {
    for(int j=0;j<E;j++) {
      edge1 e = es[j];
      if(d[e.to] > d[e.from] + e.cost) {
        d[e.to] = d[e.from] + e.cost;

        // n回目にも更新があるなら負の閉路が存在する
        if(i == V - 1) return true;
      }
    }
  }
  return false;
}

