//#include <bits/stdc++.h>
#include <set>
#include <string>
#include <iostream>

using namespace std;

int maxLen(string s){
    set<char> letter_set;
    
    for (char ch : s) {
        letter_set.insert(ch);
    }
    
    int max_length = 0;
    for (auto itor_a = letter_set.begin(); itor_a != letter_set.end(); ++itor_a) {
#if 1
        auto itor_b = itor_a;
        ++itor_b;
        for ( ; itor_b != letter_set.end(); ++itor_b) {
#else
	for (auto itor_b = itor_a + 1; itor_b != letter_set.end(); ++itor_b) {
#endif
            auto itor_curr = letter_set.end();
            auto itor_expect = letter_set.end();
            int length = 0;
            for (char ch : s) {
                if (ch == *itor_a || ch == *itor_b) {
                    if (itor_curr == letter_set.end()) {
                        itor_curr = (ch == *itor_a) ? itor_a : itor_b;
                        itor_expect = (ch == *itor_a) ? itor_b : itor_a;
                        length = 1;
                    } else if (ch == *itor_expect) {
                        length ++;
                        swap(itor_curr, itor_expect);
                    } else {
                        length = 0;
                        break;
                    }
                }
            }
            max_length = max(max_length, length);
        }
    }
    
    return max_length;
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int result = maxLen(s);
    cout << result << endl;
    return 0;
}

