#!usr/local/bin/python3

import sys


n = int(input().strip())
scores = [int(scores_temp) for scores_temp in input().strip().split(' ')]
m = int(input().strip())
alice = [int(alice_temp) for alice_temp in input().strip().split(' ')]
# your code goes here

leaderboard = [scores[0]]
now = scores[0]
for s in scores[1:]:
    if s != now:
        leaderboard.append(s)
        now = s

pos = len(leaderboard) - 1
for a in alice:
    # do binary search
    begin = 0
    end = pos + 1
    pos = (begin + end) // 2
    print ("a=%d,b=%d,e=%d,p=%d" % (a, begin, end, pos))
    while True:
        print ('---p=%d,a=%d,lb[p]=%d:%d:%d'%(pos,a,leaderboard[pos-1],leaderboard[pos],leaderboard[pos+1]))
        if a == leaderboard[pos]:
            break
        elif a > leaderboard[pos]:
            if pos == 0 or a < leaderboard[pos-1]:
                break
            end = pos
        else: # a < leaderboard[pos]
            if pos == len(leaderboard) - 1 or a > leaderboard[pos+1]:
                pos += 1
                break
            begin = pos
        pos = (begin + end) // 2
    print(pos + 1)
            
                
            
                
    

