#include <iostream>
#include <vector>


const static long long INF = 1000000000;

void warshall_floyd(std::vector< std::vector<int> > & array, int V);
void dijkstra(std::vector< std::vector<int> > & array, int s);

/* ワーシャルフロイド
 * 計算量 O(n^3)
 *
 * 引数
 * array: 隣接行列
 *    array[u][v]は辺e=(u, v)のコスト（存在しない場合はINF.
 *    ただしd[i][i]=0とする。）
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
 * cosdd
 */
void dijkstra(std::vector< std::vector<int> > & cost, std::vector<int> & d, bool used[], int s, int V) {
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
struct edge {int from, to, cost;};
void bellman_ford(std::vector<edge> & es, std::vector<int> & d, int E, int V, int s) {
  for(int i=0;i<d.size();i++) d[i] = INF;
  d[s] = 0;
  while(true) {
    bool update = false;
    for(int i=0;i<E;i++) {
      edge e = es[i];
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
bool find_negative_loop(std::vector<edge> & es, std::vector<int> & d, int E, int V) {
  for(int i=0;i<d.size();i++) d[i] = 0;

  for(int i=0;i<V;i++) {
    for(int j=0;j<E;j++) {
      edge e = es[j];
      if(d[e.to] > d[e.from] + e.cost) {
        d[e.to] = d[e.from] + e.cost;

        // n回目にも更新があるなら負の閉路が存在する
        if(i == V - 1) return true;
      }
    }
  }
  return false;
}

