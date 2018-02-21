#include <iostream>
#include <string>

#define MAXSIZE 30
using namespace std;

void GetNext(string t, int next[])
{
    int j = 0, k = -1;
    next[0] = -1;
    while (j < t.size() - 1) {
        if (k == -1 || t[j] == t[k]) {
            ++j, ++k;
            next[j] = k;
        }
        else
            k = next[k];
    }
}

void GetNextVal(string t, int nextval[])
{
    int j = 0, k = -1;
    nextval[0] = -1;
    while (j < t.size()) {
        if (k == -1 || t[j] == t[k]) {
            ++k, ++j;
            if (t[j] != t[k])
                nextval[j] = k;
            else
                nextval[j] = nextval[k];
        }
        else
            k = nextval[k];
    }
}

int KMPIndex(string s, string t)
{
    int next[MAXSIZE], i = 0, j = 0;
    GetNext(t, next);
    int tsz = t.size();
    while (i < s.size() && j < tsz) {
        if (j == -1 || s[i] == t[j]) {
            ++i;
            ++j;
            if (s[i] == t[j])
                cout << s[i] << " - " << t[j] << endl;
            if (j == -1)
                cout << "oop" << endl;
        }
        else
            j = next[j];
    }
    if (j == t.size())
        return i - t.size();
    return -1;
}
