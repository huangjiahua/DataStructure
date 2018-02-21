#include <iostream>
#include "kmp.h"

int main(int argc, char const *argv[]) {
    string s("caaaabskjdfhakaaaaabsdfhakjs");
    string t("abcabaa");
    int nv[30];
    GetNextVal(t, nv);
    for (int i = 0; i < t.size(); ++i)
        cout << nv[i] << " ";
    cout << endl;
    cout << KMPIndex(s, t) << endl;
}
