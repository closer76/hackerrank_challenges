#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << '[';
    size_t i = 0;
    for (auto itor = v.begin(); itor != v.end(); itor++)
    {
        os << setw(5) << *itor;
        if (++i != v.size())
        {
            os << ',';
        }
    }
    os << ']';

    return os;
}

vector<int> process_row(const vector<int>& accu, const vector<int>& row)
{
    vector<int> result(accu.size(), 0);
    for(int i = 0; i < accu.size(); i++)
    {
        int sum = 0;
        int max_left = 0, max_right = 0;
        int j;
        for (j = i - 1; j >= 0; j--)
        {
            sum += row[j];
            max_left = max(max_left, sum);
        }
        sum = 0;
        for (j = i + 1; j < accu.size(); j++)
        {
            sum += row[j];
            max_right = max(max_right, sum);
        }
        result[i] = max_left + max_right + accu[i] + row[i];
    }
    
    return result;
}

int main() {
    int n = 10, m = 10;
    //cin >> n >> m;
    vector<int> accu(m, 0);
    
    // random
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rand_num(-250, 250);

    for (int i = 0; i < n; i++)
    {
        vector<int> row(m);
        for (int j = 0; j < m; j++)
        {
            //cin >> row[j];
            //row[j] = rand_num(gen);
            if (i == j)
            {
                row[j] = -250;
            }
            else
            {
                row[j] = ((i ^ j) & 1) ? 0 : 1;
            }
        }
        accu = process_row(accu, row);
        cout << row << string(5, ' ') << accu << endl;
    }
    
    cout << *(max_element(accu.begin(), accu.end())) << endl;
    
    return 0;
}
