#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;
vector<string> PhoneMnemonic(const string& phone_number) {
	vector <string> ans(1, ""), dict = { "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ" };
	for (int i = 0; i < phone_number.length(); i++) {
		vector<string> temp;
		if (phone_number[i] < '2') {
			for (int j = 0; j < ans.size(); j++)
				ans[j] += phone_number[i];
			continue;
		}
		string cur = dict[phone_number[i] - '2'];
		for (int j = 0; j < cur.length(); j++) 
			temp.insert(std::end(temp), std::begin(ans), std::end(ans));
		int pos = 0;
		for (int j = 0; j < cur.length(); j++) 
			for (int k = 0; k < ans.size(); k++) 
				temp[pos++] += cur[j];

		ans.swap(temp);
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "phone_number" };
	return GenericTestMain(args, "phone_number_mnemonic.cc",
		"phone_number_mnemonic.tsv", &PhoneMnemonic,
		&UnorderedComparator<std::vector<std::string>>,
		param_names);
}
