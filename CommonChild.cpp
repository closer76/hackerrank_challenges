#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//#define MY_DEBUG

int commonChild(const string& s1, const string& s2) {
    vector<vector<int>> mem(s1.length() + 1, vector<int>(s2.length() + 1, 0));

    for (int i = 1; i <= s1.length(); i++) {
        for (int j = 1; j <= s2.length(); j++) {
            mem[i][j] = max(mem[i-1][j-1] + (s1[i-1] == s2[j-1] ? 1 : 0),
                            max(mem[i][j-1], mem[i-1][j]));
        }
    }

#ifdef MY_DEBUG
    for (int i = 0; i <= s1.length(); i++) {
        cout << "[" << mem[i][0];
        for (int j = 1; j <= s2.length(); j++) {
            cout << "," << mem[i][j];
        }
        cout << "]," << endl;
    }
#endif

    return mem[s1.length()][s2.length()];
}


int main() {
    string s1, s2;
    cin >> s1;
    cin >> s2;
    cout << commonChild(s1, s2) << endl;
    return 0;
}
