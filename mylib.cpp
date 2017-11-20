#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace KennethLo {
    /**
     * Find all primes in a given boundary using Sieve of Eratosthenes 
     * algorithm.
     * 
     * @param is_prime A vector records whether index i is a prime or not.
     **/
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

    /**
     * A function to calculate p-th power of an integer, with mod function.
     * 
     * @param base Base integer.
     * @param p Power factor.
     * @param mod The answer will be modulo by mod before returned.
     */
    int power_mod(int base, int p, int mod)
    {
        long long result = 1;
        long long tmp = base % mod;

        while(p)
        {
            if (p & 1) {
                result = (result * tmp) % mod;
            }
            p >>= 1;
            tmp = (tmp * tmp) % mod;
        }

        return (int)(result % mod);
    }
}
