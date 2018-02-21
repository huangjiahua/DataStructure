#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char const *argv[]) {
    std::string str;
    std::ostringstream os;
    os << "good";
    str = os.str();
    std::cout  << str;
}
