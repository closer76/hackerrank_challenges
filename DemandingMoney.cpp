#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>

#include "mylib.h"

using namespace std;
using namespace KennethLo;

vector<string> split_string(string);

/*
 * Complete the demandingMoney function below.
 */
class DemandingMoneyCalculator {
    vector<int> m_money;
    vector<bitset<64>> m_graph;
    int m_maxMoney;
    int m_count;
    // vector<bitset<64>> m_rec;

public:
    DemandingMoneyCalculator(const vector<int>& money, const vector<vector<int>>& roads)
        : m_money(money)
        , m_graph(money.size() + 1)
        , m_maxMoney(0)
        , m_count(0)
        // , m_rec(0)
    {
        for (const auto& r : roads) {
            m_graph[r[0]].set(r[1]);
            m_graph[r[1]].set(r[0]);;
        }
    }

    vector<int> execute() {
        bitset<64> remains;
        for (int i = 1; i <= m_money.size(); ++i) {
            remains.set(i);
        }
        m_calc2(1, remains, bitset<64>(0), 0);
        //cout << "Result = " << m_rec << endl;
        return vector<int> {m_maxMoney, m_count};
    }

private:
    void m_calc2(int index, bitset<64> remains, bitset<64> selected, int collected) {
        // cout << "idx=" << index
        //      << ";r=" << remains
        //      << ";s=" << selected
        //      << ";c=" << collected << endl;
        if (remains.none() || index > m_money.size()) {
            if (collected > m_maxMoney) {
                m_maxMoney = collected;
                m_count = 1;
                // m_rec.clear();
                // m_rec.push_back(selected);
            } else if (collected == m_maxMoney) {
                m_count ++;
                // m_rec.push_back(selected);
            }
        } else {
            // process "not selected" first
            m_calc2(index + 1, remains, selected, collected);
            if (remains.test(index)) {
                remains.reset(index);
                selected.set(index);
                collected += m_money[index - 1];
                remains.reset(index);
                remains &= ~m_graph[index];
                // cout << remains << endl;
                m_calc2(index + 1, remains, selected, collected);
            }
        }
    }
};

vector<int> demandingMoney(const vector<int>& money, const vector<vector<int>>& roads) {
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

    vector<int> result = demandingMoney(money, roads);

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
