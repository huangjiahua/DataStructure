#include <fstream>
#include <random>
#include <ctime>

using namespace std;

int main()
{
    char s[] = "ATCG";
    default_random_engine e(time(0));
    uniform_int_distribution<unsigned> u(0, 3);
    ofstream out("dna.txt");
    for (int i = 1; i <= 1000000; ++i) {
        out << s[u(e)];
        if (i % 80 == 0)
            out << endl;
    }
}
