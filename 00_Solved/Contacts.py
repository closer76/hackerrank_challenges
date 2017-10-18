#!/usr/local/python3

# Trie, with cached children count
# Use iteration instead of recursion in 'add'

class Node:
    def __init__(self):
        self.children_count = 0
        self.children = {}

class Contacts:
    def __init__(self):
        self.db = Node()
    
    def _add_body(self, name, root):
        curr = root
        curr.children_count += 1
        while len(name) > 0:
            if name[0] not in curr.children:
                curr.children[name[0]] = Node()
            curr = curr.children[name[0]]
            name = name[1:]
            
            curr.children_count += 1

    def add(self, name):
        self._add_body(name, self.db)

    def _find_body(self, name, root):
        curr = root
        while len(name) > 0:
            if name[0] in curr.children:
                curr = curr.children[name[0]]
                name = name[1:]
                if len(name) == 0:
                    return curr.children_count
            else:
                return 0

    def find(self, name):
        return self._find_body(name, self.db)

s = input().strip()
n = int(s)
app = Contacts()
for a0 in range(n):
    op, contact = input().strip().split(' ')
    if op == 'add':
        app.add(contact)
    elif op == 'find':
        print(app.find(contact))

