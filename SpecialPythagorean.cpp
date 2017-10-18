#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solve_order_n_square(int n) {
    int a, b, c;
    int result = -1;
    for (c = 5; c <= n / 2; c++) {
        for (a = 3; a <= (n - c) / 2; a++) {
            b = n - a - c;
            if (a * a + b * b == c * c) {
                result = max(result, a * b * c);
            }
        }
    }

    return result;
}

int solve_order_n(int n) {
    int a, b, c;
    int result = -1;

    // By using these equations:
    //     a^2 + b^2 = c^2
    //     a + b + c = n
    // , we can make 'b' a function of 'a' and 'n', and then 'c' can be
    // evaluated easily:
    //     b = (n^2 - 2na) / (2n - 2a)
    //     c = n - a - b
    // These (a,b,c) fullfill "a^2 + b^2 = c^2", so all we have to do now
    // is to check if 'b' (and 'c') is integer or not.
    //
    for (a = 1; a < n / 3; a++) {
        if ((n*n - 2*n*a) % (2*n - 2*a) == 0) {  // check if 'b' is integer
            b = (n*n - 2*n*a) / (2*n - 2*a);
            c = n - a - b;
    
            result = max(result, a * b * c);
        }
    }

    return result;
}

int main() {
    int count;
    cin >> count;
    for (int i = 0; i < count; i++) {
        int value;
        cin >> value;
        cout << solve_order_n(value) << endl;
    }
    return 0;
}

