#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
  priority_queue<int, vector<int>, greater<>> min_heap;
  vector<int>ans;
  if(sequence_begin == sequence_end)
    return ans;
  while(sequence_begin != sequence_end){
    if(min_heap.size() > 2 * k){
      ans.emplace_back(min_heap.top());
      min_heap.pop();
    }
    min_heap.emplace(*sequence_begin++);
  }
  while(!min_heap.empty()){
    ans.emplace_back(min_heap.top());
    min_heap.pop();
  }
  return ans;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
