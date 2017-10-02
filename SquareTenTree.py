from math import log, ceil

L = input().strip()
R = input().strip()

if len(L) == len(R):
    i = 0
    while L[i] == R[i]:
        i += 1
    if i:
        L = L[i:]
        R = R[i:]
if len(R) > 1:
    tailing_0_count = 2 ** (ceil(log(len(R), 2)) - 1)
    top = R[:tailing_0_count] + '0' * tailing_0_count
else:
    top = R[:]
ans = []
i = 0
carry = 0
#while len(R) > 2 ** i:
for i in range(ceil(log(len(R), 2)) + 1):
    #print('i=%d' % (i))
    if i == 0:
        num = int(L[-1])
        #print('num=%d' % (num))
        if num:
            ans.append((0, 10 - num + 1))
            carry = 1
        else:
            carry = 0
    else:
        x = -(2**(i))
        y = -(2**(i-1))
        num = (0 if L[x:y] == '' else int(L[x:y])) + carry
        #print('num=%d' % (num))
        print(top[x:y])
        if num:
            ans.append((i, (10 ** (2**(i-1)) if int(top[x:y]) == 0 else int(top[x:y])) - num))
            carry = 1
        else:
            carry = 0

    i += 1

for i in range(ceil(log(len(R), 2)) - 1, -1, -1):
    x = -(2**(i))
    y = -(2**(i-1))
    #print('[%d,%d]' % (x, y))
    num = (int(R[x]) if x == -1 else int(R[x:y]))
    #print('num=%d' % (num))
    if num:
        ans.append((i, num))
print(len(ans))
for pair in ans:
    print('%d %d' % pair)
