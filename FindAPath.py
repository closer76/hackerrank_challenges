#!/usr/local/bin/python3

#from collections import deque
import time

def find_shortest_path(start, end, w_table):
    row = len(w_table)
    col = len(w_table[0])
    values = [[-1 for y in range(col)] for x in range(row)]
    decided = [[False for y in range(col)] for x in range(row)]

    curr = start
    values[start[0]][start[1]] = w_table[start[0]][start[1]]
    candidates = set([])
    while True:
        if curr == end:
            break

        decided[curr[0]][curr[1]] = True

        # update values
        def update_weight(x, y):
            if 0 <= x < row and 0 <= y < col and not decided[x][y]:
                w = values[curr[0]][curr[1]] + w_table[x][y]
                if values[x][y] == -1 or values[x][y] > w:
                    values[x][y] = w
                candidates.add((x, y))

        update_weight(curr[0], curr[1] - 1)
        update_weight(curr[0], curr[1] + 1)
        update_weight(curr[0] - 1, curr[1])
        update_weight(curr[0] + 1, curr[1])

        # pick-up the next node
        next_node = None
        min_value = values[curr[0]][curr[1]] + 3001
        for node in candidates:
            if values[node[0]][node[1]] < min_value:
                next_node = node
                min_value = values[node[0]][node[1]]

        if not next_node:
            break

        curr = next_node
        candidates.remove(next_node)
        #print(candidates)

    #print(values)
    return values[end[0]][end[1]]


start_time = time.time()

weight_table = []

ROW, COL = list(map(int, input().strip().split()))
for r in range(ROW):
    weight_table.append(list(map(int, input().strip().split())))

Q_NUM = int(input().strip())
for i in range(Q_NUM):
    start_x, start_y, end_x, end_y = list(map(int, input().strip().split()))
    print(find_shortest_path((start_x, start_y), (end_x, end_y), weight_table))

print("--- %s seconds ---" % (time.time() - start_time))
