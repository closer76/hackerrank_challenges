#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// My own algorithm. Not too bad though.
void calcPrimes(vector<int>& m)
{
    m[0] = 2;
    int count = 1;

    for (int i = 3; ; i++) {
        bool is_prime = true;
        for (int j = 0; j < count && m[j] * m[j] <= i; j++) {
            if (i % m[j] == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            m[count] = i;
            count++;

            if (count >= m.size()) {
                break;
            }
        }
    }
}

// Use sieve of Eratosthenes. Over 50% faster than my algorithm.
void calcPrimes_sieve(vector<int>& m) {
    const int limit = 1300000;
    const int sqrt_limit = sqrt(limit);
    int i, j;

    vector<int> sieve(limit, true);
    for (i = 2; i <= sqrt_limit; i++) {
        if (sieve[i] == false) continue;

        for (j = i * i; j < limit; j += i) {
            sieve[j] = false;
        }
    }

    int count = 0;
    for (i = 2; i < limit && count < m.size(); i++) {
        if (sieve[i] == true) {
            m[count++] = i;
        }
    }
}

int main(void) {
    int count;

    vector<int> m(100000);
    calcPrimes_sieve(m);
    //calcPrimes(m);

    cin >> count;
    for (int i = 0; i < count; i++)
    {
        int n;
        cin >> n;
        cout << m[n-1] << endl;
    }
    return 0;
}
