#include <vector>
#include "test_framework/generic_test.h"

using std::vector;

vector<vector<int>> GeneratePascalTriangle(int num_rows) {
  vector<vector<int>> res;
  for (int i = 0; i < num_rows; i++) {
    vector<int> ans;
    ans.emplace_back(1);
    for(int j=1;j<i;j++)
      ans.emplace_back(res[i-1][j-1]+res[i-1][j]);
    if(i > 0)
      ans.emplace_back(1);
    res.emplace_back(ans);
  }
  return res;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
