#include <algorithm>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool IsValid(const string &s){
	int n = 0;
	if((s.length()>1 && s[0] == '0') || s.length()>3)
		return false;
	for(int i=0;i<s.length();i++){
		n *= 10;
		n += s[i] - '0';
	}
	return n <= 255 ? true : false;
}

vector<string> GetValidIpAddress(const string& s) {
	vector<string> result;
	for(int i=1;i<4 && i<s.length();i++) {
		string first(s.substr(0, i));
		if(IsValid(first)){
			for(int j=1;j<4 && i+j<s.length();j++){
				string second(s.substr(i, j));
				if(IsValid(second)){
					for(int k=1;k<4 && i+j+k<s.length();k++){
						string third(s.substr(i+j, k));
						if(IsValid(third)){
							string fourth(s.substr(i+j+k));
							if(IsValid(fourth)){
								result.emplace_back(first+'.'+second+'.'+third+'.'+fourth);
							}
						}
					}
				}
			}
		}
	}
	return result;
}
bool comp(vector<string> expected, vector<string> result) {
	std::sort(begin(expected), end(expected));
	std::sort(begin(result), end(result));
	return expected == result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "s" };
	return GenericTestMain(args, "valid_ip_addresses.cc",
		"valid_ip_addresses.tsv", &GetValidIpAddress, &comp,
		param_names);
}
