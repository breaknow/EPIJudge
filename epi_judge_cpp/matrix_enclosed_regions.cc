#include <stdexcept>
#include <string>
#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using namespace std;

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
	queue < pair<int, int>> Q;
	vector<vector<char>> &B = *board_ptr;
	int n = B.size(), m = B[0].size();
	vector<vector<bool>> visited(n, vector<bool>(m));
	for (int i = 0; i < n; i++) {
		visited[i][0] = visited[i][m - 1] = true;
		if (B[i][0] == 'W')
			Q.emplace(i, 0);
		if (B[i][m - 1] == 'W')
			Q.emplace(i, m - 1);
	}
	for (int i = 0; i < m; i++) {
		visited[0][i] = visited[n - 1][i] = true;
		if (B[0][i] == 'W')
			Q.emplace(0, i);
		if (B[n - 1][i] == 'W')
			Q.emplace(n - 1, i);
	}

	int xx[4] = { -1,0,1,0 }, yy[4] = { 0,1,0,-1 };

	while (!Q.empty()) {
		int x = Q.front().first, y = Q.front().second;
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = xx[i] + x;
			int ny = yy[i] + y;
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && B[nx][ny] == 'W' && !visited[nx][ny]) {
				visited[nx][ny] = true;
				Q.emplace(nx, ny);
			}
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!visited[i][j] && B[i][j] == 'W')
				B[i][j] = 'B';
	return;
}
vector<vector<string>> FillSurroundedRegionsWrapper(
	TimedExecutor& executor, vector<vector<string>> board) {
	vector<vector<char>> char_vector;
	char_vector.resize(board.size());
	for (int i = 0; i < board.size(); i++) {
		for (const string& s : board[i]) {
			if (s.size() != 1) {
				throw std::runtime_error("String size is not 1");
			}
			char_vector[i].push_back(s[0]);
		}
	}

	executor.Run([&] { FillSurroundedRegions(&char_vector); });

	board.clear();
	board.resize(char_vector.size(), {});
	for (int i = 0; i < board.size(); i++) {
		for (char c : char_vector[i]) {
			board[i].emplace_back(1, c);
		}
	}

	return board;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "board" };
	return GenericTestMain(
		args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
		&FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
