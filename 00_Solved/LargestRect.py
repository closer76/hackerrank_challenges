#!/usr/local/bin/python3

import sys

def largestRectangle(h):
    # Complete this function
    m = []
    max_height = 0
    for b in h:
        if not m or b > m[-1][0]:
            m.append((b, 1))
            #print(m)
        elif b == m[-1][0]:
            v, w = m.pop()
            m.append((v, w + 1))
            #print(m)
        elif b < m[-1][0]:
            while m and b < m[-1][0]:
                v0, w0 = m.pop()
                #print(v0, '*', w0, '=', v0 * w0, ' vs ', max_height)
                max_height = max(max_height, v0 * w0)
                if m and b < m[-1][0]:
                    v1, w1 = m.pop()
                    m.append((v1, w0 + w1))
                    #print(m)
            if m and b == m[-1][0]:
                v, w = m.pop()
                m.append((v, w + 1))
            else:
                m.append((b, w0 + 1))
            #print(m)

    width = 0
    while m:
        v, w = m.pop()
        width += w
        #print(v, '*', width, '=', v * width, ' vs ', max_height)
        max_height = max(max_height, v * width)


    return max_height

# This algorithm is from Hackerrank's editorial...
# Since the height of each index can be accessed from h[index],
# our stack needs indices only.
def largestRectangle_ref(h):
    stack = [0]
    result = 0
    i = 1
    while i < len(h):
        if not stack or h[i] > h[stack[-1]]:
            stack.append(i)
            i += 1
            #print([h[i] for i in stack])
        else:
            while stack and h[i] < h[stack[-1]]:
                old_i = stack.pop()
                result = max(result, h[old_i] * ((i - stack[-1] - 1) if stack else i))
            #print([h[i] for i in stack])
    return result

if __name__ == "__main__":
    n = int(input().strip())
    h = list(map(int, input().strip().split(' ')))
    result = largestRectangle_ref(h)
    print(result)

