#!/bin/python

from sys import stdin

def main():
    for num in sorted(map(int, next(stdin).split(' ')[:-1])):
        print(num, end=" ")
    print()


if __name__ == '__main__':
    main()
