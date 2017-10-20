"""
Sovling Ema's Supercomputer challange of Hackerrank.
Using brutal-force approach.
"""

#!/usr/local/bin/python3

from copy import deepcopy

def find_largest_plus(grid, pos_x, pos_y):
    """ Finding the largest 'plus' starts from (x, y). """
    if grid[pos_y][pos_x] == 'B':
        return -1

    legs = []
    cur_x = pos_x - 1
    while cur_x >= 0 and grid[pos_y][cur_x] == 'G':
        cur_x -= 1
    legs.append(pos_x - cur_x - 1)

    cur_x = pos_x + 1
    while cur_x < len(grid[0]) and grid[pos_y][cur_x] == 'G':
        cur_x += 1
    legs.append(cur_x - pos_x - 1)

    cur_y = pos_y - 1
    while cur_y >= 0 and grid[cur_y][pos_x] == 'G':
        cur_y -= 1
    legs.append(pos_y - cur_y - 1)

    cur_y = pos_y + 1
    while cur_y < len(grid) and grid[cur_y][pos_x] == 'G':
        cur_y += 1
    legs.append(cur_y - pos_y - 1)

    return min(legs)

def compose_new_grid(grid, pos_x, pos_y, length):
    """ Mark checked computers as 'B' to generate new grid. """
    result = deepcopy(grid)
    result[pos_y][pos_x] = 'B'
    for offset in range(1, length+1):
        result[pos_y+offset][pos_x] = 'B'
        result[pos_y-offset][pos_x] = 'B'
        result[pos_y][pos_x+offset] = 'B'
        result[pos_y][pos_x-offset] = 'B'
    return result

def get_mul(num_a, num_b):
    """ Multiply the number of cells of each plus size. """
    return (num_a * 4 + 1) * (num_b * 4 + 1)

def print_grid(grid):
    """ print grid content to screen """
    for row in grid:
        print(''.join(row))
    print('-'*len(grid[0]))


def main():
    """ main function """
    n, m = list(map(int, input().strip().split()))
    grid = []
    for i in range(n):
        grid.append(list(input().strip()))

    final_result = 0
    for y in range(n):
        for x in range(m):
            leg = find_largest_plus(grid, x, y)
            if leg >= 0:
                for i in range(leg+1):
                    occupied = compose_new_grid(grid, x, y, i)
                    for yy in range(n):
                        for xx in range(m):
                            leg2 = find_largest_plus(occupied, xx, yy)
                            final_result = max(final_result, get_mul(i, leg2))

    print(final_result)

if __name__ == '__main__':
    main()
