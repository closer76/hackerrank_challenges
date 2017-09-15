#!/usr/local/bin/python3

import sys

def checkAnagram(s1, s2):
    mem = [0] * 26
    for c in s1:
        mem[ord(c) - ord('a')] += 1
    for c in s2:
        mem[ord(c) - ord('a')] -= 1
    for i in mem:
        if i != 0:
            return False
    return True

def sherlockAndAnagrams(s):
    result = 0
    for length in range(1, len(s)):
        for start in range(0, len(s) - length):
            for end in range(start + 1, len(s) - length + 1):
                if checkAnagram(s[start:(start+length)], s[end:(end+length)]):
                    result += 1
    return result

q = int(input().strip())
for a0 in range(q):
    s = input().strip()
    result = sherlockAndAnagrams(s)
    print(result)