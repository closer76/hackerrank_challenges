"""
Program to solve Amicable Numbers problem
https://www.hackerrank.com/contests/projecteuler/challenges/euler021
"""

from math import sqrt, floor

def sum_of_proper_divisors(num):
    """ Returns sum of proper divisors of num """
    limit = floor(sqrt(num))
    result = 1
    for divider in range(2, limit + 1):
        if num % divider == 0:
            result += (num // divider)
            if divider != (num // divider):
                result += divider
    return result

CONSTRAINT = 100001

def main():
    """ main function """
    mem_table = [0] * CONSTRAINT
    amicables = []
    for num in range(2, CONSTRAINT):
        mem_table[num] = sum_of_proper_divisors(num)
        if mem_table[num] < CONSTRAINT and mem_table[num] != num:
            if mem_table[mem_table[num]] == 0:
                mem_table[mem_table[num]] = sum_of_proper_divisors(mem_table[num])
            if mem_table[mem_table[num]] == num:
                amicables.append(num)

    print(amicables[:100])
    test_count = int(input().strip())
    for _ in range(test_count):
        limit = int(input().strip())
        result = 0
        for ami_num in amicables:
            if ami_num > limit:
                break
            result += ami_num
        print(result)

if __name__ == '__main__':
    main()
