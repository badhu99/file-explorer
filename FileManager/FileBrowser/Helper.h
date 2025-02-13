#pragma once
#include <string_view>
#include <string>
#include <vector>
class Helper
{
public:
	static bool startsWithIgnoreCase(const std::string_view& baseString, const std::string_view& prefix);

	static std::string findLongestPrefix(const std::vector<std::string>& words, const std::string& base);
	static std::string findSmallestString(const std::vector<std::string>& words);
	static std::vector<std::string> splitString(const std::string& str, const char& delimiter);
};
