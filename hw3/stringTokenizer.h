#ifndef HW3_STRTOKENIZER_H
#define HW3_STRTOKENIZER_H
#include <vector>
#include <string>

/**
 * Converts the path 'p' into tokenized set of strings. p needs to be a path string, e.g. "/home/a/b/c.txt".
 * 
 * Returns: vector<string>
 * 
 * You also have the option to get "/" as the root element, instead of an empty string "". Check the .cpp file for that.
 */
std::vector<std::string> tokenizeStringPath(std::string p);

#endif //HW3_STRTOKENIZER_H