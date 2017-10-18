#!/bin/python3

#import sys

def processStacks(a, b, x):
    a.reverse()
    b.reverse()

    popped_sum = 0
    popped_count = 0
    popped_a = []

    while a and popped_sum + a[-1] <= x:
        popped_a.append(a.pop())
        popped_sum += popped_a[-1]
        popped_count += 1

    while b and popped_sum + b[-1] <= x:
        popped_sum += b.pop()
        popped_count += 1

    while b and popped_a:
        sum_a = 0
        sum_b = 0
        while b and popped_a:
            sum_a += popped_a.pop()
            sum_b += b.pop()
            if b and sum_b + b[-1] <= sum_a + (x - popped_sum):
                popped_sum = popped_sum - sum_a + sum_b
                while b and popped_sum + b[-1] <= x:
                    popped_sum += b.pop()
                    popped_count += 1
                break

    return popped_count

g = int(input().strip())
for a0 in range(g):
    n, m, x = input().strip().split(' ')
    n, m, x = [int(n), int(m), int(x)]
    a = list(map(int, input().strip().split(' ')))
    b = list(map(int, input().strip().split(' ')))
    # your code goes here
    print(processStacks(a, b, x))

