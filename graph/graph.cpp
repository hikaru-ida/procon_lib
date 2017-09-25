#include <iostream>
#include <vector>


const static long long INF = 1000000000;

void warshall_floyd(std::vector< std::vector<int> > & array, int V);
void dijkstra(std::vector< std::vector<int> > & array, int s);

/* ワーシャるフロイド
 * 計算量 O(n^3)
 */
void warshall_floyd(std::vector< std::vector<int> > & array, int V) {
  for(int k=0;k<V;k++)
   for(int i=0;i<V;i++)
    for(int j=0;j<V;j++)
     array[i][j] = std::min(array[i][j], array[i][k]+array[k][j]);
}

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

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector< std::vector<int> > v;
  v = std::vector< std::vector<int> >(n, std::vector<int>(n, 0));

  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      if(i!=j) v[i][j] = INF;
    }
  }
  for(int i=0;i<m;i++) {
    int a, b, t;
    std::cin >> a >> b >> t;
    a--; b--;
    v[a][b] = t;
    v[b][a] = t;
  }
  warshall_floyd(v, n);
  long long ans = INF;
  for(int i=0;i<n;i++) {
    int mx = 0;
    for(int j=0;j<n;j++) {
      mx = std::max(mx, v[i][j]);
    }
    ans = std::min<long long>(ans, mx);
  }

  std::cout << ans << std::endl;
  return 0;

}
