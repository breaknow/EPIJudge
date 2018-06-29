#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
	vector<vector<int>> &A = *square_matrix_ptr;
	int n = A.size();
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < (n+1) / 2; j++) {
			int temp = A[i][j];
			A[i][j] = A[n - 1 - j][i];
			A[n - 1 - j][i] = A[n - 1 - i][n - 1 - j];
			A[n - 1 - i][n - 1 - j] = A[j][n - 1 - i];
			A[j][n - 1 - i] = temp;
		}
	}
	return;
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
	RotateMatrix(&square_matrix);
	return square_matrix;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "square_matrix" };
	return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
		&RotateMatrixWrapper, DefaultComparator{},
		param_names);
}
