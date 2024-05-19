# ./write | py read.py
from sys import stdin


for n in sorted(map(int, stdin.read().split()), reverse=True):
    print(n, end=' ')
