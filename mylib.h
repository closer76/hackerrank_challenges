#ifndef __MY_LIB_H__
#define __MY_LIB_H__

#include <iostream>
#include <vector>

namespace KennethLo {

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

    void seive_for_primes(std::vector<int>& is_prime);

};

#endif