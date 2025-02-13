#include "Helper.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

bool Helper::startsWithIgnoreCase(const std::string_view& baseString, const std::string_view& prefix)
{
    if (prefix.size() > baseString.size()) return false;

    return std::equal(prefix.begin(), prefix.end(), baseString.begin(),
        [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}

std::string Helper::findLongestPrefix(const std::vector<std::string>& words, const std::string& base)
{
    if (words.empty()) return "";

    std::string longestPrefix = base;

    auto smallestString = findSmallestString(words);

    for (auto i = base.size(); i < smallestString.size(); i++) {
        auto letter = smallestString[i];
        for (auto word : words) {
            auto letterWord = word[i];
            if (letter != letterWord) {
                return longestPrefix;
            }
        }
        longestPrefix += letter;
    }

    return longestPrefix;
}

std::string Helper::findSmallestString(const std::vector<std::string>& words)
{
    if (words.empty()) return "";

    auto smallest = std::min_element(words.begin(), words.end(),
        [](const std::string_view& s1, const std::string_view& s2) {
            return s1.size() < s2.size();
        });

    return *smallest;
}

std::vector<std::string> Helper::splitString(const std::string& str, const char& delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}
