#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace KennethLo {

    template <typename T>
    ostream& operator<<(ostream& os, const vector<T>& v)
    {
        os << '[';
        size_t i = 0;
        for (auto itor = v.begin(); itor != v.end(); itor++)
        {
            os << *itor;
            if (++i != v.size())
            {
                os << ',';
            }
        }
        os << ']';

        return os;
    }

    void seive_for_primes(vector<int>& is_prime) {
        int test_limit = ceil(sqrt(is_prime.size()));
        is_prime[0] = 0;
        is_prime[1] = 0;
        for (int i = 2; i <= test_limit; i++) {
            if (is_prime[i]) {
                for (int j = i * i; j < is_prime.size(); j += i) {
                    is_prime[j] = 0;
                }
            }
        }
    }
}
