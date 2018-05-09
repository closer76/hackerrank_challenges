#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "mylib.h"

using namespace std;
using namespace KennethLo;

vector<string> split_string(string);

/*
 * Complete the valueOfFriendsship function below.
 */
uint64_t valueOfFriendsship(int n, const vector<vector<int>>& friendships) {
    /* Key ideas to "maximize" __total__:
     * 1. Since the value will be accumulated each step, we need to magnify
     *    it as soon as possible.
     * 2. The bigger a circle is, the earlier it should be formed.
     * 3. "Form a circle one-by-one" is better than "form 2 sub-circles, then
     *    join them by connecting one of each".
     */
    vector<int> indices(n);
    vector<list<int>> circles(n, list<int>());

    for (int i = 0; i < n; ++i) {
        indices[i] = i;
        circles[i].push_back(i);
    }

    for (const auto& r : friendships) {
        int s0 = r[0] - 1, s1 = r[1] - 1;
        if (indices[s0] != indices[s1]) {
            int idx_src, idx_dest;
            if (circles[indices[s0]].size() > circles[indices[s1]].size()) {
                idx_src = indices[s1];
                idx_dest = indices[s0];
            } else {
                idx_src = indices[s0];
                idx_dest = indices[s1];
            }
            for (auto i : circles[idx_src]) {
                indices[i] = idx_dest;
            }
            circles[idx_dest].splice(circles[idx_dest].end(), circles[idx_src]);
        }
    }

    vector<uint64_t> counts;
    for (const auto& s : circles) {
        if (s.size() > 1) {
            //cout << s << endl;
            counts.push_back(s.size() - 1);
        }
    }
    sort(counts.begin(), counts.end(), greater<uint64_t>());
    //cout << counts << endl;

    uint64_t result = 0;
    uint64_t prev = 0;
    uint64_t remain = friendships.size();
    for (uint64_t i : counts) {
        //   1*2 + 2*3 + 3*4 + ... + n(n+1)
        // = 1^2 + 2^2 + ... + n^2 + 1 + 2 + ... + n
        // = (n * (n+1) * (2n+1) / 6) + (n * (n+1) / 2)
        // = n * (n+1 * (2n+1) / 3
        result += i * (i + 1) * (i + 2) / 3 + prev * i;
        remain -= i;
        prev += i * (i + 1);
    }
    result += (remain * prev);

    return result;
}

int main()
{
    ios::sync_with_stdio(false);

    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        int m = stoi(nm[1]);

        vector<vector<int>> friendships(m);
        for (int friendships_row_itr = 0; friendships_row_itr < m; friendships_row_itr++) {
            friendships[friendships_row_itr].resize(2);

            for (int friendships_column_itr = 0; friendships_column_itr < 2; friendships_column_itr++) {
                cin >> friendships[friendships_row_itr][friendships_column_itr];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        uint64_t result = valueOfFriendsship(n, friendships);
        cout << result << "\n";
        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
