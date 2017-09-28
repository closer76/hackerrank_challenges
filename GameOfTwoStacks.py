#!/bin/python3

#import sys

def dbg_print(*objects):
    DBG = False
    #DBG = True
    if DBG:
        print(*objects)

def processStacks(a, b, x):
    #print(a)

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
        dbg_print('  sum=%d, b[-1]=%d' % (popped_sum, b[-1]))
        popped_sum += b.pop()
        popped_count += 1

    dbg_print('  count = ', popped_count)

    while b and popped_a:
        dbg_print('  popped_a=' + str(popped_a))
        dbg_print('  b       =' + str(b[-10:]))
        dbg_print('  sum     =' + str(popped_sum))

        sum_a = 0
        sum_b = 0
        while b and popped_a:
            sum_a += popped_a.pop()
            sum_b += b.pop()
            if b and sum_b + b[-1] <= sum_a + (x - popped_sum):
                dbg_print('  sum_b = ', sum_b, ', b.top() = ', b[-1])
                dbg_print('  sum_a = ', sum_a, '; x - popped_sum = ', x - popped_sum)
                popped_sum = popped_sum - sum_a + sum_b
                while b and popped_sum + b[-1] <= x:
                    dbg_print('  sum=%d, b[-1]=%d' % (popped_sum, b[-1]))
                    popped_sum += b.pop()
                    popped_count += 1
                dbg_print('  count = ', popped_count)
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

