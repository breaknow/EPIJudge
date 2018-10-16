#include <string>
#include <unordered_set>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

using namespace std;

void dfs(int p, vector<vector<bool>> &D, vector<string> &ans, unordered_set<string> &duplicate, const string &domain) {
	if (p < 0)
		return;
	for (int i = 1; i <= domain.length(); i++) {
		if (D[p][i]) {
			string temp = domain.substr(p - i + 1, i);
			//if (duplicate.find(temp) == duplicate.end()) {
				ans.emplace_back(temp);
				//duplicate.emplace(temp);
				dfs(p - i, D, ans, duplicate, domain);
				return;
			//}
		}
	}
}

vector<string> DecomposeIntoDictionaryWords(
	const string& domain, const unordered_set<string>& dictionary) {
	vector<vector<bool>> D(domain.length() + 1);
	for (int i = 0; i < domain.length(); i++) {
		D[i].resize(domain.length() + 1);
		if (dictionary.find(domain.substr(0, i + 1)) != dictionary.end())
			D[i][i + 1] = true;
	}
	for (int i = 0; i < domain.length(); i++) {
		for (int j = 1; j < domain.length(); j++) {
			if (D[i][j]) {
				for (int k = i + 1; k < domain.length(); k++) {
					if (dictionary.find(domain.substr(i + 1, k - (i + 1) + 1)) != dictionary.end())
						D[k][k - (i + 1) + 1] = true;
				}
			}
		}
	}
	unordered_set<string> duplicate;
	vector<string> ans;
	dfs(domain.length() - 1, D, ans, duplicate, domain);
	reverse(ans.begin(), ans.end());
	return ans;
}
void DecomposeIntoDictionaryWordsWrapper(
	TimedExecutor& executor, const string& domain,
	const unordered_set<string>& dictionary, bool decomposable) {
	vector<string> result = executor.Run(
		[&] { return DecomposeIntoDictionaryWords(domain, dictionary); });
	if (!decomposable) {
		if (!result.empty()) {
			throw TestFailure("domain is not decomposable");
		}
		return;
	}

	if (std::any_of(std::begin(result), std::end(result),
		[&](const std::string& s) { return !dictionary.count(s); })) {
		throw TestFailure("Result uses words not in dictionary");
	}

	if (std::accumulate(std::begin(result), std::end(result), string()) !=
		domain) {
		throw TestFailure("Result is not composed into domain");
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "domain", "dictionary",
										 "decomposable" };
	return GenericTestMain(args, "is_string_decomposable_into_words.cc",
		"is_string_decomposable_into_words.tsv",
		&DecomposeIntoDictionaryWordsWrapper,
		DefaultComparator{}, param_names);
}
