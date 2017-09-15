#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool checkAnagram(const string& str, int start, int end, int count) {
    vector<int> mem(26, 0);

    for (int i = 0; i < count; i++) {
        mem[str[start+i] - 'a'] += 1;
        mem[str[end+i] - 'a'] -= 1;
    }

    for (auto i : mem) {
        if (i != 0) {
            return false;
        }
    }

    return true;
}

int sherlockAndAnagrams(const string& s) {
    int result = 0;
    for (int length = 1; length < s.length(); length++) {
        for (int start = 0; start < s.length() - length; start++) {
            for (int end = start + 1; end < s.length() - length + 1; end++) {
                if (checkAnagram(s, start, end, length)) {
                    result += 1;
                }
            }
        }
    }

    return result;
}

int main(void) {
    int n;
    cin >> n;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        cout << sherlockAndAnagrams(s) << endl;
    }
}
