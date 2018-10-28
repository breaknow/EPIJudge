#include <deque>
#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;
using namespace std;

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
	vector<deque<bool>> &image = *image_ptr;
	queue<pair<int, int>> Q;
	int xx[4] = { -1,0,1,0 }, yy[4] = { 0,1,0,-1 };
	bool color = image[x][y];
	image[x][y] = !color;
	Q.emplace(x, y);
	while (!Q.empty()) {
		x = Q.front().first;
		y = Q.front().second;
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = xx[i] + x;
			int ny = yy[i] + y;
			if (nx >= 0 && nx < image.size() && ny >= 0 && ny < image[0].size() && image[nx][ny] == color) {
				image[nx][ny] = !color;
				Q.emplace(nx, ny);
			}
		}
	}
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
	vector<vector<int>> image) {
	vector<deque<bool>> b;
	b.reserve(image.size());
	for (const vector<int>& row : image) {
		deque<bool> tmp;
		tmp.resize(row.size());
		for (int i = 0; i < row.size(); ++i) {
			tmp[i] = static_cast<bool>(row[i]);
		}
		b.push_back(tmp);
	}

	executor.Run([&] { FlipColor(x, y, &b); });

	image.resize(b.size());

	for (int i = 0; i < image.size(); ++i) {
		image[i].resize(b.size());
		for (int j = 0; j < image[i].size(); ++j) {
			image[i][j] = b[i][j];
		}
	}
	return image;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "x", "y", "image" };
	return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
		&FlipColorWrapper, DefaultComparator{}, param_names);
}
