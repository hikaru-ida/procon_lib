#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


#define TO_STRING(VariableName) # VariableName

void show_list2d(const std::vector< std::vector<int> > & v, int k);
void show_list2d(const std::vector< std::vector<int> > & v, int k=4) {
  for(int i=0;i<v.size();i++) {
    for(int j=0;j<v[i].size();j++) {
      std::cout << "[" << i << "]";
      std::cout << "[" << j << "]";
      std::cout << std::setw(k) << v[i][j] << std::endl;
    }
  }
}


void show_matrix(const std::vector<int> & v, int k=4) {
  for(int i=0;i<v.size();i++) {
    std::cout << "[" << i << "]";
    std::cout << std::setw(k) << v[i] << std::endl;
  }
}

/* 多次元のvectorを表示
 * v: 多次元vector
 * k: 最小出力桁数
 */
void show_matrix(const std::vector< std::vector<int> > & v, int k=4) {
  int keta=0;
  int vsize = v.size();
  while(vsize) {
    vsize /= 10;
    keta++;
  }
  std::cout << std::setw(keta+2) << " ";

  // 列番号の表示
  for(int i=0;i<v.size();i++) {
    std::string col_ix = "["+ std::to_string(i) + "]";
    std::cout << std::setw(k) << col_ix;
  }
  std::cout  << std::endl;


  for(int i=0;i<v.size();i++) {
    // 行番号の表示
    std::string row_ix = "["+std::to_string(i)+"]";
    std::cout << std::setw(keta) << row_ix;
    // 行列の表示
    for(int j=0;j<v[0].size();j++) {
      std::cout << std::setw(k) << v[i][j];
    }
    std::cout << std::endl;
  }

}

