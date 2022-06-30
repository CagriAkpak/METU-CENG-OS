#include <vector>
#include <string>
#include "stringTokenizer.h"

std::vector<std::string> tokenizeStringPath(std::string p){
	int pos = -1;
	std::vector<std::string> v;
	while((pos = p.find('/'))!=-1){
		std::string dir = p.substr(0, pos);
		v.push_back(dir);
		p = p.substr(pos+1);
	};

	//* uncomment if you want to have / for paths starting from root. Currently it is ""(empty string) instead of "/"
	// if(v.size()){
	// 	if(v[0] == ""){
	// 		v[0]="/";
	// 	}
	// }

	if(p.size()){
		v.push_back(p);
	}

	return v;
}