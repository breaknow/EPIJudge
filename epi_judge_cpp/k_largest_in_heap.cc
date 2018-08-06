#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

struct HeapEntry{
  int val, pos;
  bool operator<(const HeapEntry &rhs) const {
    return val < rhs.val;
  }
};

vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
  priority_queue<HeapEntry, vector<HeapEntry>, less<>> max_heap;
  vector<int> ans;
  if(A.empty())
    return ans;
  max_heap.emplace(HeapEntry{A[0], 0});
  for(int i=0;i<min(k, (int)A.size());i++){
    HeapEntry cur(max_heap.top());
    max_heap.pop();
    ans.emplace_back(cur.val);
    if(cur.pos * 2+1 < A.size()) // start from 0
		max_heap.emplace(HeapEntry{A[cur.pos * 2+1], cur.pos * 2+1});
	if(cur.pos * 2 + 2< A.size())
    	max_heap.emplace(HeapEntry{A[cur.pos * 2 + 2], cur.pos * 2+2});
  }
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
