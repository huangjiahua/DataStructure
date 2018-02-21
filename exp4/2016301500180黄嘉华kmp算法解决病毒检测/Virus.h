#ifndef _Virus_h_
#define _Virus_h_
#include "kmp.h"
#include <string>

class Virus {
private:
    std::string DNA;
    std::size_t org_sz;
public:
    Virus(const std::string& s): DNA(s), org_sz(DNA.size()) { DNA += DNA; }
    Virus(const std::string&& s): DNA(s), org_sz(DNA.size()) { DNA += DNA; }
    std::size_t size() const { return org_sz; }
    const PatternString pattern(std::size_t i) const {
        return PatternString(DNA.substr(i, org_sz));
    }
    const std::string subString(std::size_t i) const {
        return DNA.substr(i, org_sz);
    }

};


#endif
