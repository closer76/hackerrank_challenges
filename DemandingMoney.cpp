#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "mylib.h"

using namespace std;
using namespace KennethLo;

vector<string> split_string(string);

string format_flags(uint64_t flags, int count) {
    string result("");
    for (int i = 0; i < count; i++) {
        result.push_back((flags & (static_cast<uint64_t>(1)<<i)) ? '1' : '0');
    }

    return result;
}

uint64_t flag_set(uint64_t flags, int index) {
    return flags | (static_cast<uint64_t>(1) << index);
}

uint64_t flag_reset(uint64_t flags, int index) {
    return flags & ~((static_cast<uint64_t>(1) << index));
}

bool flag_test(uint64_t flags, int index) {
    return (0 != (flags & (static_cast<uint64_t>(1) << index)));
}

/*
 * Complete the demandingMoney function below.
 */
class DemandingMoneyCalculator {
    vector<int> m_money;
    vector<uint64_t> m_graph;
    map<uint64_t, pair<uint64_t, uint64_t>> m_mem;
    int m_indent;   // For debug

public:
    DemandingMoneyCalculator(const vector<int>& money, const vector<vector<int>>& roads)
        : m_money(money)
        , m_graph(money.size() + 1, 0)
        , m_mem()
        , m_indent(0)
    {
        for (const auto& r : roads) {
            m_graph[r[0]] = flag_set(m_graph[r[0]], r[1]);
            m_graph[r[1]] = flag_set(m_graph[r[1]], r[0]);
        }
    }

    vector<uint64_t> execute() {
        // Literal integer will be 32-bit only, so we need to cast to
        // 64-bit type first.
        uint64_t remains = (static_cast<uint64_t>(1) << (m_money.size() + 1)) - 2;
        auto result = m_calc3(1, remains);

        return vector<uint64_t> {result.first, result.second};
    }

private:
    pair<uint64_t,uint64_t> m_calc3(int index, uint64_t remains) {
#ifdef DEBUG_OUTPUT
        m_indent += 2;
        cout << string(m_indent, ' ')
             << "Index = " << index
             << ", remains = " << format_flags(remains, m_money.size() + 1) << endl;
#endif
        pair<uint64_t, uint64_t> result {0, 1};
        if (!remains) {
            result = {0, 1};
        } else if (!flag_test(remains, index)){
            result = m_calc3(index + 1, remains);
        } else {
            remains = flag_reset(remains, index);
#ifdef DEBUG_OUTPUT
            cout << string(m_indent, ' ')
                 << "skip: " << format_flags(remains, m_money.size() + 1) << endl;
#endif
            if (m_mem.find(remains) == m_mem.end()) {
                m_mem[remains] = m_calc3(index + 1, remains);
            }
            auto skip = m_mem[remains];
            remains &= ~m_graph[index];
#ifdef DEBUG_OUTPUT
            cout << string(m_indent, ' ')
                 << "take: " << format_flags(remains, m_money.size() + 1) << endl;
#endif
            if (m_mem.find(remains) == m_mem.end()) {
                m_mem[remains] = m_calc3(index + 1, remains);
            }
            auto take = m_mem[remains];
            take.first += m_money[index - 1];

#ifdef DEBUG_OUTPUT
            cout << string(m_indent, ' ');
            cout << "skip[" << skip.first << "," << skip.second << "]\n";
            cout << string(m_indent, ' ');
            cout << "take[" << take.first << "," << take.second << "]\n";
#endif

            if (take.first > skip.first) {
                result = take;
            } else if (take.first == skip.first) {
                take.second += skip.second;
                result = take;
            } else {
                result = skip;
            }
        }

#ifdef DEBUG_OUTPUT
        m_indent -= 2;
#endif

        return result;
    }
};

vector<uint64_t> demandingMoney(const vector<int>& money, const vector<vector<int>>& roads) {
    DemandingMoneyCalculator calculator(money, roads);
    return calculator.execute();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    string money_temp_temp;
    getline(cin, money_temp_temp);

    vector<string> money_temp = split_string(money_temp_temp);

    vector<int> money(n);

    for (int money_itr = 0; money_itr < n; money_itr++) {
        int money_item = stoi(money_temp[money_itr]);

        money[money_itr] = money_item;
    }

    vector<vector<int>> roads(m);
    for (int roads_row_itr = 0; roads_row_itr < m; roads_row_itr++) {
        roads[roads_row_itr].resize(2);

        for (int roads_column_itr = 0; roads_column_itr < 2; roads_column_itr++) {
            cin >> roads[roads_row_itr][roads_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // The result might exceed the limit of 32-bit integer, so use uint64_t
    // instead. (Test case #48 will fail due to this reason.)
    vector<uint64_t> result = demandingMoney(money, roads);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

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
