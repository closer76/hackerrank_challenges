# Enter your code here. Read input from STDIN. Print output to STDOUT
def get_result(grid1, grid2, r1, r2, c1, c2):
    for p in range(r1 - r2 + 1):
        for q in range(c1 - c2 + 1):
            for r in range(r2):
                if grid2[r] != grid1[p+r][q:(q+c2)]:
                    break
                else:
                    print("p,q,r=", p, q, r, ":", grid2[r], ":", grid1[p+r][q:(q+c2)])
                    if r == (r2 - 1):
                        return "YES"
    return "NO"

n = int(input().strip())
for i in range(n):
    (r1, c1) = list(map(int, input().strip().split()))
    grid1 = []
    for j in range(r1):
        grid1.append(input().strip())
    (r2, c2) = list(map(int, input().strip().split()))
    grid2 = []
    for j in range(r2):
        grid2.append(input().strip())

    print(get_result(grid1, grid2, r1, r2, c1, c2))
    

