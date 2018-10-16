#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score,
	const vector<int>& individual_play_scores) {
	vector<int> D(final_score + 1, 0);
	D[0] = 1; 
	for (int j : individual_play_scores) {
		for (int i = 0; i < final_score; i++) {
			if (D[i] == 0)
				continue;
			if (i + j <= final_score)
				D[i + j] += D[i];
		}
	}
	return D[final_score];
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "final_score", "individual_play_scores" };
	return GenericTestMain(args, "number_of_score_combinations.cc",
		"number_of_score_combinations.tsv",
		&NumCombinationsForFinalScore, DefaultComparator{},
		param_names);
}
