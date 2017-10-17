def findCollaz(mem_table, num):
    result = 0
    if num >= len(mem_table) or mem_table[num] == 0:
        if num % 2 == 0:
            result = 1 + findCollaz(mem_table, num // 2)
        else:
            result = 1 + findCollaz(mem_table, 3 * num + 1)
        if num < len(mem_table):
            mem_table[num] = result
    else:
        result = mem_table[num]

    return result
        
def getCollazSeqLength(limit):
    result = [0 for _ in range(limit * 3)]
    result[0] = 0
    result[1] = 1
    for i in range(2,limit+1):
        findCollaz(result, i)

    count = 0
    for i in range(limit, limit * 2):
        if result[i] != 0:
            count += 1
    print('Under ', limit * 2, ': ', count)
    count = 0
    biggest = limit * 2
    for i in range(limit * 2, limit * 3):
        if result[i] != 0:
            count += 1
            biggest = i
    print('Under ', limit * 3, ': ', count, '; biggest = ', biggest)

    biggest = 1
    pos = 1
    for i in range(2,limit+1):
        if result[i] >= biggest:
            biggest = result[i]
            pos = i
        result[i] = pos

    return result

table = getCollazSeqLength(5000000)

t = int(input().strip())
for i in range(t):
    n = int(input().strip())
    print(table[n])
