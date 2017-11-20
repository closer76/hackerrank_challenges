#ifndef __MY_LIB_H__
#define __MY_LIB_H__

#include <iostream>
#include <vector>

namespace KennethLo {

    /**
     * \fn ostream& operator<<(ostream& os, const vector<T>& v)
     * \brief Helper operator to output contents of a std::vector.
     **/
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
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

    /**
     * Find all primes in a given boundary using Sieve of Eratosthenes 
     * algorithm.
     * 
     * @param is_prime A vector records whether index i is a prime or not.
     **/
    void seive_for_primes(std::vector<int>& is_prime);

    /**
     * A function to calculate p-th power of an integer, with mod function.
     * 
     * @param base Base integer.
     * @param p Power factor.
     * @param mod The answer will be modulo by mod before returned.
     */
    int power_mod(int base, int p, int mod);
};

#endif