#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

using namespace std;

struct Item {
	int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
	vector<int> D(capacity + 1, 0);
	int ans = 0;
	for (Item i : items) {
		for (int j = capacity; j >= 0; j--) {
			if ((j == 0 || D[j] > 0) && j + i.weight <= capacity && D[j + i.weight] < D[j] + i.value) {
				D[j + i.weight] = D[j] + i.value;
				if (ans < D[j + i.weight])
					ans = D[j + i.weight];
			}
		}
	}
	return ans;
}
template <>
struct SerializationTraits<Item> : UserSerTraits<Item, int, int> {};

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "items", "capacity" };
	return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
		&OptimumSubjectToCapacity, DefaultComparator{},
		param_names);
}
