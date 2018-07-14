#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s) {
	int st = 0;
	string &cur = *s;
	std::reverse(cur.begin(), cur.end());
	for (int i = 0; i < s->length(); i++) {
		if (cur[i] == ' ') {
			for (int j = st; j < (st + i) / 2; j++) {
				std::swap(cur[j], cur[i-1-(j-st)]);
			}
			st = i + 1;
		}
	}
	for (int j = st; j < (st + s->length()) / 2; j++) {
		std::swap(cur[j], cur[s->length() - 1 - (j - st)]);
	}
	return;
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
	string s_copy = s;

	executor.Run([&] { ReverseWords(&s_copy); });

	return s_copy;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "s" };
	return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
		&ReverseWordsWrapper, DefaultComparator{},
		param_names);
}
