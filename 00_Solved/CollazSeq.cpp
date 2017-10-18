#include <iostream>
#include <vector>

using namespace std;

int findCollaz(vector<int>& mem_table, int64_t num) {
    int result = 0;
    if (num >= mem_table.size() || mem_table[num] == 0) {
        if (num % 2 == 0) {
            result = 1 + findCollaz(mem_table, num / 2);
        } else {
            result = 1 + findCollaz(mem_table, 3 * num + 1);
        }

        if (num < mem_table.size()) {
            mem_table[num] = result;
        }
    } else {
        result = mem_table[num];
    }

    return result;
}

vector<int> getCollazSeqLength(int limit) {
    int64_t i;
    auto result = vector<int>(limit * 3, 0);
    result[0] = 0;
    result[1] = 1;
    for (i = 2; i <= limit; i++) {
        findCollaz(result, i);
    }

    int biggest = 1;
    int pos = 1;
    for (i = 2; i <= limit; i++) {
        if (result[i] >= biggest) {
            biggest = result[i];
            pos = i;
        }
        result[i] = pos;
    }

    return result;
}

int main(void) {
    vector<int> table = getCollazSeqLength(5000000);

    int t, n;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        cout << table[n] << endl;
    }
}
