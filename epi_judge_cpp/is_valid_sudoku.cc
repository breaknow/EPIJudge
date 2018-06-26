#include <vector>
#include "test_framework/generic_test.h"

using std::vector;

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>> &partial_assignment) {
    const vector<vector<int>> &A = partial_assignment;
    for (int i = 0; i < 9; i++) {
        vector<bool> w(10), h(10), p(10);
        for (int j = 0; j < 9; j++) {
            if (w[A[i][j]] || h[A[j][i]])
                return false;
            w[A[i][j]] = h[A[j][i]] = true;
            if (p[A[(i / 3) * 3 + j / 3][(i % 3) * 3 + (j % 3)]])
                return false;
            p[A[(i / 3) * 3 + j / 3][(i % 3) * 3 + (j % 3)]] = true;
            w[0] = h[0] = p[0] = false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"partial_assignment"};
    return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                           &IsValidSudoku, DefaultComparator{}, param_names);
}
