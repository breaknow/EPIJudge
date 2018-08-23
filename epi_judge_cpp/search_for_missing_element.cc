#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct DuplicateAndMissing {
	int duplicate, missing;
};

DuplicateAndMissing FindDuplicateMissing(const vector<int>& A) {
	DuplicateAndMissing ans;
	int sum[2], xor[2];
	sum[0] = sum[1] = xor[0] = xor[1] = 0;
	for (int i = 0; i < A.size(); i++) {
		sum[0] += i;
		xor[0] ^= i;
		sum[1] += A[i];
		xor[1] ^= A[i];
	}
	int diff = sum[1] - sum[0];
	int s = xor[0] ^ xor[1];
	ans.duplicate = (s + diff) / 2;
	ans.missing = s - ans.duplicate;
	return ans;
}
template <>
struct SerializationTraits<DuplicateAndMissing>
	: UserSerTraits<DuplicateAndMissing, int, int> {
};

bool operator==(const DuplicateAndMissing& lhs,
	const DuplicateAndMissing& rhs) {
	return std::tie(lhs.duplicate, lhs.missing) ==
		std::tie(rhs.duplicate, rhs.missing);
}

std::ostream& operator<<(std::ostream& out, const DuplicateAndMissing& x) {
	return out << "duplicate: " << x.duplicate << ", missing: " << x.missing;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A" };
	return GenericTestMain(
		args, "search_for_missing_element.cc", "find_missing_and_duplicate.tsv",
		&FindDuplicateMissing, DefaultComparator{}, param_names);
}
