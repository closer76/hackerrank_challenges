def transist(grid):
    r = len(grid)
    c = len(grid[0])
    result = [['O' for _ in row] for row in grid]
    for x in range(r):
        for y in range(c):
            if grid[x][y] == 'O' or \
               (x > 0 and grid[x-1][y] == 'O') or \
               (y > 0 and grid[x][y-1] == 'O') or \
               (x < r - 1 and grid[x+1][y] == 'O' or \
               (y < c - 1 and grid[x][y+1] == 'O')):
                result[x][y] = '.'
    return result

def getGrid(grid, sec):
    if sec == 1:
        return grid
    elif sec % 2 == 0:
        return [['O' for _ in row] for row in grid]
    else:
        grid_a = transist(grid)
        grid_b = transist(grid_a)
        if (sec // 2 % 2 == 1):
            return grid_a
        else:
            return grid_b


r, c, sec = list(map(int, input().strip().split()))
grid = []
for i in range(r):
    s = input().strip()
    grid.append([c for c in s])

for row in getGrid(grid, sec):
    print(''.join(row))
