#include <iostream>
#include <vector>
#include <set>

struct union_find {
  std::vector<int> rank, par;
  int v_size;
  union_find() {}

  // 初期化
  union_find(int n) {
    v_size = n;
    rank.resize(n, 0);
    par.resize(n);
    for(int i=0;i<n;i++) {
      par[i] = i;
    }
  }

  // 木の根を求める
  int find(int x) {
    if(par[x] == x) {
      return x;
    } else {
      return par[x] = find(par[x]);
    }
  }

  // xとyの属する集合を併合
  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;

    if(rank[x] < rank[y]) {
      par[x] = y;
    } else {
      par[y] = x;
      if(rank[x] == rank[y]) rank[x]++;
    }
  }

  // xとyが同じ集合に属するか否か
  bool same(int x, int y) {
    return find(x) == find(y);
  }

  // グループの個数を数える
  int count() {
    std::set<int> st;
    for(int i=0;i<v_size;i++) {
      st.insert(find(i));
    }
    return st.size();
  }

};
