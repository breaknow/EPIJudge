#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
	vector<int> &A = *A_ptr; // �����ʹ�� ������
	int next = 0;
	for (int i = 0; i < A.size(); i++) 
		if (i + 1 == A.size() // �� ������ ���� �;� �迭 ���� ������ ���� �ʴ´�.
			|| A[i] != A[i + 1])
			A[next++] = A[i];
	A.resize(next);
	return next;
}
vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
	int end = executor.Run([&] { return DeleteDuplicates(&A); });
	A.resize(end);
	return A;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "A" };
	return GenericTestMain(
		args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
		&DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
