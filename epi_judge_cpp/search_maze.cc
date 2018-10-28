#include <istream>
#include <string>
#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
using namespace std;
typedef enum { kWhite, kBlack } Color;
struct Coordinate {
	bool operator==(const Coordinate& that) const {
		return x == that.x && y == that.y;
	}

	int x, y;
};
vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s,
	const Coordinate& e) {
	vector<vector<Coordinate>> path(maze.size(), vector<Coordinate>(maze[0].size()));
	vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size()));
	queue<Coordinate> Q;
	int xx[4] = { -1,0,1,0 }, yy[4] = { 0,1,0,-1 };
	Q.emplace(s);
	while (!Q.empty()) {
		Coordinate cur = Q.front();
		Q.pop();
		if (cur == e)
			break;
		for (int i = 0; i < 4; i++) {
			int nx = xx[i] + cur.x;
			int ny = yy[i] + cur.y;
			if (nx >= 0 && nx < maze.size() && ny >= 0 && ny < maze[0].size() && maze[nx][ny] == kWhite) {
				if (!visited[nx][ny]) {
					path[nx][ny] = cur;
					visited[nx][ny] = true;
					Coordinate temp;
					temp.x = nx;
					temp.y = ny;
					Q.emplace(temp);
				}
			}
		}
	}
	vector<Coordinate> ans;
	if (!visited[e.x][e.y])
		return ans;
	Coordinate temp = e;
	while (!(temp == s)) {
		ans.emplace_back(temp);
		temp = path[temp.x][temp.y];
	}
	ans.emplace_back(temp);
	reverse(ans.begin(), ans.end());
	return ans;
}
template <>
struct SerializationTraits<Color> : SerializationTraits<int> {
	using serialization_type = Color;

	static serialization_type Parse(const std::string& str) {
		return static_cast<serialization_type>(
			SerializationTraits<int>::Parse(str));
	}

	static serialization_type JsonParse(const json_parser::Json& json_object) {
		return static_cast<serialization_type>(
			SerializationTraits<int>::JsonParse(json_object));
	}
};

template <>
struct SerializationTraits<Coordinate> : UserSerTraits<Coordinate, int, int> {
	static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
		return {};
	}

	static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
	const Coordinate& prev, const Coordinate& cur) {
	if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
		cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == kWhite)) {
		return false;
	}
	return cur == Coordinate{ prev.x + 1, prev.y } ||
		cur == Coordinate{ prev.x - 1, prev.y } ||
		cur == Coordinate{ prev.x, prev.y + 1 } ||
		cur == Coordinate{ prev.x, prev.y - 1 };
}

bool SearchMazeWrapper(TimedExecutor& executor,
	const vector<vector<Color>>& maze, const Coordinate& s,
	const Coordinate& e) {
	vector<vector<Color>> copy = maze;

	auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

	if (path.empty()) {
		return s == e;
	}

	if (!(path.front() == s) || !(path.back() == e)) {
		throw TestFailure("Path doesn't lay between start and end points");
	}

	for (size_t i = 1; i < path.size(); i++) {
		if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
			throw TestFailure("Path contains invalid segments");
		}
	}

	return true;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "maze", "s", "e" };
	return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
		&SearchMazeWrapper, DefaultComparator{}, param_names);
}
