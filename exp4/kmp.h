#ifndef _kmp_h_
#define _kmp_h_
#include <string>
#include <vector>
#include <iostream>

class PatternString {
    using string = std::string;
    friend int findSubString(const string& target, const PatternString &p);
private:
    string pattern;
    std::vector<int> next;
public:
    PatternString(const string str);
    int size() const { return pattern.size(); }
};

PatternString::PatternString(const string str): pattern(str), next(str.size())
{
    if (str.size() < 1)
        return ;
    next[0] = -1;
    if (str.size() < 2)
        return ;
    next[1] = 0;
    if (str.size() < 3)
        return ;
    int i = 1, j = 1;
    while (i != pattern.size()) {
        j = next[i];
        while (j != -1) {
            if (pattern[i] == pattern[j])
                break;
            j = next[j];
        }
        next[++i] = j + 1;
    }

    for (i = 1; i != pattern.size(); ++i) {
        j = next[i];
        while (j != -1 && pattern[i] == pattern[j])
            j = next[j];
        next[i] = j;
    }
}


int findSubString(const std::string& t, const PatternString& p)
{
    int sz = t.size() - p.size() + 1;
    if (sz < 1)
        return -1;
    int i = 0, j = -1;
    for ( ; i < sz; ++i) {
        ++j;
        while (j != -1) {
            while (t[i] == p.pattern[j]) {
                ++i;
                ++j;
                if (j == p.size())
                    return i - j;
                if (i + p.size() > t.size())
                    return -1;
            }
            j = p.next[j];
        }
    }
    return -1;
}




#endif
